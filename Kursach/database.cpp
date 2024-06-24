#include "database.h"
#include "qsqlrecord.h"
#include "user.h"
#include <QDate>

DataBase::DataBase()
{
    //Тут было тестовове
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("D:\\SQL\\DataBases\\Kurs.db");
//    //db.setDatabaseName("Kurs.db");
//    if (!db.open()) {
//        qDebug() << "Ошибка при подключении к базе данных:" << db.lastError().text();
//    }

    //Тут нужное
    QString dbPath = QCoreApplication::applicationDirPath() + "/Kurs.db";
    bool dbExists = QFile::exists(dbPath);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Ошибка при подключении к базе данных:" << db.lastError().text();
        throw std::runtime_error("Не удалось открыть базу данных.");
    }

    if (!dbExists) {
        qDebug() << "База данных не существует. Создание новой базы данных.";
        initializeDatabase();
    } else {
        qDebug() << "База данных уже существует.";
    }

}

void DataBase::initializeDatabase()
{
    QSqlQuery query(db);

    // Создание таблицы "Люди"
    if (!query.exec(R"(
            CREATE TABLE "Люди" (
                "ID_Человека" INTEGER NOT NULL UNIQUE,
                "Имя" TEXT NOT NULL,
                "Фамилия" TEXT NOT NULL,
                "Отчество" TEXT,
                "Телефон" TEXT NOT NULL UNIQUE,
                "Адрес" TEXT NOT NULL,
                "Логин" TEXT NOT NULL UNIQUE,
                "Пароль" TEXT NOT NULL,
                "Роль" TEXT NOT NULL,
                PRIMARY KEY("ID_Человека" AUTOINCREMENT)
            );
        )")) {
        qDebug() << "Ошибка при создании таблицы 'Люди':" << query.lastError().text();
    }

    // Создание таблицы "Доставка"
    if (!query.exec(R"(
            CREATE TABLE "Доставка" (
                "ID_Доставки" INTEGER NOT NULL UNIQUE,
                "ID_Покупателя" INTEGER NOT NULL,
                "Общая_Цена" INTEGER NOT NULL,
                "Дата_Покупки" TEXT NOT NULL,
                "Дата_Доставки" TEXT,
                "Адрес" TEXT NOT NULL,
                "Телефон" TEXT NOT NULL,
                "Статус" TEXT NOT NULL,
                PRIMARY KEY("ID_Доставки" AUTOINCREMENT),
                FOREIGN KEY("ID_Покупателя") REFERENCES "Люди"("ID_Человека")
            );
        )")) {
        qDebug() << "Ошибка при создании таблицы 'Доставка':" << query.lastError().text();
    }

    // Создание таблицы "Заказ"
    if (!query.exec(R"(
            CREATE TABLE "Заказ" (
                "ID_Заказа" INTEGER NOT NULL UNIQUE,
                "ID_Доставки" INTEGER NOT NULL,
                "ID_Продукта" INTEGER NOT NULL,
                "Название" TEXT NOT NULL,
                "Цена" INTEGER NOT NULL,
                "Количество" INTEGER NOT NULL,
                PRIMARY KEY("ID_Заказа" AUTOINCREMENT),
                FOREIGN KEY("ID_Продукта") REFERENCES "Товары"("ID_Товара"),
                FOREIGN KEY("ID_Доставки") REFERENCES "Доставка"("ID_Доставки")
            );
        )")) {
        qDebug() << "Ошибка при создании таблицы 'Заказ':" << query.lastError().text();
    }

    // Создание таблицы "Товары"
    if (!query.exec(R"(
            CREATE TABLE "Товары" (
                "ID_Товара" INTEGER NOT NULL UNIQUE,
                "Название" TEXT NOT NULL,
                "Описание" TEXT NOT NULL,
                "Цена" TEXT NOT NULL,
                "Наличие" INTEGER NOT NULL,
                "Скидка" INTEGER NOT NULL,
                PRIMARY KEY("ID_Товара" AUTOINCREMENT)
            );
        )")) {
        qDebug() << "Ошибка при создании таблицы 'Товары':" << query.lastError().text();
    }

    // Добавление администратора
    if (!query.exec(R"(
            INSERT INTO "Люди" ("Имя", "Фамилия", "Отчество", "Телефон", "Адрес", "Логин", "Пароль", "Роль")
            VALUES ('Админ', 'Администратор', 'Отчество', '1234567890', 'Адрес', 'админ', 'админ', 'Администратор');
        )")) {
        qDebug() << "Ошибка при добавлении администратора:" << query.lastError().text();
    }
}


