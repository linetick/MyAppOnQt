#ifndef BUYWINDOW_H
#define BUYWINDOW_H

#include <QDialog>
#include <database.h>

namespace Ui {
class BuyWindow;
}

class BuyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BuyWindow(QWidget *parent = nullptr);
    ~BuyWindow();

private slots:
    void on_Return_button_Clicked_clicked();

    void on_Buy_button_Clicked_clicked();

signals:
    void complete();

public slots:
    void takeCountMoney(QString a);

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::BuyWindow *ui;
    DataBase db;
};

#endif // BUYWINDOW_H
