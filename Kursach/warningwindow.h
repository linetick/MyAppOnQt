#ifndef WARNINGWINDOW_H
#define WARNINGWINDOW_H

#include <QDialog>

namespace Ui {
class WarningWindow;
}

class WarningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WarningWindow(QWidget *parent = nullptr);
    ~WarningWindow();

signals:
    void yes();

private slots:

    void on_Yes_button_Clicked_clicked();

    void on_No_button_Clicked_clicked();

private:
    Ui::WarningWindow *ui;
};

#endif // WARNINGWINDOW_H
