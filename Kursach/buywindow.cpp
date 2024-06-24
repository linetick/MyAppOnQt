#include "buywindow.h"
#include "ui_buywindow.h"
#include <QMessageBox>

BuyWindow::BuyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyWindow)
{
    ui->setupUi(this);

    setWindowTitle("Покупка");
}

BuyWindow::~BuyWindow()
{
    delete ui;
}

void BuyWindow::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    ui->label_9->setText(db.takeAddres());
}

void BuyWindow::on_Return_button_Clicked_clicked()
{
    this->close();
}

void BuyWindow::takeCountMoney(QString a)
{
    ui->label_8->setText(a);
}


void BuyWindow::on_Buy_button_Clicked_clicked()
{
    if(db.addDelivery(ui->label_8->text().toInt()) == true)
    {
        Basket::clearCart();
        emit complete();
        QMessageBox::information(this, "Успех", "Ваша доставка находится в обработке");
        this->close();
    }
}