//Проверка пустых строк МБ это нужно вынести в ещё один класс, где проверять
QStringList DataBase::checkInput(const QString& Name, const QString& LastName,
                                 const QString& MiddleName, const QString& Address,
                                 const QString& NumberPhone, const QString& login, const QString& password, const QString& Role) {
    QStringList errors;
    if (Name.trimmed().isEmpty()) {
        errors << "Name";
    }
    if (LastName.trimmed().isEmpty()) {
        errors << "LastName";
    }
    if (MiddleName.trimmed().isEmpty()) {
        errors << "MiddleName";
    }
    if (NumberPhone.trimmed().isEmpty() || NumberPhone.length() != 10) {
        errors << "NumberPhone";
    }
    if (Address.trimmed().isEmpty() && Role == "Покупатель") {
        errors << "Address";
    }
    if (login.trimmed().isEmpty()) {
        errors << "login";
    }
    if (password.trimmed().isEmpty()) {
        errors << "password";
    }
    for(int i = 1; i< NumberPhone.length(); i++)
    {
        if(NumberPhone[i] == '+')
        {
          errors << "NumberPhone";
        }
    }
    return errors;
}

// Проверка уникальности логина и номера
QStringList DataBase::checkUnique(const QString& login, const QString& phone) {
    QStringList uniqueErrors;
    QSqlQuery query(db);
    query.prepare("SELECT 'login' AS Field FROM \"Люди\" WHERE \"Логин\" = :login "
                  "UNION ALL SELECT 'phone' FROM \"Люди\" WHERE \"Телефон\" = :phone");
    query.bindValue(":login", login);
    query.bindValue(":phone", phone);
    if (!query.exec()) {
        qDebug() << "Ошибка при проверке уникальности:" << query.lastError().text();
    } else {
        while (query.next()) {
            if (query.value(0).toString() == "login") {
                uniqueErrors << "loginNotUnique";
            } else if (query.value(0).toString() == "phone") {
                uniqueErrors << "phoneNotUnique";
            }
        }
    }
    return uniqueErrors;
}

//Проверка уникальности продукта
QStringList DataBase::checkProductUnique(const QString& productName)
{
    QStringList uniqueErrors;
    QSqlQuery query(db);
    query.prepare("SELECT 'productName' FROM \"Товары\" WHERE \"Название\" = :productName");
    query.bindValue(":productName", productName);

    if (!query.exec()) {
        qDebug() << "Ошибка при проверке уникальности продукта:" << query.lastError().text();
    } else {
        if (query.next()) {
            uniqueErrors << "productNameNotUnique";  // Если запрос вернул строку, значит продукт с таким названием уже существует
        }
    }
    return uniqueErrors;
}


//------------- ТУТ ВСТАВКИ----------------------------
//Вставка перса
bool DataBase::insertNewPerson(const QString& Name, const QString& LastName, const QString& MiddleName,
                               const QString& NumberPhone, const QString& Address, const QString& login,
                               const QString& password, const QString& Role) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO \"Люди\" (\"Имя\", \"Фамилия\", \"Отчество\", \"Телефон\", \"Адрес\", \"Логин\", \"Пароль\", \"Роль\") "
                  "VALUES (:Name, :LastName, :MiddleName, :Phone, :Address, :Login, :Password, :Role)");

    query.bindValue(":Name", Name);
    query.bindValue(":LastName", LastName);
    query.bindValue(":MiddleName", MiddleName);
    query.bindValue(":Phone", NumberPhone);
    query.bindValue(":Address", Address);
    query.bindValue(":Login", login);
    query.bindValue(":Password", password);
    query.bindValue(":Role", Role);
    if (!query.exec()) {
        qDebug() << "Ошибка при вставке данных:" << query.lastError().text();
            return false;
    }
    return true;
}

