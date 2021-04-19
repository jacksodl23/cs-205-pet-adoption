#include "petdisplay.h"
#include "ui_petdisplay.h"

PetDisplay::PetDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PetDisplay)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("number of pets liked or number of pets viewed here");

    QString photoFilePath(":/resources/imgs/petPhoto0.jpg");
    petPic.load(photoFilePath);
    int width = ui->animalDisplay->width();
    int height = ui->animalDisplay->height();
    ui->animalDisplay->setPixmap(petPic.scaled(width, height, Qt::KeepAspectRatio));
    displayPet();
    getCurrentUser();
}

PetDisplay::~PetDisplay()
{
    delete ui;
}

void PetDisplay::on_actionQuit_triggered()
{
   QApplication::quit();
}

// changes available breeds based on pet type
void PetDisplay::on_typeBox_activated(const QString &arg1)
{
    std::vector<std::string> dogBreedList = {"Affenpinscher", "Curly-Coated Retriever",
                               "Foxhound", "Lakeland Terrier"};
    if (arg1 == "Dog") {
        ui->breedBox->clear();
        for (unsigned long i = 0; i < dogBreedList.size(); i++) {
            ui->breedBox->addItem(dogBreedList[i].data());
        }
    }


    std::vector<std::string> catBreedList = {"Abyssinian", "Manx",
                               "Russian Blue", "Sphynx"};
    if (arg1 == "Cat") {
        ui->breedBox->clear();
        for (unsigned long j = 0; j < catBreedList.size(); j++) {
            ui->breedBox->addItem(catBreedList[j].data());
        }
    }
}

void PetDisplay::on_pushButton_clicked()
{
    QMessageBox::information(this, "Hurray!", "Search button clicked!");
    //QMessageBox searchBox;
    //searchBox.setText("Hurray!\nSearch button clicked!");
    //searchBox.exec();
}

void PetDisplay::displayPet()
{
    QSqlQuery query;
    if (query.exec("select max(pet_id) from Pet")) {
        if (query.next()) {
            int maxID = query.value(0).toInt();

            srand(time(0));
            int displayID = rand() % maxID + 1;

            QSqlQuery q2;
            q2.prepare("select * from Pet where pet_id = ?");
            q2.addBindValue(displayID);
            if (q2.exec()) {
                if (q2.next()) {
                    QString name = q2.value(1).toString();
                    ui->label_name->setText(name);
                }
            }
        }
    }
}

void PetDisplay::getCurrentUser()
{
    QSqlQuery query;
    query.prepare("select * from Adopter where adopter_id = ?");
    query.addBindValue(currentUserID);

    if (query.exec()) {
        if (query.next()) {
            QString name = query.value(1).toString();
            ui->label_user_name->setText("Welcome " + name);
        }
    }
}
