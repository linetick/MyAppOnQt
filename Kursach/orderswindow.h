#ifndef ORDERSWINDOW_H
#define ORDERSWINDOW_H

//#include <QDialog>
#include "database.h"
#include "changedeliverywindow.h"
#include "qsortfilterproxymodel.h"
#include "QWidget"

namespace Ui {
class OrdersWindow;
}

class OrdersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersWindow(QWidget *parent = nullptr);
    ~OrdersWindow();

    void showAll();
    int takeID();
    void styleButton(bool a);
    void showZakaz(int a);

signals:
    void Return();
    void openChange();
    void getInformationInChange(int);

private slots:
    void on_Return_button_clicked_clicked();

    void on_showAll_button_Clicked_clicked();

    void on_SProccesingOrders_button_clicked_clicked();

    void on_showEndOrder_button_Clicked_clicked();

    void on_showDelieveryOrders_button_clicked_clicked();

    void on_SCanceledOrders_button_Clicked_clicked();

    void on_back_button_Clicked_clicked();

    void on_ChangeStatus_button_Clicked_clicked();

public slots:
    void onCellDoubleClicked(const QModelIndex &index);
    void reset();

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::OrdersWindow *ui;
    DataBase db;
    ChangeDeliveryWindow *_ChangeDeliveryWindow;
    bool check = false;
    int count;
    QSortFilterProxyModel *proxyModel;
};

#endif // ORDERSWINDOW_H