//Вставка продукта
bool DataBase::insertProduct(const QString& name, const QString& description, const QString& price, int availability, int discount) {
    QSqlQuery query;
    query.prepare("INSERT INTO \"Товары\" (\"Название\", \"Описание\", \"Цена\", \"Наличие\", \"Скидка\") VALUES (:name, :description, :price, :availability, :discount)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":price", price);
    query.bindValue(":availability", availability);
    query.bindValue(":discount", discount);

    if (!query.exec()) {
        qDebug() << "Ошибка при добавлении нового товара:" << query.lastError().text();
        return false; // Возвращает false, если произошла ошибка
    }

    return true; // Возвращает true, если вставка прошла успешно
}

bool DataBase::updateProduct(int productId, const QString& name, const QString& description, const QString& price, int availability, int discount) {
    QSqlQuery query;
    query.prepare("UPDATE \"Товары\" SET \"Название\" = :name, \"Описание\" = :description, \"Цена\" = :price, \"Наличие\" = :availability, \"Скидка\" = :discount WHERE \"ID_Товара\" = :productId");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":price", price);
    query.bindValue(":availability", availability);
    query.bindValue(":discount", discount);
    query.bindValue(":productId", productId);

    if (!query.exec()) {
        qDebug() << "Ошибка при обновлении данных товара:" << query.lastError().text();
        return false; // Возвращает false, если произошла ошибка
    }

    return true; // Возвращает true, если обновление прошло успешно
}


//Изменение доставки
bool DataBase::updateDeliveryDetails(int deliveryId, const QString& newAddress, const QString& newDeliveryDate, const QString& newStatus)
{
    QSqlQuery query;

    // Обновляем адрес в таблице Люди
    QString updateAddressQuery = R"(
        UPDATE Доставка
        SET Адрес = :newAddress
        WHERE ID_Доставки = :deliveryId
    )";

    query.prepare(updateAddressQuery);
    query.bindValue(":newAddress", newAddress);
    query.bindValue(":deliveryId", deliveryId);

    if (!query.exec()) {
        qDebug() << "Error updating address:" << query.lastError().text();
        return false;
    }

    // Обновляем дату доставки и статус в таблице Доставка
    QString updateDeliveryQuery = R"(
        UPDATE Доставка
        SET Дата_Доставки = :newDeliveryDate,
            Статус = :newStatus
        WHERE ID_Доставки = :deliveryId
    )";

    query.prepare(updateDeliveryQuery);
    query.bindValue(":newDeliveryDate", newDeliveryDate);
    query.bindValue(":newStatus", newStatus);
    query.bindValue(":deliveryId", deliveryId);

    if (!query.exec()) {
        qDebug() << "Error updating delivery details:" << query.lastError().text();
        return false;
    }
    qDebug() << "Delivery details updated successfully for ID_Доставки:" << deliveryId;
        return true;
}


//-----------------------------------------------------------

//Проверка при входе
QString DataBase::checkCredentials(const QString& login, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT \"ID_Человека\", \"Роль\" FROM \"Люди\" WHERE \"Логин\" = :login AND \"Пароль\" = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
            qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
                return "Ошибка";
    }

    if (query.next()) {
            int userId = query.value(0).toInt();
            QString userRole = query.value(1).toString();

            User* session = User::getInstance();
            session->setUserId(userId);
            session->setUserRole(userRole);

            qDebug() << "Вход выполнен успешно. ID пользователя:" << userId
                     << ", Роль:" << userRole;

                return userRole;
    }

    return "Ошибка";
}

bool DataBase::addDelivery(int Price)
{
    User* session = User::getInstance();
    QDate currentDate = QDate::currentDate();
    QSqlQuery userQuery(db);

    userQuery.prepare("SELECT Адрес, Телефон FROM Люди WHERE ID_Человека = :userId");
    userQuery.bindValue(":userId", session->getUserId());

    if (!userQuery.exec() || !userQuery.next()) {
                qDebug() << "Error retrieving user data:" << userQuery.lastError();
                return false;
    }

    QString address = userQuery.value("Адрес").toString();
    QString phone = userQuery.value("Телефон").toString();

    // Запрос на добавление доставки
    QSqlQuery query(db);
    query.prepare("INSERT INTO Доставка (ID_Покупателя, Общая_Цена, Дата_Покупки, Дата_Доставки, Адрес, Телефон, Статус) VALUES (:customerId, :totalPrice, :purchaseDate, :deliveryDate, :address, :phone, :status)");
    query.bindValue(":customerId", session->getUserId());
    query.bindValue(":totalPrice", Price);
    query.bindValue(":purchaseDate", currentDate.toString("dd.MM.yyyy"));
    query.bindValue(":deliveryDate", "В обработке"); // Дата доставки на данный момент неизвестна
    query.bindValue(":address", address);
    query.bindValue(":phone", phone);
    query.bindValue(":status", "В обработке");

    if (!query.exec()) {
                qDebug() << "Error inserting delivery data:" << query.lastError();
                return false;
    }

    int deliveryId = query.lastInsertId().toInt();

    QList<Basket::CartItem> cart = Basket::getCartItems();

    for (const auto& item : cart)
        {
            int productId = item.productId;
            int quantity = item.quantity;

            query.prepare("INSERT INTO Заказ (ID_Доставки, ID_Продукта, Название, Цена, Количество) VALUES (:deliveryId, :productId, :name, :price, :quantity)");
            query.bindValue(":deliveryId", deliveryId);
            query.bindValue(":productId", productId);
            query.bindValue(":name", item.name);
            query.bindValue(":price", item.price);
            query.bindValue(":quantity", quantity);

            if (!query.exec()) {
                    qDebug() << "Ошибка вставки в таблицу Заказ:" << query.lastError().text();
                        db.rollback();
                    return false;
            }

            query.prepare("UPDATE Товары SET Наличие = Наличие - :quantity WHERE ID_Товара = :productId");
            query.bindValue(":quantity", quantity);
            query.bindValue(":productId", productId);

            if (!query.exec()) {
                    qDebug() << "Ошибка обновления таблицы Товары:" << query.lastError().text();
                                db.rollback();
                    return false;
            }

            qDebug() << "Доставка добавлена с ID:" << deliveryId;
        }
    return true;
}

