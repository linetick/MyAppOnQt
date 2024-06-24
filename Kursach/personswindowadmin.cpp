#include "personswindowadmin.h"
#include "ui_personswindowadmin.h"

PersonsWindowAdmin::PersonsWindowAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonsWindowAdmin),
    proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    setWindowTitle("Окно списка пользователей");

    _AddPerson = new AddPerson(this);
    _WarningWindow = new WarningWindow(this);
    _ChangePersonWindow = new ChangePersonWindow(this);

    _AddPerson->setModal(true);
    ui->tableView->verticalHeader()->setVisible(false);

    //connect(this, &PersonsWindowAdmin::openAddPerson);
    connect(this, &PersonsWindowAdmin::openAddPerson,
            _AddPerson, &AddPerson::exec);
    // connect(_AddProductWindow, &AddProductWindow::close,
    //       this, &AddProductWindow::show);
    //connect(_AddPerson, &AddPerson::closee,
      //      this, &ProductsWindow_Manager::enableHomeWindow);
    connect(this, &PersonsWindowAdmin::openWarning, _WarningWindow, &WarningWindow::exec);
    connect(this, &PersonsWindowAdmin::openChangePerson, _ChangePersonWindow, &ChangePersonWindow::exec);
    connect(_WarningWindow, &WarningWindow::yes, this, &PersonsWindowAdmin::DeletePerson);
    connect(this, &PersonsWindowAdmin::giveInformationChange, _ChangePersonWindow, &ChangePersonWindow::takeID);
    connect(_ChangePersonWindow, &ChangePersonWindow::update, this, &PersonsWindowAdmin::updatePersons);
    connect(_AddPerson, &AddPerson::update, this, &PersonsWindowAdmin::updatePersons);

    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel);

    connect(ui->Search, &QLineEdit::textChanged, this, [this](const QString &text) {
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    });

    //Махинации с таблицей
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

PersonsWindowAdmin::~PersonsWindowAdmin()
{
    delete ui;
}

void PersonsWindowAdmin::updatePersons()
{
    //ui->tableView->setModel(db.getPeopleTableNoneLogin());
    proxyModel->setSourceModel(db.getPeopleTableNoneLogin());
}

void PersonsWindowAdmin::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    updatePersons();
}

int PersonsWindowAdmin::takeID()
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

void PersonsWindowAdmin::on_Return_button_Clicked_clicked()
{
    this->close();
    emit Return();
}


void PersonsWindowAdmin::on_AddPerson_button_Clicked_clicked()
{
    emit openAddPerson();
}


void PersonsWindowAdmin::on_deletePerson_button_Clicked_clicked()
{
    if(takeID() !=-1)
    {
        ID = takeID();
        emit openWarning();
    }
}

void PersonsWindowAdmin::DeletePerson()
{
    db.deletePerson(ID);
    updatePersons();
}


void PersonsWindowAdmin::on_changePersons_button_Clicked_clicked()
{
    if(takeID() !=-1)
    {
        ID = takeID();
        emit giveInformationChange(ID);
        emit openChangePerson();
    }
}

