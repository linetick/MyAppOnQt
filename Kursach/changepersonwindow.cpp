#include "changepersonwindow.h"
#include "ui_changepersonwindow.h"
#include "QMessageBox"

ChangePersonWindow::ChangePersonWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePersonWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);

    setWindowTitle("Изменение пользователя");

    //Валидатор на номер
    QRegularExpression rx("[0-9+]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->Phone->setValidator(validator);
    //Валидатор на имя отчество и тп
    QRegularExpression rxx("[А-Яа-яЁё]*");
    QValidator *validatorr = new QRegularExpressionValidator(rxx, this);
    ui->FName->setValidator(validatorr);
    ui->MName->setValidator(validatorr);
    ui->LName->setValidator(validatorr);
}

ChangePersonWindow::~ChangePersonWindow()
{
    delete ui;
}

void ChangePersonWindow::applyStyleForLabel(int mode)
{
    if(mode == 1)
    {
        ui->warning->setText("Пользователь успешно изменен!");
        ui->warning->setStyleSheet("color: navy; font-weight: bold; font-size: 10pt; border: none; background-color: none;");

    }
    else if(mode == 2)
    {
        ui->warning->setText("Введите корректные данные!");
        ui->warning->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
    }
    else if(mode == 3)
    {
        ui->warning->setText("");
    }
}

bool ChangePersonWindow::checkPhone(QString phone)
{
    if((phone[0] == '+' || phone[0] == '-' )&& phone.length() ==  12) return true;
    if(phone[0] != '+' && phone.length() == 10) return true;
    return false;
}

QStringList ChangePersonWindow::checkInput(const QString& Name, const QString& LastName,
                                 const QString& MiddleName, const QString& Address,
                                 const QString& NumberPhone, const QString& login, const QString& password, const QString& Role) {
    QStringList errors;
    if (Name.trimmed().isEmpty()) {
        errors << "Name";
    }
    if (LastName.trimmed().isEmpty()) {
        errors << "LastName";
    }
    if (MiddleName.trimmed().isEmpty()) {
        errors << "MiddleName";
    }
    if (NumberPhone.trimmed().isEmpty() || checkPhone(NumberPhone)== false) {
        errors << "NumberPhone";
    }
    if (Address.trimmed().isEmpty() && Role == "Покупатель") {
        errors << "Address";
    }
    if (login.trimmed().isEmpty()) {
        errors << "login";
    }
    if (password.trimmed().isEmpty() && _password == true) {
        errors << "password";
    }
    return errors;
}

void ChangePersonWindow::applyErrorStyles(const QStringList &errors) {
    QString errorStyle = "border: 1px solid red; color:white;";
    for (const QString &error : errors) {
        if (error == "Name") {
            ui->FName->setStyleSheet(errorStyle);
        } else if (error == "LastName") {
            ui->LName->setStyleSheet(errorStyle);
        }
         else if (error == "NumberPhone" || error == "phoneNotUnique") {
            ui->Phone->setStyleSheet(errorStyle);
        } else if (error == "Address") {
            ui->Adres->setStyleSheet(errorStyle);
        } else if (error == "login" || error == "loginNotUnique") {
            ui->login->setStyleSheet(errorStyle);
        } else if (error == "password") {
            ui->password->setStyleSheet(errorStyle);
        }
    }
}

void ChangePersonWindow::applyDefaultStyles()
{
    QString Defalut = "color:white; padding-left: 10px;";
    ui->FName->setStyleSheet(Defalut);
    ui->LName->setStyleSheet(Defalut);
    ui->MName->setStyleSheet(Defalut);
    ui->Phone->setStyleSheet(Defalut);
    ui->Adres->setStyleSheet(Defalut);
    ui->login->setStyleSheet(Defalut);
    ui->password->setStyleSheet(Defalut);
   //ui->Role->setStyleSheet(Defalut);


}

void ChangePersonWindow::applyDefaultStyleButton()
{
    _LName = false;
    _FName = false;
    _MName = false;
    _Phone = false;
    _Adres = false;
    _login = false;
    _password = false;
    ui->ChangeLName_button_Clicked->setText("Изменить фамилию");
    ui->ChangeFName_button_Clicked->setText("Изменить имя");
    ui->ChangeMName_button_Clicked->setText("Изменить отчество");
    ui->ChangePhone_button_Clicked->setText("Изменить телефон");
    ui->ChangeAdres_button_Clicked->setText("Изменить адрес");
    ui->ChangeLogin_button_Clicked->setText("Изменить логин");
    ui->ChangePassword_button_Clicked->setText("Изменить пароль");
}

void ChangePersonWindow::on_Close_button_Clicked_clicked()
{
    this->close();
}


