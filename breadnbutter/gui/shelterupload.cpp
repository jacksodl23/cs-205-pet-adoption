#include "shelterupload.h"
#include "ui_shelterupload.h"
#include "shelterhelp.h"
#include "shelterprofile.h"
#include "createaccount.h"
#include "mainwindow.h"

// gets a list of dog breeds by selecting each distinct dog breed in the pet table.
void shelterUpload::fetchDogBreeds()
{
    QSqlQuery query;
    query.prepare("select distinct breed from pet where is_cat = 0");

    if (query.exec()) {
        while (query.next()) {
            QString breed = query.value(0).toString();
            ui->breedBox->addItem(breed); // adds this breed to the drop down menu.
        }
    } else {
        qDebug() << "Error fetching dog breeds:" << query.lastError().text();
    }
}

shelterUpload::shelterUpload(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterUpload)
{
    ui->setupUi(this);

    // Used to initially populate drop down menus.
    fetchDogBreeds(); // gets list of dog breeds.
    fetchBreedColors(); // gets list of colors.
    fetchHairLengths(); // gets list of hair lengths.
}

shelterUpload::~shelterUpload()
{
    delete ui;
}

/* Handles changes in the type drop down menu.
 * Fetches dog breeds if dog is selected and cat breeds if cat is selected.
 */
void shelterUpload::on_typeBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Dog"){
        ui->breedBox->clear();

        fetchDogBreeds();
    }
    else if(arg1 == "Cat"){
        ui->breedBox->clear();

        QSqlQuery query;
        query.prepare("select distinct breed from pet where is_cat = 1");

        if (query.exec()) {
            while (query.next()) {
                QString breed = query.value(0).toString();
                ui->breedBox->addItem(breed);
            }
        } else {
            qDebug() << "Error fetching dog breeds:" << query.lastError().text();
        }
    }
}

/* Fetches list of colors from database.
 * Populates color drop down menu after fetching.
 */
void shelterUpload::fetchBreedColors()
{
    QSqlQuery query;
    query.prepare("select distinct color from pet where breed = ?");
    query.addBindValue(ui->breedBox->currentText());

    if (query.exec()) {
        while (query.next()) {
            QString color = query.value(0).toString();
            ui->colorBox->addItem(color);
        }
    } else {
        qDebug() << "Error fetching colors:" << query.lastError().text();
    }
}

/* Fetches hair lengths from database.
 * Populates drop down menu after fetching.
 */
void shelterUpload::fetchHairLengths()
{
    ui->hairLenBox->clear();

    QSqlQuery query;
    query.prepare("select distinct hair_length from pet");
    if (query.exec()) {
        while (query.next()) {
            QString hairLen = query.value(0).toString();
            ui->hairLenBox->addItem(hairLen);
        }
    } else {
        qDebug() << "Error fetching hair lengths:" << query.lastError().text();
    }
}

/* Handles when breed is changed.
 * Fetches colors and hair lengths after selection.
 */
void shelterUpload::on_breedBox_activated(const QString &arg1)
{
    ui->colorBox->clear();

    fetchBreedColors();
    fetchHairLengths();
}

// Hides the current window and shows the shelter profile interface.
void shelterUpload::on_cancelButton_clicked()
{
    hide();
    parentWidget()->show();
}

/* Uploads the pet to the database.
 * Fetches values of all fields.
 * Creates a new Pet instance out of these values and inserts it into the database.
 */
void shelterUpload::on_addButton_clicked()
{
    bool is_cat = false;
    if (ui->typeBox->currentText() == "Cat")
        is_cat = true;

    QString name = ui->nameField->text();
    int age = ui->ageField->text().toInt();
    QString breed = ui->breedBox->currentText();
    QString color = ui->colorBox->currentText();
    QString hairLen = ui->hairLenBox->currentText();
    float weight = ui->weightField->text().toFloat();
    QString origin = ui->originBox->currentText();
    QString description = ui->descriptionTextEdit->toPlainText();

    bool hypo = false;
    if (ui->hypoBox->currentText() == "Yes")
        hypo = true;

    Pet newPet(is_cat, name, age, breed, color, hairLen, weight, origin, hypo, description);

    bool ok = newPet.insertIntoDB(shelter->getShelterID());

    if(ok) {
        QMessageBox::information(this, "Successful!", "Yay! You've added a new pet!");

        hide();
        parentWidget()->show();
    } else {
        QMessageBox::critical(this, "Error!", "Something went wrong when attempting to upload your pet. Please try again.");
    }
}

// sets the current shelter.
void shelterUpload::setShelter(Shelter *value)
{
    shelter = value;
}

// shows the shelter profile screen when the profile menu item is clicked.
void shelterUpload::on_actionProfile_triggered()
{
    shelterProfile *w = new shelterProfile(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// shows the help screen when the help menu item is clicked.
void shelterUpload::on_actionHelp_triggered()
{
    shelterhelp *w = new shelterhelp(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// logs out the current user and presents the login window.
void shelterUpload::on_actionLog_out_triggered()
{
    hide();
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

// quits the program when the quit menu item is clicked.
void shelterUpload::on_actionQuit_triggered()
{
   QApplication::quit();
}

// shows a dialog explaining the program.
void shelterUpload::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
