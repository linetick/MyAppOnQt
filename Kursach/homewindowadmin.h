#ifndef HOMEWINDOWADMIN_H
#define HOMEWINDOWADMIN_H

//#include <QDialog>
#include "personalaccountwindow.h"
#include "productswindow_manager.h"
#include "personswindowadmin.h"
#include "orderswindow.h"
//#include "QDialog"
#include "QWidget"

namespace Ui {
class HomeWindowAdmin;
}

class HomeWindowAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWindowAdmin(QWidget *parent = nullptr);
    ~HomeWindowAdmin();

private:
    Ui::HomeWindowAdmin *ui;
    PersonalAccountWindow *_PersonalAccountWindow;
    ProductsWindow_Manager *_ProductsWindow_Manager;
    PersonsWindowAdmin *_PersonsWindowAdmin;
    OrdersWindow *_OrdersWindow;
    // заказы(add)

    // QWidget interface
signals:
    void openProductsWindow();
    void openPAccountWindow();
    void openPersonsWindow();
    void openOrdersWindow();
    void exit();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_Products_button_clicked_clicked();
    void on_Persons_button_Clicked_clicked();
    void on_Orders_button_Clicked_clicked();
    void on_PAccount_button_clicked_clicked();
    void on_exit_clicked();
};

#endif // HOMEWINDOWADMIN_H
