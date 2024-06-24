#include "changedeliverywindow.h"
#include "ui_changedeliverywindow.h"

ChangeDeliveryWindow::ChangeDeliveryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDeliveryWindow)
{
    ui->setupUi(this);

    setWindowTitle("Изменение доставки");
}

ChangeDeliveryWindow::~ChangeDeliveryWindow()
{
    delete ui;
}

void ChangeDeliveryWindow::applyDefaultStyle()
{
    ui->Addres->setStyleSheet("color:white; padding-left: 10px;");
    ui->Addres->setStyleSheet("color:white; padding-left: 10px;");
    //ui->Phone->setStyleSheet("color:white; padding-left: 10px;");
    ui->AddressError->setText("");
    ui->DateError->setText("");
    ui->label_5->setText("");
}

bool ChangeDeliveryWindow::checkInput(QString takeAddres, QDate _takeNewDate)
{
    QStringList errors;
    if(_dateBuy > _takeNewDate)
    {
        errors << "Date";
    }
    if(takeAddres.trimmed().isEmpty())
    {
        errors << "Adres_empty";
    }
    if(errors.empty()) return true;
    QString errorStyle = "border: 1px solid red; color:white;";
    for(const QString &error : errors)
    {
        if(error == "Date")
        {
            ui->EndDate->setStyleSheet(errorStyle);
            ui->DateError->setText("Дата доставки не может быть раньше даты покупки!");
        }
        else if(error == "Adres_empty")
        {
            ui->Addres->setStyleSheet(errorStyle);
            ui->AddressError->setText("Адрес не должен быть пустым!");
        }
    }
    return false;
}

void ChangeDeliveryWindow::on_ChangeOrder_button_Clicked_clicked()
{
    QString takeAddres = ui->Addres->text();
    QDate _takeNewDate = ui->EndDate->date();
    QString takeNewDate = _takeNewDate.toString("dd.MM.yyyy");
    applyDefaultStyle();
    if(takeAddres.trimmed().isEmpty())
    {
        ui->Addres->setStyleSheet("border: 1px solid red; color:white;");
        ui->AddressError->setStyleSheet("Введите корректный адрес");
    }
//    if(takeNewDate.trimmed().isEmpty())
//    {
//        //ui->EndDate->setStyleSheet("border: 1px solid red; color:white;");
//        ui->DateError->setStyleSheet("Введите корректную дату");
//    }
    else
    {
        if(db.updateDeliveryDetails(ID, takeAddres, takeNewDate, ui->Status->currentText()) == true)
        {
            applyDefaultStyle();
            ui->label_5->setText("Доставка успешно изменена!");
            emit reset();
        }
    }
}


void ChangeDeliveryWindow::on_Close_button_Clicked_clicked()
{
    this->close();
}

void ChangeDeliveryWindow::takeID(int a)
{
    ID = a;
   QStringList details = db.getDeliveryById(a);
   ui->FirstName->setText(details.at(0));
   ui->LastName->setText(details.at(1));
   ui->MiddleName->setText(details.at(2));
   ui->Phone->setText(details.at(3));
   ui->Addres->setText(details.at(4)); //adsadasd
   _Addres = details.at(4);
   //ui->Status
   ui->DateBuy->setText(details.at(6));
   _dateBuy = QDate::fromString(details.at(6), "dd.MM.yyyy");
   ui->EndDate->setDate(QDate::fromString(details.at(7), "dd.MM.yyyy"));
   _endDate = QDate::fromString(details.at(7), "dd.MM.yyyy");
   //_endDate = __endDate.toString("dd.MM.yyyy");

   ui->Addres->setReadOnly(true);
   ui->EndDate->setReadOnly(true);
   applyDefaultStyle();
}


void ChangeDeliveryWindow::on_ChangeAddres_button_Clicked_clicked()
{
   if(ChangeAddres == false)
    {
        ChangeAddres = true;
        ui->ChangeAddres_button_Clicked->setText("Отменить");
        ui->Addres->setReadOnly(false);
    }
   else
   {
        ChangeAddres = false;
        ui->ChangeAddres_button_Clicked->setText("Изменить адрес");
        ui->Addres->setText(_Addres);
        ui->Addres->setReadOnly(true);
   }
}


void ChangeDeliveryWindow::on_ChangeEndDate_button_Clicked_clicked()
{
   if(ChangeEndDate == false)
   {
        ChangeEndDate = true;
        ui->ChangeEndDate_button_Clicked->setText("Отменить");
        ui->EndDate->setReadOnly(false);
   }
   else
   {
        ChangeEndDate = false;
        ui->ChangeEndDate_button_Clicked->setText("Изменить дату");
        ui->EndDate->setDate(_endDate);
        ui->EndDate->setReadOnly(true);
   }
}

