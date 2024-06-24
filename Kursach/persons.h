#ifndef PERSONS_H
#define PERSONS_H

//#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "database.h"
#include "qsortfilterproxymodel.h"
#include "QWidget"

namespace Ui {
class Persons;
}

class Persons : public QWidget
{
    Q_OBJECT

public:
    explicit Persons(QWidget *parent = nullptr);
    ~Persons();

    void showEvent(QShowEvent *event);
    void getPersons();

signals:
    void Return();

private slots:
    void on_Return_button_Clicked_clicked();

private:
    Ui::Persons *ui;
    DataBase db;
    QSqlTableModel *model;
    QSortFilterProxyModel *proxyModel;
};

#endif // PERSONS_H
