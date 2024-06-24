#include "registrwindoww.h"
#include "ui_registrwindoww.h"
#include "QLineEdit"
#include <QIntValidator>
#include <QMessageBox>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

RegistrWindoww::RegistrWindoww(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrWindoww)
{
    ui->setupUi(this);

    setWindowTitle("Регистрация");

    ui->lineEdit_7->setEchoMode(QLineEdit::Password);// Валидатор на пароль
    //Валидатор на номер
    QRegularExpression rx("[0-9+]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_4->setValidator(validator);
    //Валидатор на имя отчество и тп
    QRegularExpression rxx("[А-Яа-яЁё]*");
    QValidator *validatorr = new QRegularExpressionValidator(rxx, this);
    ui->lineEdit->setValidator(validatorr);
    ui->lineEdit_2->setValidator(validatorr);
    ui->lineEdit_3->setValidator(validatorr);
}

RegistrWindoww::~RegistrWindoww()
{
    delete ui;
}

void RegistrWindoww::applyErrorStyles(const QStringList &errors) {
    QString errorStyle = "border: 1px solid red; color:white;";
    for (const QString &error : errors) {
        if (error == "Name") {
            ui->lineEdit->setStyleSheet(errorStyle);
        } else if (error == "LastName") {
            ui->lineEdit_2->setStyleSheet(errorStyle);
        } else if (error == "MiddleName") {
            ui->lineEdit_3->setStyleSheet(errorStyle);
        } else if (error == "NumberPhone" || error == "phoneNotUnique") {
            ui->lineEdit_4->setStyleSheet(errorStyle);
        } else if (error == "Address") {
            ui->lineEdit_5->setStyleSheet(errorStyle);
        } else if (error == "login" || error == "loginNotUnique") {
            ui->lineEdit_6->setStyleSheet(errorStyle);
        } else if (error == "password") {
            ui->lineEdit_7->setStyleSheet(errorStyle);
        }
    }
}

void RegistrWindoww::applyDefaultStyles()
{
    QString Defalut = "color:white; padding-left: 10px;";
    ui->lineEdit->setStyleSheet(Defalut);
    ui->lineEdit_2->setStyleSheet(Defalut);
    ui->lineEdit_3->setStyleSheet(Defalut);
    ui->lineEdit_4->setStyleSheet(Defalut);
    ui->lineEdit_5->setStyleSheet(Defalut);
    ui->lineEdit_6->setStyleSheet(Defalut);
    ui->lineEdit_7->setStyleSheet(Defalut);
}

void RegistrWindoww::on_Return_button_Clicked_clicked()
{
    this->close();
    emit openMainWindow();
}

void RegistrWindoww::on_reg_button_Clicked_clicked()
{
    QString Name = ui->lineEdit->text();
    QString LastName = ui->lineEdit_2->text();
    QString MiddleName = ui->lineEdit_3->text();
    QString NumberPhone = ui->lineEdit_4->text();
    if(NumberPhone.length() == 12)
    {
        NumberPhone.remove(0, 2);
    }
    QString Address = ui->lineEdit_5->text();
    QString login = ui->lineEdit_6->text();
    QString password = ui->lineEdit_7->text();

    //Проверка ошибок
    QStringList errors = DB.checkInput(Name, LastName, MiddleName, Address, NumberPhone, login, password, "Покупатель");
    QStringList uniqueErrors = DB.checkUnique(login, NumberPhone);
    errors.append(uniqueErrors);

    applyDefaultStyles();//стили по умолчанию

    if (errors.isEmpty())
    {
        if(DB.insertNewPerson(Name, LastName, MiddleName, NumberPhone, Address, login, password, "Покупатель") == true)
        {
            QMessageBox::information(nullptr, "Успех", "Вы успешно зарегистрировались");
            this->close();
            emit openMainWindow();
        }
        //else QMessageBox::warning(nullptr, "Ошибка", "Ошибка при вставке в бд");
    }
    else
    {
        applyErrorStyles(errors);
    }
}

