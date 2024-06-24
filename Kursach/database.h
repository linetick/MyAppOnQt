#ifndef DATABASE_H
#define DATABASE_H
#include<QSqlTableModel>
#include<QSqlError>
#include <QStringList>
#include <QSqlQuery>
#include <QDebug>
#include <basketclass.h>
#include<QSqlRelationalTableModel>
#include<QSqlRelation>
#include<QSqlRecord>
#include <QFile>
#include <QCoreApplication>


class DataBase
{
public:
    DataBase();
    QStringList checkInput(const QString& Name, const QString& LastName,
                           const QString& MiddleName, const QString& Address,
                           const QString& NumberPhone, const QString& login, const QString& password, const QString& Role);

    QStringList checkUnique(const QString& login, const QString& phone);

    bool insertNewPerson(const QString& Name, const QString& LastName, const QString& MiddleName,
                         const QString& NumberPhone, const QString& Address, const QString& login,
                         const QString& password, const QString& Role);
    QString checkCredentials(const QString& login, const QString& password);
    QStringList checkProductUnique(const QString& productName);
    bool insertProduct(const QString& name, const QString& description, const QString& price, int availability, int discount);
    void getProduct();
    QSqlTableModel* getModel();
    QSqlRelationalTableModel *Anothermodel();

    QSqlRecord getProductById(int productId);
    void addToBusket(int selected);
    QString takeAddres();
    bool addDelivery(int Price);
    void getDeliveryByCustomerId();
    void getOrdersByDeliveryId(int deliveryId);
    QSqlQueryModel* getDeliveryInfo(int a);
    QSqlQueryModel* setHeadlines(QSqlQueryModel* model);
    QStringList getDeliveryById(int deliveryId);
    bool updateDeliveryDetails(int deliveryId, const QString& newAddress, const QString& newDeliveryDate, const QString& newStatus);
    bool updateProduct(int productId, const QString& name, const QString& description, const QString& price, int availability, int discount);
    bool deleteProduct(int productId);
    QSqlTableModel* getPeopleTable();
    bool deletePerson(int personID);
    QSqlTableModel* getPeopleTableNoneLogin();
    QSqlRecord getPersonByID(int personID);
    bool updatePerson(int IDPerson,const QString& Name, const QString& LastName, const QString& MiddleName,
                                const QString& NumberPhone, const QString& Address, const QString& login,
                      const QString& password, const QString& Role);
    bool changePassword(int IDperson, QString password);
    bool changeAddres(int IDperson, QString addres);
    bool changePhone(int IDperson, QString phone);
    void initializeDatabase();

private:
    QSqlDatabase db;
    QSqlTableModel* model;
    QSqlRelationalTableModel *modell;
};

#endif // DATABASE_H
