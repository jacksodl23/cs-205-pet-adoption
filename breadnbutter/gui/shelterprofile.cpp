#include "shelterprofile.h"
#include "ui_shelterprofile.h"
#include "shelterhelp.h"
#include "shelterupload.h"

shelterProfile::shelterProfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterProfile)
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome " + currentUser.getFirstName() + "!");

    fetchShelter();
    if (currentShelter != nullptr)
        populatePetsTable();
}

shelterProfile::~shelterProfile()
{
    delete ui;
}

void shelterProfile::fetchShelter()
{
    QSqlQuery query;
    query.prepare("select shelter_id from shelter where owner_id = ?");
    query.addBindValue(currentUser.getID());

    if (query.exec()) {
        if (query.next()) {
            int shelterID = query.value(0).toInt();

            Shelter *s = new Shelter(shelterID);

            currentShelter = s;
            ui->shelterNameLabel->setText("You are the owner of " + currentShelter->getName());
        } else {
            QMessageBox::critical(this, "No Shelter Linked!", "The shelter you own could not be found.");
            logOutShelterOwner();
        }
    } else {
        qDebug() << "Error finding owner's shelter:" << query.lastError().text();
    }
}

/*
void shelterProfile::on_actionUpload_triggered()
{
    shelterUpload *w = new shelterUpload;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}
*/

void shelterProfile::populatePetsTable()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select pet.name, pet.color, pet.hair_length, pet.description, pet_attributes.age, pet_attributes.breed, pet_attributes.weight, pet_attributes.origin "
                  "from pet "
                  "inner join pet_attributes on pet_attributes.pet_att_id = pet.pet_attribute_id "
                  "where pet.shelter_id = ?");
    query.addBindValue(currentShelter->getShelterID());

    if (query.exec()) {
        model->setQuery(query);
        ui->tableView->setModel(model);
    } else {
        qDebug() << "Error getting pets in shelter:" << query.lastError().text();
    }
}

void shelterProfile::on_actionUpload_triggered()
{
    shelterUpload *w = new shelterUpload(this);
    w->setShelter(currentShelter);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void shelterProfile::on_actionLog_out_triggered()
{
    logOutShelterOwner();
}

void shelterProfile::logOutShelterOwner()
{
    hide();

    currentUser.logOut();
    parentWidget()->show();
}

void shelterProfile::on_actionHelp_triggered()
{
    shelterhelp *w = new shelterhelp(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}
