#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    //инициализация окон

    setWindowTitle("Вход в систему");

    _RegistrWindoww = new RegistrWindoww(); //окно регистрации
    _HomeWindowAdmin = new HomeWindowAdmin();
    _HomeWindowManager = new HomeWindowManager();
    _HomeWindowBuyeer = new HomeWindowBuyeer();

    connect(this, &MainWindow::openRegistrWindow,
            this, &MainWindow::close);
    connect(this, &MainWindow::openRegistrWindow,
            _RegistrWindoww, &RegistrWindoww::show);
    connect(_RegistrWindoww, &RegistrWindoww::openMainWindow,
            this, &MainWindow::show);

    connect(this, &MainWindow::openHomeWindowAdmin, this, &MainWindow::close);
    connect(this, &MainWindow::openHomeWindowAdmin, _HomeWindowAdmin, &HomeWindowAdmin::show);

    connect(this, &MainWindow::openHomeWindowManager, this, &MainWindow::close);
    connect(this, &MainWindow::openHomeWindowManager, _HomeWindowManager, &HomeWindowManager::show);

    connect(this, &MainWindow::openHomeWindowBuyer, this, &MainWindow::close);
    connect(this, &MainWindow::openHomeWindowBuyer, _HomeWindowBuyeer, &HomeWindowManager::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    if(db.open())
    {
        QMessageBox::information(nullptr, "ошибка", "Ошибка");

    }

    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString role = DB.checkCredentials(login, password);

   if(role == "Администратор")
    {
        emit openHomeWindowAdmin();
    }
    if(role == "Менеджер")
    {
        emit openHomeWindowManager();
    }
    if(role == "Покупатель")
    {
        emit openHomeWindowBuyer();
    }
    if(role == "Ошибка")
    {
        QMessageBox::information(nullptr, "Ошибка", "Неправильно введённый логин или пароль");
    }


}


void MainWindow::on_pushButton_2_clicked()
{
    emit openRegistrWindow();
}

