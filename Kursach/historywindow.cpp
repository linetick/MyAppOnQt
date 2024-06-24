#include "historywindow.h"
#include "qsortfilterproxymodel.h"
#include "ui_historywindow.h"

HistoryWindow::HistoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWindow),
    proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    setWindowTitle("История покупок");

    connect(ui->tableView, &QTableView::doubleClicked, this, &HistoryWindow::onCellDoubleClicked);

    QHeaderView* horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch); // Растягивает все столбцы равномерно

    //QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    //proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel);

    connect(ui->Search, &QLineEdit::textChanged, this, [this](const QString &text) {
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    });


    //Махинации с таблицей
    ui->tableView->setShowGrid(true); // Показывает сетку таблицы
    ui->tableView->setFrameShape(QFrame::NoFrame); // Убирает рамку вокруг таблицы, если необходимо
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->verticalHeader()->setVisible(false);

    bool check = false;
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

int HistoryWindow::takeID()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        //QMessageBox::warning(this, "Выбор элемента", "Пожалуйста, выберите элемент в таблице."); // тут добавить
        return -1;
    }

    bool correctColumnSelected = false;
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0) { // Предполагаем, что ID_Товара находится в первой колонке
            //correctColumnSelected = true;
            return index.data().toInt();
        }
    }

    if (!correctColumnSelected)
    {
        //QMessageBox::warning(this, "Неверный выбор", "Пожалуйста, выберите ID_Товара в первой колонке.");
        return -1;
    } /*else {
        // Здесь код для обработки корректного выбора, если необходимо
        QMessageBox::information(this, "Корректный выбор", "Выбран ID_Товара.");
    }*/
    return -1;
}

void HistoryWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    ShowDelivery();
    styleButton(false);
}

void HistoryWindow::ShowDelivery()
{
    db.getDeliveryByCustomerId();
    //ui->tableView->setModel(db.getModel());
    proxyModel->setSourceModel(db.getModel());
}

void HistoryWindow::showZakaz(int a)
{
    db.getOrdersByDeliveryId(a);
    //ui->tableView->setModel(db.Anothermodel());
    proxyModel->setSourceModel(db.Anothermodel());
}

void HistoryWindow::onCellDoubleClicked(const QModelIndex &index)
{
    if(check == false)
    {
        int selected = takeID();
        if(selected != -1)
        {
            check = true;
            showZakaz(selected);
            styleButton(true);
        }
    }
}

void HistoryWindow::styleButton(bool a)
{
    if(a == false)
    {
        ui->ReturnToDelivery_button_Clicked->setStyleSheet("QPushButton {color: white; font-weight: bold;border: none; font-size: 20pt;background-color: none;}");
        ui->ReturnToDelivery_button_Clicked->setText("");
    }
    else
    {
        ui->ReturnToDelivery_button_Clicked->setStyleSheet("QPushButton {color: white;background-color: rgba(255,255,255,30);border: 1px solid rgba(255,255,255,40);border-radius: 12px;font-size: 14pt;} QPushButton:hover{background-color: rgba(255,255,255,40);}QPushButton:pressed{background-color: rgba(255,255,255,70);}");
        ui->ReturnToDelivery_button_Clicked->setText("<-");
    }
}


void HistoryWindow::on_Return_button_clicked_clicked()
{
    check = false;
    this->close();
    emit Return();
}


void HistoryWindow::on_pushButton_clicked()
{
    if(check == true)
    {
        ShowDelivery();
    }
}


void HistoryWindow::on_ReturnToDelivery_button_Clicked_clicked()
{
    ShowDelivery();
    check = false;
    styleButton(false);
}

