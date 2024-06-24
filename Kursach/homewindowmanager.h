#ifndef HOMEWINDOWMANAGER_H
#define HOMEWINDOWMANAGER_H

//#include <QDialog>
#include "persons.h"
#include "productswindow_manager.h"
#include "personalaccountwindow.h"
#include "orderswindow.h"
#include "QWidget"

namespace Ui {
class HomeWindowManager;
}

class HomeWindowManager : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWindowManager(QWidget *parent = nullptr);
    ~HomeWindowManager();

signals:
    void openPersons();
    void openProducts();
    void openOrders();
    void openPAccount();
    void exit();

private slots:
    void on_Products_button_clicked_clicked();

    void on_Persons_button_clicked_clicked();

    void on_Orders_button_Clicked_clicked();

    void on_PAccount_button_Clicked_clicked();

    void on_exit_clicked();

private:
    Ui::HomeWindowManager *ui;
    Persons *_PersonsWindow;
    ProductsWindow_Manager *_ProductsWindow_Manager;
    PersonalAccountWindow *_PersonalAccountWindow;
    OrdersWindow *_OrdersWindow;
};

#endif // HOMEWINDOWMANAGER_H
