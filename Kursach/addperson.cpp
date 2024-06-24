#include "addperson.h"
#include "ui_addperson.h"
#include "QMessageBox"

AddPerson::AddPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPerson)
{
    ui->setupUi(this);

    setWindowTitle("Добавление пользователя");
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

AddPerson::~AddPerson()
{
    delete ui;
}

void AddPerson::on_Close_button_Clicked_clicked()
{
    applyDefaultStyles();
    applyStyleForLabel(3);
    this->close();    
}

void AddPerson::applyErrorStyles(const QStringList &errors) {
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

void AddPerson::applyStyleForLabel(int mode)
{
    if(mode == 1)
    {
        ui->label_5->setText("Пользователь успешно создан!");
        ui->label_5->setStyleSheet("color: navy; font-weight: bold; font-size: 10pt; border: none; background-color: none;");

    }
    else if(mode == 2)
    {
        ui->label_5->setText("Введите корректные данные!");
        ui->label_5->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
    }
    else if(mode == 3)
    {
        ui->label_5->setText("");
    }
}

void AddPerson::applyDefaultStyles()
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

void AddPerson::on_AddUser_button_Clicked_clicked()
{
    QString Name = ui->lineEdit->text();
    QString LastName = ui->lineEdit_2->text();
    QString MiddleName = ui->lineEdit_3->text();
    QString NumberPhone = ui->lineEdit_4->text();
    if(NumberPhone.length() == 12 && NumberPhone[0] == '+')
    {
        NumberPhone.remove(0, 2);
    }
    QString Address = ui->lineEdit_5->text();
    QString login = ui->lineEdit_6->text();
    QString password = ui->lineEdit_7->text();
    QString Role = ui->comboBox->currentText();
    QStringList errors = DB.checkInput(Name, LastName, MiddleName, Address, NumberPhone, login, password, Role);
    QStringList uniqueErrors = DB.checkUnique(login, NumberPhone);
    errors.append(uniqueErrors);

    applyDefaultStyles();//стили по умолчанию
    applyStyleForLabel(3);

    if (errors.isEmpty())
    {
        if(DB.insertNewPerson(Name, LastName, MiddleName, NumberPhone, Address, login, password, Role) == true)
        {
            //QMessageBox::information(nullptr, "Успех", "Пользователь создан");
            applyStyleForLabel(1);
            applyDefaultStyles();
            emit update();
        }
        else QMessageBox::warning(nullptr, "Ошибка", "Ошибка при вставке в бд");
    }
    else
    {
        applyStyleForLabel(2);
        applyErrorStyles(errors);
    }
}

