#ifndef ADDPERSON_H
#define ADDPERSON_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AddPerson;
}

class AddPerson : public QDialog
{
    Q_OBJECT

public:
    explicit AddPerson(QWidget *parent = nullptr);
    ~AddPerson();

    void applyErrorStyles(const QStringList &errors);
    void applyDefaultStyles();
    void applyStyleForLabel(int mode);

signals:
   void closee();
    void update();

private slots:
    void on_Close_button_Clicked_clicked();

    void on_AddUser_button_Clicked_clicked();

private:
    Ui::AddPerson *ui;
    DataBase DB;
};

#endif // ADDPERSON_H
