#include "homewindowbuyeer.h"
#include "ui_homewindowbuyeer.h"

HomeWindowBuyeer::HomeWindowBuyeer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWindowBuyeer)
{
    ui->setupUi(this);

    setWindowTitle("Домашнее окно");

    connect(this, &HomeWindowBuyeer::exit, qApp, &QApplication::quit);

    _ProductsWindow_Buyer = new ProductsWindow_Buyer();
    _HistoryWindow = new HistoryWindow();
    _BasketWindow = new BasketWindow();
    _PersonalAccountWindow = new PersonalAccountWindow();

    connect(this, &HomeWindowBuyeer::openProductsWindow, //Открыть продукты
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openProductsWindow,
            _ProductsWindow_Buyer, &ProductsWindow_Buyer::show);
    connect(_ProductsWindow_Buyer, &ProductsWindow_Buyer::Return,
            this, &ProductsWindow_Buyer::show);
    //------------------
    connect(this, &HomeWindowBuyeer::openHistoryWindow, //Открыть историю покупок
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openHistoryWindow,
            _HistoryWindow, &HistoryWindow::show);
    connect(_HistoryWindow, &HistoryWindow::Return,
            this, &HistoryWindow::show);
    //-------------------
    connect(this, &HomeWindowBuyeer::openBasketWindow, //Открыть окно корзины
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openBasketWindow,
            _BasketWindow, &BasketWindow::show);
    connect(_BasketWindow, &BasketWindow::Return,
            this, &BasketWindow::show);
    //--------------------
    connect(this, &HomeWindowBuyeer::openPersonalAccWindow,
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openPersonalAccWindow,
            _PersonalAccountWindow, &PersonalAccountWindow::show);
    connect(_PersonalAccountWindow, &PersonalAccountWindow::Return,
            this, &PersonalAccountWindow::show);
}

HomeWindowBuyeer::~HomeWindowBuyeer()
{
    delete ui;
}

void HomeWindowBuyeer::on_Products_button_Clicked_clicked()
{
    emit openProductsWindow();
}


void HomeWindowBuyeer::on_Basket_button_Clicked_clicked()
{
    emit openBasketWindow();
}


void HomeWindowBuyeer::on_History_button_Clicked_clicked()
{
    emit openHistoryWindow();
}


void HomeWindowBuyeer::on_PAccount_button_Clicked_clicked()
{
    emit openPersonalAccWindow();
}


void HomeWindowBuyeer::on_exit_clicked()
{
    emit exit();
}

