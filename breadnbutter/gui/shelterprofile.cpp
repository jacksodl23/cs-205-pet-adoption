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
    else
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
            ShelterOwner *owner = new ShelterOwner(currentUser.getID());
            s->setOwner(owner);

            currentShelter = s;
            ui->shelterNameLabel->setText("You are the owner of " + currentShelter->getName());
        }
    } else {
        qDebug() << "Error finding owner's shelter:" << query.lastError().text();
    }
}

void shelterProfile::populatePetsTable()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from Pet where shelter_id = ?");
    query.addBindValue(currentShelter->getShelterID());

    query.exec();
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void shelterProfile::on_actionUpload_triggered()
{
    shelterUpload *w = new shelterUpload(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void shelterProfile::on_actionLog_out_triggered()
{
    hide();

    currentUser.logOut();
    parentWidget()->show();
}