void ChangePersonWindow::on_ChangePerson_button_Clicked_clicked()
{
    if(ui->Phone->text().length() == 12)
    {
        ui->Phone->text().remove(0, 2);
    }
    QStringList errors = checkInput(ui->FName->text(), ui->LName->text(),
                                   ui->MName->text(), ui->Adres->text(),
                                   ui->Phone->text(), ui->login->text(), ui->password->text(), ui->Role->currentText());
    QStringList uniqueErrors;
    if(ui->Phone->text()!= Phone && ui->login->text() != login)  uniqueErrors = db.checkUnique(login, ui->Phone->text());

    if(ui->Phone->text()!= Phone) uniqueErrors = db.checkUnique(login, ui->Phone->text());
    if(ui->login->text() != login) uniqueErrors = db.checkUnique(login, ui->Phone->text());
    errors.append(uniqueErrors);

    applyDefaultStyles();//стили по умолчанию
    applyStyleForLabel(3);

    if (errors.isEmpty())
    {
        QString a;
        if(_password == true) a = ui->password->text();
        if(_password == false) a = password;
//        if(ui->FName->text() == FName && ui->LName->text() == LName && ui->MName->text() == MName && ui->Phone->text() == Phone,
//                               ui->Adres->text() == Adres && ui->login->text() == login, a == password && ui->Role->currentText() == Role)
//        {
//            applyDefaultStyles();
//            applyStyleForLabel(3);
//            return;
//        }
        if(db.updatePerson(ID, ui->FName->text(), ui->LName->text(), ui->MName->text(), ui->Phone->text(),
                               ui->Adres->text(), ui->login->text(), a, ui->Role->currentText()) == true)
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

void ChangePersonWindow::takeID(int a)
{
    ID = a;
    QSqlRecord data = db.getPersonByID(a);
    LName = data.value(1).toString();
    FName = data.value(2).toString();
    MName = data.value(3).toString();
    Phone = data.value(4).toString();
    Adres = data.value(5).toString();
    login = data.value(6).toString();
    password = data.value(7).toString();;      //data.value(7).toString();
    Role = data.value(8).toString();

    ui->LName->setText(LName);
    ui->FName->setText(FName);
    ui->MName->setText(MName);
    ui->Phone->setText(Phone);
    ui->Adres->setText(Adres);
    ui->login->setText(login);
    ui->password->setPlaceholderText("Тут есть пароль");

    ui->FName->setReadOnly(true);
    ui->LName->setReadOnly(true);
    ui->MName->setReadOnly(true);
    ui->Phone->setReadOnly(true);
    ui->Adres->setReadOnly(true);
    ui->login->setReadOnly(true);
    ui->password->setReadOnly(true);

    applyDefaultStyles();
    applyDefaultStyleButton();
    applyStyleForLabel(3);
}


void ChangePersonWindow::on_ChangeLName_button_Clicked_clicked()
{
    if(_LName == false)
    {
        _LName = true;
        ui->ChangeLName_button_Clicked->setText("Отменить");
        ui->LName->setReadOnly(false);
    }
    else
    {
        _LName = false;
        ui->ChangeLName_button_Clicked->setText("Изменить фамилию");
        ui->LName->setText(LName);
        ui->LName->setReadOnly(true);
    }
}


void ChangePersonWindow::on_ChangeFName_button_Clicked_clicked()
{
    if(_FName == false)
    {
        _FName = true;
        ui->ChangeFName_button_Clicked->setText("Отменить");
        ui->FName->setReadOnly(false);
    }
    else
    {
        _FName = false;
        ui->ChangeFName_button_Clicked->setText("Изменить имя");
        ui->FName->setText(FName);
        ui->FName->setReadOnly(true);
    }
}


void ChangePersonWindow::on_ChangeMName_button_Clicked_clicked()
{
    if(_MName == false)
    {
        _MName = true;
        ui->ChangeMName_button_Clicked->setText("Отменить");
        ui->MName->setReadOnly(false);
    }
    else
    {
        _MName = false;
        ui->ChangeMName_button_Clicked->setText("Изменить отчество");
        ui->MName->setText(MName);
        ui->MName->setReadOnly(true);
    }
}


void ChangePersonWindow::on_ChangePhone_button_Clicked_clicked()
{
    if(_Phone == false)
    {
        _Phone = true;
        ui->ChangePhone_button_Clicked->setText("Отменить");
        ui->Phone->setReadOnly(false);
    }
    else
    {
        _Phone = false;
        ui->ChangePhone_button_Clicked->setText("Изменить телефон");
        ui->Phone->setText(Phone);
        ui->Phone->setReadOnly(true);
    }
}


void ChangePersonWindow::on_ChangeAdres_button_Clicked_clicked()
{
    if(_Adres == false)
    {
        _Adres = true;
        ui->ChangeAdres_button_Clicked->setText("Отменить");
        ui->Adres->setReadOnly(false);
    }
    else
    {
        _Adres = false;
        ui->ChangeAdres_button_Clicked->setText("Изменить адрес");
        ui->Adres->setText(Adres);
        ui->Adres->setReadOnly(true);
    }
}


void ChangePersonWindow::on_ChangeLogin_button_Clicked_clicked()
{
    if(_login == false)
    {
        _login = true;
        ui->ChangeLogin_button_Clicked->setText("Отменить");
        ui->login->setReadOnly(false);
    }
    else
    {
        _login = false;
        ui->ChangeLogin_button_Clicked->setText("Изменить логин");
        ui->login->setText(login);
        ui->login->setReadOnly(true);
    }
}


void ChangePersonWindow::on_ChangePassword_button_Clicked_clicked()
{
    if(_password == false)
    {
        _password = true;
        ui->ChangePassword_button_Clicked->setText("Отменить");
        ui->password->setReadOnly(false);
    }
    else
    {
        _password = false;
        ui->ChangePassword_button_Clicked->setText("Изменить пароль");
        ui->password->setText("");
        ui->password->setPlaceholderText(password);
        ui->password->setReadOnly(true);
    }
}

