#ifndef PRODUCTSWINDOW_MANAGER_H
#define PRODUCTSWINDOW_MANAGER_H

//#include <QDialog>
#include "addproductwindow.h"
#include "changeproductwindow.h"
#include "qsortfilterproxymodel.h"
#include "warningwindow.h"
#include "QWidget"

namespace Ui {
class ProductsWindow_Manager;
}

class ProductsWindow_Manager : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsWindow_Manager(QWidget *parent = nullptr);
    ~ProductsWindow_Manager();

    void disableHomeWindow();
    void enableHomeWindow();
    void getPerson();
    void getProducts();
    void showEvent(QShowEvent *event);
    int takeID();

signals:
    void Return();
    void openAddProduct();
    void changeProduct(); //Тут подумать
    //void disableHomeWindow();
    void openChangeProduct();
    void openWarning();
    void getInformationInChange(int);

public slots:
    void Delete();

private slots:
    void on_Return_button_Clicked_clicked();

    void on_AddProduct_button_Clicked_clicked();

    void on_ChangeProduct_button_Clicked_clicked();

    void on_DeleteProduct_button_Clicked_clicked();

private:
    Ui::ProductsWindow_Manager *ui;
    int ID;
    AddProductWindow *_AddProductWindow;
    ChangeProductWindow *_ChangeProductWindow;
    WarningWindow *_WarningWindow;
    DataBase db;
    QSortFilterProxyModel *proxyModel;
};

#endif // PRODUCTSWINDOW_MANAGER_H