bool DataBase::updatePerson(int IDPerson, const QString& Name, const QString& LastName, const QString& MiddleName,
                               const QString& NumberPhone, const QString& Address, const QString& login,
                               const QString& password, const QString& Role)
{
    QSqlQuery query;
    query.prepare("UPDATE \"Люди\" SET \"Имя\" = :Name, \"Фамилия\" = :LastName, \"Отчество\" = :MiddleName, \"Телефон\" = :Phone, \"Адрес\" = :Address, \"Логин\" = :Login, \"Пароль\" = :Password, \"Роль\" = :Role WHERE \"ID_Человека\" = :personId");
    query.bindValue(":Name", Name);
    query.bindValue(":LastName", LastName);
    query.bindValue(":MiddleName", MiddleName);
    query.bindValue(":Phone", NumberPhone);
    query.bindValue(":Address", Address);
    query.bindValue(":Login", login);
    query.bindValue(":Password", password);
    query.bindValue(":Role", Role);
    query.bindValue(":personId", IDPerson);

    if (!query.exec()) {
            qDebug() << "Ошибка при обновлении данных пользователя:" << query.lastError().text();
            return false; // Возвращает false, если произошла ошибка
    }

    return true;
}

bool DataBase::changePassword(int IDperson, QString password)
{
    QSqlQuery query;
    query.prepare("UPDATE \"Люди\" SET \"Пароль\" = :Password WHERE \"ID_Человека\" = :personId");
    query.bindValue(":Password", password);
    query.bindValue(":personId", IDperson);

    if (!query.exec()) {
            qDebug() << "Ошибка при обновлении данных пользователя:" << query.lastError().text();
            return false; // Возвращает false, если произошла ошибка
    }

    return true;
}

bool DataBase::changeAddres(int IDperson, QString addres)
{
    QSqlQuery query;
    query.prepare("UPDATE \"Люди\" SET \"Адрес\" = :Password WHERE \"ID_Человека\" = :personId");
    query.bindValue(":Password", addres);
    query.bindValue(":personId", IDperson);

    if (!query.exec()) {
            qDebug() << "Ошибка при обновлении данных пользователя:" << query.lastError().text();
            return false; // Возвращает false, если произошла ошибка
    }

    return true;
}

bool DataBase::changePhone(int IDperson, QString phone)
{
    QSqlQuery query;
    query.prepare("UPDATE \"Люди\" SET \"Телефон\" = :Password WHERE \"ID_Человека\" = :personId");
    query.bindValue(":Password", phone);
    query.bindValue(":personId", IDperson);

    if (!query.exec()) {
            qDebug() << "Ошибка при обновлении данных пользователя:" << query.lastError().text();
            return false; // Возвращает false, если произошла ошибка
    }

    return true;
}

//-------------------------------------------Тут запросы на возвращение таблиц-------------------------------------

//Запрос на возвращение продуктов
void DataBase::getProduct()
{
    model = new QSqlTableModel(nullptr, db);
    model->setTable("Товары");
    model->select();
}

QSqlTableModel* DataBase::getModel() {
    return model;
}

QSqlRelationalTableModel* DataBase::Anothermodel()
{
    return modell;
}

