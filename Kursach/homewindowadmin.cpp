#include "homewindowadmin.h"
#include "ui_homewindowadmin.h"

HomeWindowAdmin::HomeWindowAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWindowAdmin)
{
    ui->setupUi(this);

    setWindowTitle("Домашнее окно");
    //Инициализация окон
    _PersonalAccountWindow = new PersonalAccountWindow();
    _PersonsWindowAdmin = new PersonsWindowAdmin();
    _ProductsWindow_Manager = new ProductsWindow_Manager();
    _OrdersWindow = new OrdersWindow();

    connect(this, &HomeWindowAdmin::exit, qApp, &QApplication::quit);


    connect(this, &HomeWindowAdmin::openProductsWindow, //Открыть продукты
            this, &HomeWindowAdmin::close);
    connect(this, &HomeWindowAdmin::openProductsWindow,
            _ProductsWindow_Manager, &ProductsWindow_Manager::show);
    connect(_ProductsWindow_Manager, &ProductsWindow_Manager::Return,
            this, &ProductsWindow_Manager::show);
    //------------------
    connect(this, &HomeWindowAdmin::openPersonsWindow, //Открыть продукты
            this, &HomeWindowAdmin::close);
    connect(this, &HomeWindowAdmin::openPersonsWindow,
            _PersonsWindowAdmin, &PersonsWindowAdmin::show);
    connect(_PersonsWindowAdmin, &PersonsWindowAdmin::Return,
            this, &PersonsWindowAdmin::show);
    //------------------
    connect(this, &HomeWindowAdmin::openOrdersWindow, //Открыть продукты
            this, &HomeWindowAdmin::close);
    connect(this, &HomeWindowAdmin::openOrdersWindow,
            _OrdersWindow, &OrdersWindow::show);
    connect(_OrdersWindow, &OrdersWindow::Return,
            this, &OrdersWindow::show);
    //-------------------
    connect(this, &HomeWindowAdmin::openPAccountWindow, //Открыть продукты
            this, &HomeWindowAdmin::close);
    connect(this, &HomeWindowAdmin::openPAccountWindow,
            _PersonalAccountWindow, &PersonalAccountWindow::show);
    connect(_PersonalAccountWindow, &PersonalAccountWindow::Return,
            this, &PersonalAccountWindow::show);


    // окно заказов
}

HomeWindowAdmin::~HomeWindowAdmin()
{
    delete ui;
}

void HomeWindowAdmin::closeEvent(QCloseEvent *event)
{
    //qApp->quit();
}



void HomeWindowAdmin::on_Products_button_clicked_clicked()
{
    emit openProductsWindow();
}


void HomeWindowAdmin::on_Persons_button_Clicked_clicked()
{
    emit openPersonsWindow();
}


void HomeWindowAdmin::on_Orders_button_Clicked_clicked()
{
    emit openOrdersWindow();
}


void HomeWindowAdmin::on_PAccount_button_clicked_clicked()
{
    emit openPAccountWindow();
}


void HomeWindowAdmin::on_exit_clicked()
{
    emit exit();
}

