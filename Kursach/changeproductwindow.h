#ifndef CHANGEPRODUCTWINDOW_H
#define CHANGEPRODUCTWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class ChangeProductWindow;
}

class ChangeProductWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeProductWindow(QWidget *parent = nullptr);
    ~ChangeProductWindow();

    void applyStyleForLabel(int mode);
    void applyDefaultStyles();
    void applyDefaultStyleButton();
    QStringList checkInputProduct(QString name, QString information, QString price, QString count, QString discount);
    void applyErrorStyles(const QStringList &errors);

public slots:
    void takeID(int a);


signals:
    void update();


private slots:
    void on_Close_button_Clicked_clicked();

    void on_ChangeName_button_Clicked_clicked();

    void on_ChangeInformation_button_Clicked_clicked();

    void on_ChangePrice_button_Clicked_clicked();

    void on_ChangeQuantity_button_Clicked_clicked();

    void on_ChangeDiscount_button_Clicked_clicked();

    void on_ChangeProduct_button_Clicked_clicked();

private:
    Ui::ChangeProductWindow *ui;
    DataBase db;

    bool checkName;
    bool checkInformation ;
    bool checkPrice;
    bool checkQuantity;
    bool checkDiscount;

    int ID;
    QString Name;
    QString Information;
    int Price;
    int Quantity;
    int Discount;
};

#endif // CHANGEPRODUCTWINDOW_H