void DataBase::getDeliveryByCustomerId()
{
    model = new QSqlTableModel(nullptr, db);
    model->setTable("Доставка");

    User* session = User::getInstance();
    int ID = session->getUserId();

        // Устанавливаем фильтр по ID_Покупателя
    model->setFilter(QString("ID_Покупателя = %1").arg(ID));

        // Исключаем поле ID_Покупателя из представления
    model->setHeaderData(1, Qt::Horizontal, "Общая_Цена"); // Устанавливаем заголовок для ID_Покупателя
    model->removeColumn(1); // Убираем колонку ID_Покупателя

    model->select();
}

QSqlQueryModel* DataBase::getDeliveryInfo(int a) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr;
    if(a == 5)
    {
            queryStr = R"(
            SELECT
                Доставка.ID_Доставки,
                Люди.Фамилия,
                Люди.Имя,
                Люди.Отчество,
                Доставка.Телефон,
                Доставка.Адрес,
                Доставка.Статус,
                Доставка.Дата_Покупки,
                Доставка.Дата_Доставки
            FROM
                Доставка
            JOIN
                Люди ON Доставка.ID_Покупателя = Люди.ID_Человека
        )";
    }
    if(a == 1)
    {
        queryStr = R"(
        SELECT
            Доставка.ID_Доставки,
            Люди.Фамилия,
            Люди.Имя,
            Люди.Отчество,
            Доставка.Телефон,
            Доставка.Адрес,
            Доставка.Статус,
            Доставка.Дата_Покупки,
            Доставка.Дата_Доставки
        FROM
            Доставка
        JOIN
            Люди ON Доставка.ID_Покупателя = Люди.ID_Человека
        WHERE
            Доставка.Статус = 'В обработке'
        )";
    }
    if(a  == 2)
    {
        queryStr = R"(
        SELECT
            Доставка.ID_Доставки,
            Люди.Фамилия,
            Люди.Имя,
            Люди.Отчество,
            Доставка.Телефон,
            Доставка.Адрес,
            Доставка.Статус,
            Доставка.Дата_Покупки,
            Доставка.Дата_Доставки
        FROM
            Доставка
        JOIN
            Люди ON Доставка.ID_Покупателя = Люди.ID_Человека
        WHERE
            Доставка.Статус = 'Доставляется'
        )";
    }
    if(a == 3)
    {
        queryStr = R"(
        SELECT
            Доставка.ID_Доставки,
            Люди.Фамилия,
            Люди.Имя,
            Люди.Отчество,
            Доставка.Телефон,
            Доставка.Адрес,
            Доставка.Статус,
            Доставка.Дата_Покупки,
            Доставка.Дата_Доставки
        FROM
            Доставка
        JOIN
            Люди ON Доставка.ID_Покупателя = Люди.ID_Человека
        WHERE
            Доставка.Статус = 'Отменён'
        )";
    }
    if(a == 4)
    {
        queryStr = R"(
        SELECT
            Доставка.ID_Доставки,
            Люди.Фамилия,
            Люди.Имя,
            Люди.Отчество,
            Доставка.Телефон,
            Доставка.Адрес,
            Доставка.Статус,
            Доставка.Дата_Покупки,
            Доставка.Дата_Доставки
        FROM
            Доставка
        JOIN
            Люди ON Доставка.ID_Покупателя = Люди.ID_Человека
        WHERE
            Доставка.Статус = 'Завершён'
        )";
    }

    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
            qDebug() << "Error executing query:" << query.lastError().text();
            delete model;
            return nullptr;
    }

    model->setQuery(query);

    return setHeadlines(model);
}
//----------------------------------Рефакторинг-------------------------:
QSqlQueryModel* DataBase::setHeadlines(QSqlQueryModel* model)
{
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Фамилия");
    model->setHeaderData(2, Qt::Horizontal, "Имя");
    model->setHeaderData(3, Qt::Horizontal, "Отчество");
    model->setHeaderData(4, Qt::Horizontal, "Номер");
    model->setHeaderData(5, Qt::Horizontal, "Адрес");
    model->setHeaderData(6, Qt::Horizontal, "Статус");
    model->setHeaderData(7, Qt::Horizontal, "Покупка");
    model->setHeaderData(8, Qt::Horizontal, "Доставка");
    return model;
}


