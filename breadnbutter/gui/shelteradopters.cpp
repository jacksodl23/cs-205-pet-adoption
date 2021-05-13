#include "shelteradopters.h"
#include "ui_shelteradopters.h"

ShelterAdopters::ShelterAdopters(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShelterAdopters)
{
    ui->setupUi(this);

    populateTable();
}

ShelterAdopters::~ShelterAdopters()
{
    delete ui;
}

void ShelterAdopters::on_actionQuit_triggered()
{
    QApplication::quit();
}

void ShelterAdopters::populateTable()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from Liked_By");

    if (query.exec()) {
        model->setQuery(query);

        ui->tableView->setModel(model);
    } else {
        qDebug() << "Error getting likes:" << query.lastError().text();
    }
}
