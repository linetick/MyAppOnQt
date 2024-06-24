#ifndef PRODUCTSWINDOW_BUYER_H
#define PRODUCTSWINDOW_BUYER_H

#include "basketwindow.h"
#include "database.h"
//#include <QDialog>
#include "basketclass.h"
#include "QWidget"


namespace Ui {
class ProductsWindow_Buyer;
}

class ProductsWindow_Buyer : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsWindow_Buyer(QWidget *parent = nullptr);
    ~ProductsWindow_Buyer();

    int takeID();
    void showEvent(QShowEvent *event);

signals:
    void Return();
    void productAdded();

private slots:
    void on_Return_button_Clicked_clicked();

    void on_Add_button_Clicked_clicked();

private:
    Ui::ProductsWindow_Buyer *ui;
    DataBase db;
    BasketWindow *_BasketWindow;
    QSortFilterProxyModel *proxyModel;
   // Basket basket;
};

#endif // PRODUCTSWINDOW_BUYER_H
