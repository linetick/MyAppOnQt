#include "homewindowmanager.h"
#include "ui_homewindowmanager.h"

HomeWindowManager::HomeWindowManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWindowManager)
{
    ui->setupUi(this);

    //connect(this, &HomeWindowManager::exit, qApp, &QApplication::quit);

    setWindowTitle("Домашнее окно");

    _PersonalAccountWindow = new PersonalAccountWindow();
    _PersonsWindow = new Persons();
    _ProductsWindow_Manager = new ProductsWindow_Manager();
    _OrdersWindow = new OrdersWindow();


    connect(this, &HomeWindowManager::openProducts, //Открыть продукты
            this, &HomeWindowManager::close);
    connect(this, &HomeWindowManager::openProducts,
            _ProductsWindow_Manager, &ProductsWindow_Manager::show);
    connect(_ProductsWindow_Manager, &ProductsWindow_Manager::Return,
            this, &ProductsWindow_Manager::show);
    //------------------
    connect(this, &HomeWindowManager::openPersons, //Открыть людей
            this, &HomeWindowManager::close);
    connect(this, &HomeWindowManager::openPersons,
            _PersonsWindow, &Persons::show);
    connect(_PersonsWindow, &Persons::Return,
            this, &Persons::show);
    //------------------
    connect(this, &HomeWindowManager::openOrders, //Открыть заказы
            this, &HomeWindowManager::close);
    connect(this, &HomeWindowManager::openOrders,
            _OrdersWindow, &OrdersWindow::show);
    connect(_OrdersWindow, &OrdersWindow::Return,
            this, &OrdersWindow::show);
    //-------------------
    connect(this, &HomeWindowManager::openPAccount, //Открыть лКабинет
            this, &HomeWindowManager::close);
    connect(this, &HomeWindowManager::openPAccount,
            _PersonalAccountWindow, &PersonalAccountWindow::show);
    connect(_PersonalAccountWindow, &PersonalAccountWindow::Return,
            this, &PersonalAccountWindow::show);

}

HomeWindowManager::~HomeWindowManager()
{
    delete ui;
}

void HomeWindowManager::on_Products_button_clicked_clicked()
{
    emit openProducts();
}


void HomeWindowManager::on_Persons_button_clicked_clicked()
{
    emit openPersons();
}


void HomeWindowManager::on_Orders_button_Clicked_clicked()
{
    emit openOrders();
}


void HomeWindowManager::on_PAccount_button_Clicked_clicked()
{
    emit openPAccount();
}


void HomeWindowManager::on_exit_clicked()
{
    emit exit();
}

