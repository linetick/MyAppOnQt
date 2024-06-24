#ifndef ADDPRODUCTWINDOW_H
#define ADDPRODUCTWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AddProductWindow;
}

class AddProductWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductWindow(QWidget *parent = nullptr);
    ~AddProductWindow();

    void applyStyleForLabel(int mode);
    void applyDefaultStyles();
    void applyErrorStyles(const QStringList &errors);
    QStringList checkInputProduct(QString name, QString information, QString money, QString count, QString skidka);

signals:
    void closee();

private slots:
    void on_Close_button_Clicked_clicked();

    void on_AddProduct_button_Clicked_clicked();

private:
    Ui::AddProductWindow *ui;
    DataBase DB;
};

#endif // ADDPRODUCTWINDOW_H
