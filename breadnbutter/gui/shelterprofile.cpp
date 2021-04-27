#include "shelterprofile.h"
#include "ui_shelterprofile.h"

shelterProfile::shelterProfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterProfile)
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome " + currentUser.getFirstName() + "!");

    fetchShelter();
    if (currentShelter == nullptr)
        QMessageBox::warning(this, "No Shelter Linked!", "Please indicate which shelter you own.", QMessageBox::Ok);
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
            ShelterOwner *owner = new ShelterOwner(currentUser.getID());
            s->setOwner(owner);

            currentShelter = s;
            ui->shelterNameLabel->setText("You are the owner of " + currentShelter->getName());
        }
    } else {
        qDebug() << "Error finding owner's shelter:" << query.lastError().text();
    }
}
