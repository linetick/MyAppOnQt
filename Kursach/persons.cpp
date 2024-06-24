#include "persons.h"
#include "ui_persons.h"
#include <QSqlTableModel>
#include <QMessageBox>

Persons::Persons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Persons),
    proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    setWindowTitle("Окно списка пользователей");

    // Запрос таблицы людей

//    if(db.open())
//    {
//        QMessageBox::critical(nullptr,"Найс", "Открыта");
//    }

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

Persons::~Persons()
{
    delete ui;
}

void Persons::getPersons()
{
    proxyModel->setSourceModel(db.getPeopleTable());
    //ui->tableView->setModel(db.getPeopleTable());
}

void Persons::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    getPersons();
}

void Persons::on_Return_button_Clicked_clicked()
{
    this->close();
    emit Return();
}

