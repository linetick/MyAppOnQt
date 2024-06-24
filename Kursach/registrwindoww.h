#ifndef REGISTRWINDOWW_H
#define REGISTRWINDOWW_H

//#include <QDialog>
#include <QSqlDatabase>
#include "database.h"
#include "QWidget"


namespace Ui {
class RegistrWindoww;
}

class RegistrWindoww : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrWindoww(QWidget *parent = nullptr);
    ~RegistrWindoww();

    bool Check();
    void applyErrorStyles(const QStringList &errors);
    void applyDefaultStyles();

signals:
    void openMainWindow();

private slots:
    void on_Return_button_Clicked_clicked();

    void on_reg_button_Clicked_clicked();

private:
    Ui::RegistrWindoww *ui;
    QSqlDatabase db;
    DataBase DB;
};

#endif // REGISTRWINDOWW_H
