#ifndef CHANGEPERSONWINDOW_H
#define CHANGEPERSONWINDOW_H

#include "database.h"
#include <QDialog>

namespace Ui {
class ChangePersonWindow;
}

class ChangePersonWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePersonWindow(QWidget *parent = nullptr);
    ~ChangePersonWindow();

    void applyDefaultStyles();
    void applyDefaultStyleButton();
    void applyErrorStyles(const QStringList &errors);
    QStringList checkInput(const QString& Name, const QString& LastName,
                           const QString& MiddleName, const QString& Address,
                           const QString& NumberPhone, const QString& login, const QString& password, const QString& Role);
    bool checkPhone(QString phone);
    void applyStyleForLabel(int mode);

private slots:
    void on_Close_button_Clicked_clicked();

    void on_ChangePerson_button_Clicked_clicked();

    void on_ChangeLName_button_Clicked_clicked();

    void on_ChangeFName_button_Clicked_clicked();

    void on_ChangeMName_button_Clicked_clicked();

    void on_ChangePhone_button_Clicked_clicked();

    void on_ChangeAdres_button_Clicked_clicked();

    void on_ChangeLogin_button_Clicked_clicked();

    void on_ChangePassword_button_Clicked_clicked();

public slots:
    void takeID(int a);

signals:
    void update();

private:
    Ui::ChangePersonWindow *ui;
    DataBase db;
    int ID;
    QString LName;
    QString FName;
    QString MName;
    QString Phone;
    QString Adres;
    QString login;
    QString password;
    QString Role;

    bool _LName;
    bool _FName;
    bool _MName;
    bool _Phone;
    bool _Adres;
    bool _login;
    bool _password;
    bool _Role;
};

#endif // CHANGEPERSONWINDOW_H
