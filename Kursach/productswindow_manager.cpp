#include "productswindow_manager.h"
#include "ui_productswindow_manager.h"

ProductsWindow_Manager::ProductsWindow_Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductsWindow_Manager),
    proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    setWindowTitle("Список продуктов");

    _AddProductWindow = new AddProductWindow(this);
    _ChangeProductWindow = new ChangeProductWindow(this);
    _WarningWindow = new WarningWindow(this);

    _AddProductWindow->setModal(true);
    //DataBase* database = new DataBase();

    connect(this, &ProductsWindow_Manager::openAddProduct, //Открыть продукты
            this, &ProductsWindow_Manager::disableHomeWindow);
    connect(this, &ProductsWindow_Manager::openAddProduct,
            _AddProductWindow, &AddProductWindow::exec);
   // connect(_AddProductWindow, &AddProductWindow::close,
     //       this, &AddProductWindow::show);
    connect(_AddProductWindow, &AddProductWindow::closee,
            this, &ProductsWindow_Manager::getPerson);
    connect(this, &ProductsWindow_Manager::openChangeProduct, _ChangeProductWindow, &ChangeProductWindow::exec);
    connect(this, &ProductsWindow_Manager::openWarning, _WarningWindow, &WarningWindow::exec);
    connect(this, &ProductsWindow_Manager::getInformationInChange, _ChangeProductWindow, &ChangeProductWindow::takeID);
    connect(_ChangeProductWindow, &ChangeProductWindow::update, this, &ProductsWindow_Manager::getProducts);
    connect(_WarningWindow, &WarningWindow::yes, this, &ProductsWindow_Manager::Delete);

    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel);

    connect(ui->Search, &QLineEdit::textChanged, this, [this](const QString &text) {
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    });


    // Махинации с таблицей:
    QHeaderView* horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch); // Растягивает все столбцы равномерно
    //
    ui->tableView->setShowGrid(true); // Показывает сетку таблицы
    ui->tableView->setFrameShape(QFrame::NoFrame); // Убирает рамку вокруг таблицы, если необходимо
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->verticalHeader()->setVisible(false);
}

void ProductsWindow_Manager::getProducts()
{
    db.getProduct();
    proxyModel->setSourceModel(db.getModel());
    //ui->tableView->setModel(db.getModel());
}

void ProductsWindow_Manager::getPerson()
{
    getProducts();
}

void ProductsWindow_Manager::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    getProducts();

}
void ProductsWindow_Manager::disableHomeWindow() {
    // Метод делает домашнее окно неактивным, но оно остаётся видимым
    //this->setDisabled(true);
}

void ProductsWindow_Manager::enableHomeWindow() {
    // Метод делает домашнее окно снова активным
    //this->setEnabled(true);
}



ProductsWindow_Manager::~ProductsWindow_Manager()
{
    delete ui;
}

int ProductsWindow_Manager::takeID()
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

void ProductsWindow_Manager::Delete()
{
    db.deleteProduct(ID);
    getProducts();
}

void ProductsWindow_Manager::on_Return_button_Clicked_clicked()
{
    this->close();
    emit Return();
}


void ProductsWindow_Manager::on_AddProduct_button_Clicked_clicked()
{
    emit openAddProduct();
}

void ProductsWindow_Manager::on_ChangeProduct_button_Clicked_clicked()
{
    int selected = takeID();
    if(selected != -1)
    {
        emit getInformationInChange(selected);
        emit openChangeProduct();

    }

}


void ProductsWindow_Manager::on_DeleteProduct_button_Clicked_clicked()
{
    if(takeID() !=-1)
    {
        ID = takeID();
        emit openWarning();
    }
}