void DataBase::getOrdersByDeliveryId(int deliveryId) {
        modell = new QSqlRelationalTableModel(nullptr, db);
        modell->setTable("Заказ");

        // Устанавливаем связь с таблицей Товары по ID_Продукта
        //modell->setRelation(2, QSqlRelation("Товары", "ID_Товара", "Название"));

        // Устанавливаем фильтр по ID_Доставки
        modell->setFilter(QString("ID_Доставки = %1").arg(deliveryId));

        // Исключаем поле ID_Доставки
        //modell->setHeaderData(1, Qt::Horizontal, "Название"); // Устанавливаем заголовок для ID_Доставки
        modell->removeColumn(1);
        //modell->removeColumn(2);// Убираем колонку ID_Доставки

        // Обновляем данные модели
        modell->select();
    }

QSqlRecord DataBase::getProductById(int productId) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Товары WHERE ID_Товара = :ID");
    query.bindValue(":ID", productId);
    if (query.exec() && query.next()) {
                return query.record();
    }
    qDebug() << "Ошибка при запросе продукта:" << query.lastError().text();
        return QSqlRecord();
}

void DataBase::addToBusket(int productID)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Товары WHERE ID_Товара = :ID");
    query.bindValue(":ID", productID);
}

QString DataBase::takeAddres()
{
    User* session = User::getInstance();
    int ID = session->getUserId();
    QSqlQuery query(db);
    query.prepare("SELECT Адрес FROM Люди WHERE ID_Человека = :ID");
    //query.prepare("SELECT Адрес FROM Люди");
    query.bindValue(":ID", ID);

    if (!query.exec()) {
                qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
                    return "";
    }

    if (query.next())
    {
        QString address = query.value(0).toString();
        return address;
    }
    else
    {
       qDebug() << "Запись не найдена";
       return "";
    }
}

QStringList DataBase::getDeliveryById(int deliveryId)
{
    QStringList deliveryDetails;

    QSqlQuery query;
    QString queryStr = R"(
        SELECT
            Люди.Фамилия,
            Люди.Имя,
            Люди.Отчество,
            Доставка.Телефон,
            Доставка.Адрес,
            Доставка.Статус,
            Доставка.Дата_Покупки,
            Доставка.Дата_Доставки
        FROM
            Доставка
        JOIN
            Люди ON Доставка.ID_Покупателя = Люди.ID_Человека
        WHERE
            Доставка.ID_Доставки = :deliveryId
    )";

    query.prepare(queryStr);
    query.bindValue(":deliveryId", deliveryId);

    if (query.exec()) {
       if (query.next()) {
                    QSqlRecord record = query.record();
                    deliveryDetails << record.value("Фамилия").toString()
                                    << record.value("Имя").toString()
                                    << record.value("Отчество").toString()
                                    << record.value("Телефон").toString()
                                    << record.value("Адрес").toString()
                                    << record.value("Статус").toString()
                                    << record.value("Дата_Покупки").toString()
                                    << record.value("Дата_Доставки").toString();
       } else {
                    qDebug() << "No record found for ID_Доставки:" << deliveryId;
       }
    } else {
       qDebug() << "Query error:" << query.lastError();
    }

    return deliveryDetails;
}

QSqlTableModel* DataBase::getPeopleTable() {
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Люди");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    // Удаляем колонки "Логин" и "Пароль"
    model->removeColumn(model->fieldIndex("Логин"));
    model->removeColumn(model->fieldIndex("Пароль"));

    return model;
}

QSqlTableModel* DataBase::getPeopleTableNoneLogin() {
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Люди");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    // Удаляем колонку "Пароль"
    model->removeColumn(model->fieldIndex("Пароль"));

    return model;
}


//Удаление продукта

bool DataBase::deleteProduct(int IDProduct)
{
    QSqlQuery query;
    query.prepare("DELETE FROM \"Товары\" WHERE \"ID_Товара\" = :productId");
    query.bindValue(":productId", IDProduct);

    if (!query.exec()) {
       qDebug() << "Ошибка при удалении товара:" << query.lastError().text();
           return false;
    }

    return true;
}

bool DataBase::deletePerson(int personID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM \"Люди\" WHERE \"ID_Человека\" = :personID");
    query.bindValue(":personID", personID);

    if (!query.exec()) {
           qDebug() << "Ошибка при удалении пользователя:" << query.lastError().text();
               return false;
    }

    return true;
}

QSqlRecord DataBase::getPersonByID(int personID)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Люди WHERE ID_Человека = :ID");
    query.bindValue(":ID", personID);
    if(query.exec() && query.next())
    {
               return query.record();
    }
    qDebug() << "Ошибка при заапросе продукта:" << query.lastError().text();
        return QSqlRecord();
}
