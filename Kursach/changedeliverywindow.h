#ifndef CHANGEDELIVERYWINDOW_H
#define CHANGEDELIVERYWINDOW_H

#include <QDialog>
#include "database.h"
#include  <QDate>

namespace Ui {
class ChangeDeliveryWindow;
}

class ChangeDeliveryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDeliveryWindow(QWidget *parent = nullptr);
    ~ChangeDeliveryWindow();

    void applyDefaultStyle();
    bool checkInput(QString takeAddres, QDate _takeNewDate);

private slots:
    void on_ChangeOrder_button_Clicked_clicked();

    void on_Close_button_Clicked_clicked();

    void on_ChangeAddres_button_Clicked_clicked();

    void on_ChangeEndDate_button_Clicked_clicked();

signals:
    void reset();

public slots:
    void takeID(int a);

private:
    Ui::ChangeDeliveryWindow *ui;
    DataBase db;
    QDate _dateBuy;
    QDate _endDate;
    QString _Addres;
    bool ChangeAddres = false;
    bool ChangeEndDate = false;
    int ID;
};

#endif // CHANGEDELIVERYWINDOW_H
