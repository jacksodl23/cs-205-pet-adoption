#include "shelteradopters.h"
#include "ui_shelteradopters.h"

ShelterAdopters::ShelterAdopters(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShelterAdopters)
{
    ui->setupUi(this);
}

ShelterAdopters::~ShelterAdopters()
{
    delete ui;
}

void ShelterAdopters::on_actionQuit_triggered()
{
    QApplication::quit();
}

void ShelterAdopters::setShelter(Shelter *value)
{
    shelter = value;

    populateTable();
}

/* Populates the table of
 * adopters who have liked the logged in shelter owner's pets.
 * Uses a query to select records from the liked by table.
 * Joins pet table to check that the pet's shelter is the current owner's shelter.
 * Sets the query the table view is to use.
 */
void ShelterAdopters::populateTable()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from Liked_By "
                  "inner join User on user.user_id = liked_by.adopter_id "
                  "inner join Pet on pet.pet_id = liked_by.pet_id "
                  "inner join Location on location.location_id = user.location_id "
                  "where pet.shelter_id = ?");
    query.addBindValue(shelter->getShelterID());

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(11, Qt::Horizontal, tr("pet name"));

        ui->tableView->setModel(model);

        int rowCount = model->rowCount();
        if (rowCount != 1)
            ui->adopterCountLabel->setText(QString::number(rowCount) + " adopters have liked your pets.");
        else
            ui->adopterCountLabel->setText("1 adopter has liked your pets.");

        ui->tableView->hideColumn(0); // liked_by_id
        ui->tableView->hideColumn(1); // adopter_id
        ui->tableView->hideColumn(2); // pet_id
        ui->tableView->hideColumn(3); // user_id
        ui->tableView->hideColumn(5); // location_id
        ui->tableView->hideColumn(8); // password
        ui->tableView->hideColumn(9); // is_adopter
        ui->tableView->hideColumn(10); // pet_id
        ui->tableView->hideColumn(12); // shelter_id
        ui->tableView->hideColumn(13); // color
        ui->tableView->hideColumn(14); // hair_length
        ui->tableView->hideColumn(15); // is_cat
        ui->tableView->hideColumn(16); // age
        ui->tableView->hideColumn(17); // breed
        ui->tableView->hideColumn(18); // weight
        ui->tableView->hideColumn(19); // origin
        ui->tableView->hideColumn(20); // hypoallergenic
        ui->tableView->hideColumn(21); // description
        ui->tableView->hideColumn(22); // location_id
        ui->tableView->hideColumn(26); // lattitude
        ui->tableView->hideColumn(27); // longitude
    } else {
        qDebug() << "Error getting likes:" << query.lastError().text();
    }
}

/*
 * Shows a message box explaining the program.
 */
void ShelterAdopters::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
