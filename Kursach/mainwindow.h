#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "homewindowadmin.h"
#include "homewindowbuyeer.h"
#include "homewindowmanager.h"
#include "registrwindoww.h"
#include "database.h"
#include "user.h"
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void openRegistrWindow();
    void openHomeWindowAdmin();
    void openHomeWindowManager();
    void openHomeWindowBuyer();

private:
    Ui::MainWindow *ui;
    RegistrWindoww *_RegistrWindoww;
    HomeWindowAdmin *_HomeWindowAdmin;
    HomeWindowManager *_HomeWindowManager;
    HomeWindowBuyeer *_HomeWindowBuyeer;
    QSqlDatabase db;
    DataBase DB;
};
#endif // MAINWINDOW_H
