#ifndef PERSONSWINDOWADMIN_H
#define PERSONSWINDOWADMIN_H

//#include <QDialog>
#include "addperson.h"
#include "addperson.h"
#include "qsortfilterproxymodel.h"
#include "warningwindow.h"
#include "changepersonwindow.h"
#include "database.h"
#include "QWidget"

namespace Ui {
class PersonsWindowAdmin;
}

class PersonsWindowAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit PersonsWindowAdmin(QWidget *parent = nullptr);
    ~PersonsWindowAdmin();

    int takeID();
    void showEvent(QShowEvent *event);


signals:
    void Return();
    void openAddPerson();
    void openWarning();
    void openChangePerson();
    void giveInformationChange(int);

private slots:
    void on_Return_button_Clicked_clicked();
    void on_AddPerson_button_Clicked_clicked();

    void on_deletePerson_button_Clicked_clicked();

    void on_changePersons_button_Clicked_clicked();

public slots:
    void DeletePerson();
    void updatePersons();

private:
    Ui::PersonsWindowAdmin *ui;
    AddPerson *_AddPerson;
    WarningWindow *_WarningWindow;
    ChangePersonWindow *_ChangePersonWindow;
    DataBase db;
    int ID;
    QSortFilterProxyModel *proxyModel;
};

#endif // PERSONSWINDOWADMIN_H
