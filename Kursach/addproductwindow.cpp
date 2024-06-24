#include "addproductwindow.h"
#include "qvalidator.h"
#include "ui_addproductwindow.h"
#include <QMessageBox>

AddProductWindow::AddProductWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProductWindow)
{
    ui->setupUi(this);

    setWindowTitle("Добавление продукта");
    //Валидатор на цифры
    QRegularExpression rx("[0-9]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->Skidka->setValidator(validator);
    ui->Count->setValidator(validator);
    ui->Money->setValidator(validator);

}

AddProductWindow::~AddProductWindow()
{
    delete ui;
}

void AddProductWindow::applyStyleForLabel(int mode)
{
    if(mode == 1)
    {
        ui->label_11->setText("Продукт успешно добавлен!");
        ui->label_11->setStyleSheet("color: navy; font-weight: bold; font-size: 10pt; border: none; background-color: none;");

    }
    else if(mode == 2)
    {
        ui->label_11->setText("Введите корректные данные!");
        ui->label_11->setStyleSheet("color: red; font-weight: bold; font-size: 10pt; border: none; background-color: none;");
    }
    else if(mode == 3)
    {
        ui->label_11->setText("");
    }
}

void AddProductWindow::applyDefaultStyles()
{
    QString Defalut = "color:white; padding-left: 10px;";
    ui->Name->setStyleSheet(Defalut);
    ui->Money->setStyleSheet(Defalut);
    ui->Skidka->setStyleSheet(Defalut);
    ui->Information->setStyleSheet(Defalut);
    ui->Count->setStyleSheet(Defalut);
}


void AddProductWindow::on_Close_button_Clicked_clicked()
{
    applyDefaultStyles();
    applyStyleForLabel(3);
    this->close();
    emit closee();
}
QStringList AddProductWindow::checkInputProduct(QString name, QString information, QString money, QString count, QString skidka)
{
    QStringList errors;
    if (name.trimmed().isEmpty()) {
        errors << "Name";
    }
    if (information.trimmed().isEmpty()) {
        errors << "Information";
    }
    if (money.trimmed().isEmpty() || money[0] == '0') {
        errors << "Money";
    }
    if (count.trimmed().isEmpty()) {
        errors << "Count";
    }
    if (skidka.trimmed().isEmpty()) {
        errors << "Skidka";
    }

    return errors;
}

void AddProductWindow::applyErrorStyles(const QStringList &errors) {
    QString errorStyle = "border: 1px solid red; color:white;";
    for (const QString &error : errors) {
        if (error == "Name" || error == "productNameNotUnique") {
            ui->Name->setStyleSheet(errorStyle);
        } else if (error == "Information") {
            ui->Information->setStyleSheet(errorStyle);
        } else if (error == "Money") {
            ui->Money->setStyleSheet(errorStyle);
        } else if (error == "Count") {
            ui->Count->setStyleSheet(errorStyle);
        } else if (error == "Skidka") {
            ui->Skidka->setStyleSheet(errorStyle);
        }
    }
}



void AddProductWindow::on_AddProduct_button_Clicked_clicked()
{
    QString name = ui->Name->text();
    QString infromation = ui->Information->toPlainText();
    QString money = ui->Money->text();
    QString countString = ui->Count->text();
    //int count =countString.toInt();
    QString skidkaString = ui->Skidka->text();
    //int skidka = skidkaString.toInt();
    QStringList errors = checkInputProduct(name, infromation, money, countString, skidkaString);
    QStringList uniqueErrors = DB.checkProductUnique(name);
    errors.append(uniqueErrors);

    applyDefaultStyles();//стили по умолчанию
    applyStyleForLabel(3);

    if (errors.isEmpty())
    {
        int count =countString.toInt();
        int skidka = skidkaString.toInt();

        if(DB.insertProduct(name, infromation, money, count, skidka) == true)
        {
            //QMessageBox::information(nullptr, "Успех", "Пользователь создан");
            applyStyleForLabel(1);
            applyDefaultStyles();
            emit closee();
        }
        else QMessageBox::warning(nullptr, "Ошибка", "Ошибка при вставке в бд");
    }
    else
    {
        applyStyleForLabel(2);
        applyErrorStyles(errors);
    }


}

