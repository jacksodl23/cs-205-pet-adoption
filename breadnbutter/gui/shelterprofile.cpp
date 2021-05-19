#include "shelterprofile.h"
#include "ui_shelterprofile.h"
#include "shelterhelp.h"
#include "shelterupload.h"

shelterProfile::shelterProfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterProfile)
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome " + currentUser.getFirstName() + "!"); // sets welcome text.

    fetchShelter(); // gets the info of the current shelter.
    if (currentShelter != nullptr)
        populatePetsTable(); // if the current shelter is valid, populate the pets table.
}

shelterProfile::~shelterProfile()
{
    delete ui;
}

void shelterProfile::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if (currentShelter != nullptr)
        populatePetsTable(); // refreshes the table as soon as this window is shown.
}

/* Gets info from the current shelter.
 * Finds a shelter whose owner is the current user.
 */
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

/* Populates the table of pets.
 * Queries the database for pets with a shelter ID matching the current shelter.
 * Updates the table if pets are found and hides columns irrelevant to the user.
 * Uses a subclass of QSqlQueryModel so that the table is editable.
*/
void shelterProfile::populatePetsTable()
{
    ShelterProfileSqlModel *model = new ShelterProfileSqlModel();

    QSqlQuery query;
    query.prepare("select * "
                  "from pet "
                  "where pet.shelter_id = ?");
    query.addBindValue(currentShelter->getShelterID());

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(5, Qt::Horizontal, tr("type")); // change is_cat column name to type

        ui->tableView->setModel(model);

        ui->tableView->hideColumn(0); // pet_id
        ui->tableView->hideColumn(2); // shelter_id
    } else {
        qDebug() << "Error getting pets in shelter:" << query.lastError().text();
    }
}

// presents the pet upload interface when the upload menu item is clicked.
void shelterProfile::on_actionUpload_triggered()
{
    shelterUpload *w = new shelterUpload(this);
    w->setShelter(currentShelter);
    w->setAttribute(Qt::WA_DeleteOnClose);

    hide();
    w->show();
}

// handles when the log out menu item is clicked.
void shelterProfile::on_actionLog_out_triggered()
{
    logOutShelterOwner();
}

// hides the current window, logs out the user, and presents the main window allowing the user to log in or sign up.
void shelterProfile::logOutShelterOwner()
{
    hide();

    currentUser.logOut();
    parentWidget()->show();
}

// presents the help screen when the help menu item is clicked.
void shelterProfile::on_actionHelp_triggered()
{
    shelterhelp *w = new shelterhelp(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// presents the interface showing which adopters have liked the current shelter's pets.
void shelterProfile::on_actionAdopters_triggered()
{
    ShelterAdopters *w = new ShelterAdopters(this);
    w->setShelter(currentShelter);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// quits the program when the quit menu item is clicked.
void shelterProfile::on_actionQuit_triggered()
{
   QApplication::quit();
}

/* Deletes the currently selected pet when the delete pet button is clicked.
 * Checks which rows are currently selected.
 * Tells the model to remove any rows corresponding to those already selected in the table.
 */
void shelterProfile::on_deletePetButton_clicked()
{
   QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();

   for (int i = indexes.count(); i > 0; i--) {
       ShelterProfileSqlModel *model = static_cast<ShelterProfileSqlModel *>(ui->tableView->model());
       model->removeRow(indexes.at(i - 1).row(), QModelIndex());
   }
}

// shows a dialog explaining the program.
void shelterProfile::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
