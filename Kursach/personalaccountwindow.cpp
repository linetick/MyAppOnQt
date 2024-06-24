#include "personalaccountwindow.h"
#include "qvalidator.h"
#include "ui_personalaccountwindow.h"
#include "QMessageBox"

PersonalAccountWindow::PersonalAccountWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalAccountWindow)
{
    ui->setupUi(this);

    setWindowTitle("Личный кабинет");

    ui->oldPassword->setEchoMode(QLineEdit::Password);
    ui->NewPassword->setEchoMode(QLineEdit::Password);
    ui->NewPassword2->setEchoMode(QLineEdit::Password);
    //Валидатор на номер
    QRegularExpression rx("[0-9+]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->newPhone->setValidator(validator);
}

PersonalAccountWindow::~PersonalAccountWindow()
{
    delete ui;
}

void PersonalAccountWindow::updateInfo()
{
    User* session = User::getInstance();
    QSqlRecord data = db.getPersonByID(session->getUserId());
    ui->FMLName->setText(data.value(1).toString()+ " " + data.value(2).toString()+ " " + data.value(3).toString());
    ui->Phone->setText(data.value(4).toString());
    ui->Adres->setText(data.value(5).toString());
    password = data.value(7).toString();
}

void PersonalAccountWindow::applyDefaultStyles()
{
    QString Defalut = "color:white; padding-left: 10px;";
    ui->PassInfo->setStyleSheet(Defalut);
    ui->AddresInfo->setStyleSheet(Defalut);
    ui->PhoneInfo->setStyleSheet(Defalut);
    ui->PassInfo->setText("");
    ui->AddresInfo->setText("");
    ui->PhoneInfo->setText("");
}

void PersonalAccountWindow::applyDefalutLineEdit()
{
    ui->oldPassword->setText("");
    ui->NewPassword->setText("");
    ui->NewPassword2->setText("");
    ui->NewAddres->setText("");
    ui->newPhone->setText("");
}

void PersonalAccountWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    updateInfo();
    applyDefalutLineEdit();
    applyDefaultStyles();

}

void PersonalAccountWindow::on_Return_button_Clicked_clicked()
{
    this->close();
    emit Return();
}


void PersonalAccountWindow::on_ChangePass_button_Clicked_clicked()
{
    if(ui->oldPassword->text() != password && ui->NewPassword->text() == ui->NewPassword2->text())
    {
        User* session = User::getInstance();
        if(db.changePassword(session->getUserId(), ui->NewPassword2->text()) == true)
        {
            ui->PassInfo->setText("Пароль успешно изменён!");
            ui->PassInfo->setStyleSheet("color: navy; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
        }
        else QMessageBox::warning(nullptr, "Ошибка", "Ошибка при вставке в бд");
    }
    else
    {
        ui->PassInfo->setText("Пароль совпадает с настоящим");
        ui->PassInfo->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
    }
}


void PersonalAccountWindow::on_ChangeAddres_button_clicked_clicked()
{
    if(ui->NewAddres->text() != ui->Adres->text())
    {
        User* session = User::getInstance();
        if(db.changeAddres(session->getUserId(), ui->NewAddres->text()) == true)
        {
            ui->AddresInfo->setText("Адрес успешно изменён!");
            ui->AddresInfo->setStyleSheet("color: navy; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
            updateInfo();
        }
        else QMessageBox::warning(nullptr, "Ошибка", "Ошибка при вставке в бд");
    }
    else
    {
        ui->AddresInfo->setText("Адрес совпадает с настоящим");
        ui->AddresInfo->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
    }

}


void PersonalAccountWindow::on_ChangeNumber_button_Clicked_clicked()
{
    if(ui->newPhone->text().length() == 12)
    {
        ui->newPhone->text().remove(0, 2);
    }
    if(ui->newPhone->text().length() == 10)
    {
        if(ui->newPhone->text() != ui->Phone->text())
        {
            bool flag = true;
            QStringList errors = db.checkUnique("1", ui->newPhone->text());
            for (const QString &error : errors)
            {
                if(error == "phoneNotUnique")
                {
                    ui->PhoneInfo->setText("Данный номер уже существует!");
                    ui->PhoneInfo->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
                    flag = false;
                }
            }
            User* session = User::getInstance();
            if(flag == true)
            {
                if(db.changePhone(session->getUserId(), ui->newPhone->text()) == true)
                {
                    ui->PhoneInfo->setText("Номер успешно изменён!");
                    ui->PhoneInfo->setStyleSheet("color: navy; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
                    updateInfo();
                }
                else QMessageBox::warning(nullptr, "Ошибка", "Ошибка при вставке в бд");
            }
        }
        else
        {
            ui->PhoneInfo->setText("Номер совпадает с фактическим!");
            ui->PhoneInfo->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
        }
    }
    else
    {
        ui->PhoneInfo->setText("Введите корректный номер!");
        ui->PhoneInfo->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
    }
}

