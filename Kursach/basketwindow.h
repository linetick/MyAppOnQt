#ifndef BASKETWINDOW_H
#define BASKETWINDOW_H

#include "database.h"
//#include <QDialog>
#include "basketclass.h"
#include "buywindow.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "QWidget"

namespace Ui {
class BasketWindow;
}

class BasketWindow : public QWidget
{
    Q_OBJECT    
public:
    explicit BasketWindow(QWidget *parent = nullptr);
    ~BasketWindow();


    void updateCart();
    int takeID();
    void applyDefaultStyles();
    void calculateTotalMoney();

public slots:
    void fillTableWithCartItems(const QList<Basket::CartItem> &cart);
    void Update();

signals:
    void Return();
    void openBuyWindow();
    void takeCountMoney(QString);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_Return_button_Clicked_clicked();


    void on_Buy_button_clicked_clicked();

    void on_Clear_button_Clicked_clicked();

    void on_Delete_button_Clicked_clicked();

    void on_DeleteFull_button_Clicked__clicked();

private:
    Ui::BasketWindow *ui;
    DataBase db;
    BuyWindow *_BuyWindow;
    QStandardItemModel *model;
};

#endif // BASKETWINDOW_H
