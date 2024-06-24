#include "orderswindow.h"
#include "ui_orderswindow.h"

OrdersWindow::OrdersWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdersWindow),
    proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    setWindowTitle("Окно заказов");

    _ChangeDeliveryWindow = new ChangeDeliveryWindow(this);

    connect(ui->tableView, &QTableView::doubleClicked, this, &OrdersWindow::onCellDoubleClicked);
    connect(this, &OrdersWindow::openChange, _ChangeDeliveryWindow, &ChangeDeliveryWindow::exec);
    connect(this, &OrdersWindow::getInformationInChange, _ChangeDeliveryWindow, &ChangeDeliveryWindow::takeID);
    connect(_ChangeDeliveryWindow, &ChangeDeliveryWindow::reset, this, &OrdersWindow::reset);

    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel);

    connect(ui->Search, &QLineEdit::textChanged, this, [this](const QString &text) {
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    });

    // Махинации с таблицей:
    QHeaderView* horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);
    //
    ui->tableView->setShowGrid(true);
    ui->tableView->setFrameShape(QFrame::NoFrame);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->verticalHeader()->setVisible(false);
}

OrdersWindow::~OrdersWindow()
{
    delete ui;
}

void OrdersWindow::showAll()
{
    proxyModel->setSourceModel(db.getDeliveryInfo(5));
   //ui->tableView->setModel(db.getDeliveryInfo(5));
    count = 5;
}

void OrdersWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    showAll();
    styleButton(false);
}

void OrdersWindow::showZakaz(int a)
{
    db.getOrdersByDeliveryId(a);
    proxyModel->setSourceModel(db.Anothermodel());
    //ui->tableView->setModel(db.Anothermodel());
}

void OrdersWindow::onCellDoubleClicked(const QModelIndex &index)
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

void OrdersWindow::reset()
{
    //ui->tableView->setModel(db.getDeliveryInfo(count));
    proxyModel->setSourceModel(db.getDeliveryInfo(count));
}

int OrdersWindow::takeID()
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

void OrdersWindow::styleButton(bool a)
{
    if(a == false)
    {
        ui->back_button_Clicked->setStyleSheet("QPushButton {color: white; font-weight: bold;border: none; font-size: 20pt;background-color: none;}");
        ui->back_button_Clicked->setText("");
    }
    else
    {
        ui->back_button_Clicked->setStyleSheet("QPushButton {color: white;background-color: rgba(255,255,255,30);border: 1px solid rgba(255,255,255,40);border-radius: 12px;font-size: 14pt;} QPushButton:hover{background-color: rgba(255,255,255,40);}QPushButton:pressed{background-color: rgba(255,255,255,70);}");
        ui->back_button_Clicked->setText("<-");
    }
}

void OrdersWindow::on_Return_button_clicked_clicked()
{
    this->close();
    emit Return();
}


void OrdersWindow::on_showAll_button_Clicked_clicked()
{
    showAll();
}


void OrdersWindow::on_SProccesingOrders_button_clicked_clicked()
{
    //ui->tableView->setModel(db.getDeliveryInfo(1));
    proxyModel->setSourceModel(db.getDeliveryInfo(1));
    count = 1;
    check = false;
}


void OrdersWindow::on_showEndOrder_button_Clicked_clicked()
{
    //ui->tableView->setModel(db.getDeliveryInfo(4));
    proxyModel->setSourceModel(db.getDeliveryInfo(4));
    count = 4;
    check = false;
    styleButton(false);
}


void OrdersWindow::on_showDelieveryOrders_button_clicked_clicked()
{
    //ui->tableView->setModel(db.getDeliveryInfo(2));
    proxyModel->setSourceModel(db.getDeliveryInfo(2));
    count =2;
    check = false;
    styleButton(false);
}


void OrdersWindow::on_SCanceledOrders_button_Clicked_clicked()
{
    //ui->tableView->setModel(db.getDeliveryInfo(3));
    proxyModel->setSourceModel(db.getDeliveryInfo(3));
    count = 3;
    check = false;
    styleButton(false);
}


void OrdersWindow::on_back_button_Clicked_clicked()
{

    check = false;
    styleButton(false);
    if(count == 1) proxyModel->setSourceModel(db.getDeliveryInfo(1)); //ui->tableView->setModel(db.getDeliveryInfo(1));
    if(count == 2) proxyModel->setSourceModel(db.getDeliveryInfo(2)); //ui->tableView->setModel(db.getDeliveryInfo(2));
    if(count == 3) proxyModel->setSourceModel(db.getDeliveryInfo(3)); //ui->tableView->setModel(db.getDeliveryInfo(3));
    if(count == 4) proxyModel->setSourceModel(db.getDeliveryInfo(4)); //ui->tableView->setModel(db.getDeliveryInfo(4));
    if(count == 5) proxyModel->setSourceModel(db.getDeliveryInfo(5)); //ui->tableView->setModel(db.getDeliveryInfo(5));
}


void OrdersWindow::on_ChangeStatus_button_Clicked_clicked()
{
    int selected = takeID();
    if(selected != -1 && check != true)
    {
        emit getInformationInChange(selected);
        emit openChange();
    }
}

