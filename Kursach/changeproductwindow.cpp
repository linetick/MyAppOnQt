#include "changeproductwindow.h"
#include "qregularexpression.h"
#include "qvalidator.h"
#include "ui_changeproductwindow.h"

ChangeProductWindow::ChangeProductWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeProductWindow)
{
    ui->setupUi(this);

    setWindowTitle("Изменение продукта");

    //Валидатор на цифры
    QRegularExpression rx("[0-9]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->Discount->setValidator(validator);
    ui->Count->setValidator(validator);
    ui->Money->setValidator(validator);
}

ChangeProductWindow::~ChangeProductWindow()
{
    delete ui;
}

QStringList ChangeProductWindow::checkInputProduct(QString name, QString information, QString price, QString count, QString discount)
{
    QStringList errors;
    if (name.trimmed().isEmpty()) {
        errors << "Name";
    }
    if (information.trimmed().isEmpty()) {
        errors << "Information";
    }
    if (price.trimmed().isEmpty() || price[0] == '0') {
        errors << "Money";
    }
    if (count.trimmed().isEmpty()) {
        errors << "Count";
    }
    if (discount.trimmed().isEmpty()) {
        errors << "Skidka";
    }

    return errors;
}

void ChangeProductWindow::applyStyleForLabel(int mode)
{
    if(mode == 1)
    {
        ui->label_11->setText("Продукт успешно изменён");
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

void ChangeProductWindow::applyDefaultStyles()
{
    QString Defalut = "color:white; padding-left: 10px;";
    ui->Name->setStyleSheet(Defalut);
    ui->Money->setStyleSheet(Defalut);
    ui->Discount->setStyleSheet(Defalut);
    ui->Information->setStyleSheet(Defalut);
    ui->Count->setStyleSheet(Defalut);
}

void ChangeProductWindow::takeID(int a)
{
    ID = a;
    QSqlRecord data = db.getProductById(a);
    Name = data.value(1).toString();
    Information = data.value(2).toString();
    Price = data.value(3).toInt();
    Quantity = data.value(4).toInt();
    Discount = data.value(5).toInt();

    ui->Name->setText(Name);
    ui->Information->setText(Information);
    ui->Money->setText(QString::number(Price));
    ui->Count->setText(QString::number(Quantity));
    ui->Discount->setText(QString::number(Discount));

    ui->Name->setReadOnly(true);
    ui->Information->setReadOnly(true);
    ui->Money->setReadOnly(true);
    ui->Count->setReadOnly(true);
    ui->Discount->setReadOnly(true);
    applyDefaultStyles();
    applyDefaultStyleButton();
    ui->Information->setText("");

}

void ChangeProductWindow::applyDefaultStyleButton()
{
    checkName = false;
    checkInformation = false;
    checkPrice = false;
    checkQuantity = false;
    checkDiscount = false;
    ui->ChangeName_button_Clicked->setText("Изменить название");
    ui->ChangeInformation_button_Clicked->setText("Изменить информацию");
    ui->ChangePrice_button_Clicked->setText("Изменить цену");
    ui->ChangeQuantity_button_Clicked->setText("Изменить количество");
    ui->ChangeDiscount_button_Clicked->setText("Изменить скидку");
}

void ChangeProductWindow::applyErrorStyles(const QStringList &errors) {
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
            ui->Discount->setStyleSheet(errorStyle);
        }
    }
}

void ChangeProductWindow::on_Close_button_Clicked_clicked()
{
    this->close();
}


void ChangeProductWindow::on_ChangeName_button_Clicked_clicked()
{
    if(checkName == false)
    {
        checkName = true;
        ui->ChangeName_button_Clicked->setText("Отменить");
        ui->Name->setReadOnly(false);
    }
    else
    {
        checkName = false;
        ui->ChangeName_button_Clicked->setText("Изменить название");
        ui->Name->setText(Name);
        ui->Name->setReadOnly(true);
    }
}


void ChangeProductWindow::on_ChangeInformation_button_Clicked_clicked()
{
    if(checkInformation == false)
    {
        checkInformation = true;
        ui->ChangeInformation_button_Clicked->setText("Отменить");
        ui->Information->setReadOnly(false);
    }
    else
    {
        checkInformation = false;
        ui->ChangeInformation_button_Clicked->setText("Изменить информацию");
        ui->Information->setText(Information);
        ui->Information->setReadOnly(true);
    }
}


void ChangeProductWindow::on_ChangePrice_button_Clicked_clicked()
{
    if(checkPrice == false)
    {
        checkPrice = true;
        ui->ChangePrice_button_Clicked->setText("Отменить");
        ui->Money->setReadOnly(false);
    }
    else
    {
        checkPrice = false;
        ui->ChangePrice_button_Clicked->setText("Изменить цену");
        ui->Money->setText(QString::number(Price));
        ui->Money->setReadOnly(true);
    }
}


void ChangeProductWindow::on_ChangeQuantity_button_Clicked_clicked()
{
    if(checkQuantity == false)
    {
        checkQuantity = true;
        ui->ChangeQuantity_button_Clicked->setText("Отменить");
        ui->Count->setReadOnly(false);
    }
    else
    {
        checkQuantity = false;
        ui->ChangeQuantity_button_Clicked->setText("Изменить количество");
        ui->Count->setText(QString::number(Quantity));
        ui->Count->setReadOnly(true);
    }
}



void ChangeProductWindow::on_ChangeDiscount_button_Clicked_clicked()
{
    if(checkDiscount == false)
    {
        checkDiscount = true;
        ui->ChangeDiscount_button_Clicked->setText("Отменить");
        ui->Discount->setReadOnly(false);
    }
    else
    {
        checkDiscount = false;
        ui->ChangeDiscount_button_Clicked->setText("Изменить скидку");
        ui->Discount->setText(QString::number(Discount));
        ui->Discount->setReadOnly(true);
    }
}


void ChangeProductWindow::on_ChangeProduct_button_Clicked_clicked()
{
    QStringList errors = checkInputProduct(ui->Name->text(), ui->Information->toPlainText(), ui->Money->text(), ui->Count->text(), ui->Discount->text());
    QStringList uniqueErrors;
    if(ui->Name->text() != Name) uniqueErrors = db.checkProductUnique(ui->Name->text());
    errors.append(uniqueErrors);

    applyDefaultStyles();//стили по умолчанию
    applyStyleForLabel(3);

    if (errors.isEmpty())
    {
//        if(ui->Name->text() == Name && ui->Information->toPlainText() == Information && ui->Money->text().toInt() == Price && ui->Count->text().toInt() == Quantity && ui->Discount->text().toInt() == Discount)
//        {
//            applyStyleForLabel(3);
//            applyDefaultStyles();
//            return;
//        }
        if(db.updateProduct(ID ,ui->Name->text(), ui->Information->toPlainText(), ui->Money->text(), ui->Count->text().toInt(), ui->Discount->text().toInt()) == true)
        {
            //QMessageBox::information(nullptr, "Успех", "Пользователь создан");
            applyStyleForLabel(1);
            applyDefaultStyles();
            emit update();
        }
    }
    else
    {
        applyStyleForLabel(2);
        applyErrorStyles(errors);
    }
}

