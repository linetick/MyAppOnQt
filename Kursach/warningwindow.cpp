#include "warningwindow.h"
#include "ui_warningwindow.h"

WarningWindow::WarningWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningWindow)
{
    ui->setupUi(this);

    setWindowTitle("Уведомление");
}

WarningWindow::~WarningWindow()
{
    delete ui;
}

void WarningWindow::on_Yes_button_Clicked_clicked()
{
    emit yes();
    this->close();
}


void WarningWindow::on_No_button_Clicked_clicked()
{
      this->close();
}

