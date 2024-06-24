#include "basketwindow.h"
#include "qsortfilterproxymodel.h"
#include "ui_basketwindow.h"
#include <QShowEvent>
#include <QString>

BasketWindow::BasketWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasketWindow),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    setWindowTitle("Корзина");

    //Инициализация окна
    _BuyWindow = new BuyWindow(this);

    model->setHorizontalHeaderLabels(QStringList() << "ID_Товара" << "Название" << "Описание" << "Цена" << "Количество" << "Скидка");
    ui->tableView->setModel(model);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel);

    //Сигналы
    connect(this, &BasketWindow::openBuyWindow,
            _BuyWindow, &BuyWindow::exec);
    connect(this, &BasketWindow::takeCountMoney, _BuyWindow, &BuyWindow::takeCountMoney);
    connect(_BuyWindow, &BuyWindow::complete, this, &BasketWindow::Update);
    connect(ui->Search, &QLineEdit::textChanged, [proxyModel](const QString &text) {
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    });

    // Махинации с таблицей:
    QHeaderView* horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch); // Растягивает все столбцы равномерно
    //
    ui->tableView->setShowGrid(true); // Показывает сетку таблицы
    ui->tableView->setFrameShape(QFrame::NoFrame); // Убирает рамку вокруг таблицы, если необходимо
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->verticalHeader()->setVisible(false);
    fillTableWithCartItems(Basket::getCartItems());
}

BasketWindow::~BasketWindow()
{
    delete ui;
}

void BasketWindow::fillTableWithCartItems(const QList<Basket::CartItem> &cart) {
    //model->removeRows(0, model->rowCount());  // Очистка текущих данных в модели
    if (model != nullptr) {
        model->removeRows(0, model->rowCount());
    } else {
        qDebug() << "Model is not initialized!";
    }

    for (const auto &item : cart) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::number(item.productId)));
        row.append(new QStandardItem(item.name));
        row.append(new QStandardItem(item.description));
        row.append(new QStandardItem(QString::number(item.price)));
        row.append(new QStandardItem(QString::number(item.quantity)));
        row.append(new QStandardItem(QString::number(item.discount)));

        model->appendRow(row);
    }
    ui->tableView->update();
}

void BasketWindow::Update()
{
    BasketWindow::fillTableWithCartItems(Basket::getCartItems());
    BasketWindow::calculateTotalMoney();
}

int BasketWindow::takeID()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        //QMessageBox::warning(this, "Выбор элемента", "Пожалуйста, выберите элемент в таблице."); // тут добавить
        return -1;
    }

    bool correctColumnSelected = false;
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0) { // Предполагаем, что ID_Товара находится в первой колонке
            //correctColumnSelected = true;
            return index.data().toInt();
        }
    }

    if (!correctColumnSelected)
    {
        //QMessageBox::warning(this, "Неверный выбор", "Пожалуйста, выберите ID_Товара в первой колонке.");
        return -1;
    } /*else {
        // Здесь код для обработки корректного выбора, если необходимо
        QMessageBox::information(this, "Корректный выбор", "Выбран ID_Товара.");
    }*/
    return -1;
}

void BasketWindow::calculateTotalMoney() {
    int total = 0;
    int columnIndex = 3;

    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *item = model->item(row, columnIndex);
        if (item) {
            total += item->text().toInt();
        }
    }
    if(total > 0)
    {
        ui->Name->setStyleSheet("color: white; font-weight: bold; border: none; font-size: 20pt; background-color: none;");
        ui->Name->setText("Общая цена:");
        ui->Price->setStyleSheet("color: white; font-weight: bold; border: none; font-size: 20pt; background-color: none;");
        ui->Price->setText(QString::number(total));
        emit takeCountMoney(QString::number(total));
        ui->Buy_button_clicked->setStyleSheet("QPushButton {color: white;background-color: rgba(255,255,255,30);border: 1px solid rgba(255,255,255,40);border-radius: 12px;font-size: 14pt;} QPushButton:hover{background-color: rgba(255,255,255,40);}QPushButton:pressed{background-color: rgba(255,255,255,70);}");
        ui->Buy_button_clicked->setText("Купить");
    }
    else applyDefaultStyles();

}

void BasketWindow::applyDefaultStyles()
{
    //QString Defalut = "color:white; padding-left: 10px;";
    //ui->Name->setStyleSheet(Defalut);
    ui->Name->setText("");
    //ui->Price->setStyleSheet(Defalut);
    ui->Price->setText("");
    ui->Buy_button_clicked->setStyleSheet("QPushButton {color: white; font-weight: bold;border: none; font-size: 20pt;background-color: none;}");
    ui->Buy_button_clicked->setText("");
}


void BasketWindow::updateCart() {
    BasketWindow::fillTableWithCartItems(Basket::getCartItems());
    BasketWindow::calculateTotalMoney();
}

void BasketWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    fillTableWithCartItems(Basket::getCartItems());
    BasketWindow::calculateTotalMoney();
}

void BasketWindow::on_Return_button_Clicked_clicked()
{
    this->close();
    emit Return();
}


void BasketWindow::on_Buy_button_clicked_clicked()
{
    if(ui->Price->text() != "")  emit openBuyWindow();

}


void BasketWindow::on_Clear_button_Clicked_clicked()
{
    Basket::clearCart();
    BasketWindow::fillTableWithCartItems(Basket::getCartItems());
    BasketWindow::calculateTotalMoney();
}


void BasketWindow::on_Delete_button_Clicked_clicked()
{
    Basket::removeFromCart(takeID(), 1);
    BasketWindow::fillTableWithCartItems(Basket::getCartItems());
    BasketWindow::calculateTotalMoney();
}


void BasketWindow::on_DeleteFull_button_Clicked__clicked()
{
    Basket::removeFromCart(takeID(), 2);
    BasketWindow::fillTableWithCartItems(Basket::getCartItems());
    BasketWindow::calculateTotalMoney();
}

