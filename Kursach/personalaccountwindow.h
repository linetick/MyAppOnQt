#ifndef PERSONALACCOUNTWINDOW_H
#define PERSONALACCOUNTWINDOW_H

//#include <QDialog>
#include "database.h"
#include "user.h"
#include "QWidget"

namespace Ui {
class PersonalAccountWindow;
}

class PersonalAccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalAccountWindow(QWidget *parent = nullptr);
    ~PersonalAccountWindow();

    void showEvent(QShowEvent *event);
    void updateInfo();
    void applyDefaultStyles();
    void applyDefalutLineEdit();

signals:
    void Return();

private slots:
    void on_Return_button_Clicked_clicked();

    void on_ChangePass_button_Clicked_clicked();

    void on_ChangeAddres_button_clicked_clicked();

    void on_ChangeNumber_button_Clicked_clicked();

private:
    Ui::PersonalAccountWindow *ui;
    DataBase db;
    QString password;
};

#endif // PERSONALACCOUNTWINDOW_H
