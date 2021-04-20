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

        // clearing all of the drop down menus
        ui->breedBox->clear();
        ui->colorBox->clear();
        ui->ageBox->clear();
        ui->hairLenBox->clear();
        ui->weightBox->clear();
        ui->hypoBox->clear();

        for (unsigned long i = 0; i < dogBreedList.size(); i++) {
            ui->breedBox->addItem(dogBreedList[i].data());
        }
    }


    std::vector<std::string> catBreedList = {"Abyssinian", "Manx",
                               "Russian Blue", "Sphynx"};
    if (arg1 == "Cat") {

        // clearing all of the drop down menus
        ui->breedBox->clear();
        ui->colorBox->clear();
        ui->ageBox->clear();
        ui->hairLenBox->clear();
        ui->weightBox->clear();
        ui->hypoBox->clear();

        for (unsigned long j = 0; j < catBreedList.size(); j++) {
            ui->breedBox->addItem(catBreedList[j].data());
        }
    }
}

void PetDisplay::on_breedBox_activated(const QString &arg1)
{
    std::vector<std::string> affenpinscherColors = {"Black", "Grey", "Red", "Tan",
                                                   "Silver", "Beige"};

    // handle dog breeds colors and hair length -- maybe use a map with key val pairs
    // loaded from the database?
    if (arg1 == "Affenpinscher") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long k = 0; k < affenpinscherColors.size(); k++) {
            ui->colorBox->addItem(affenpinscherColors[k].data());
        }
        ui->hairLenBox->addItem("Long");
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> curlyCoatedRetrieverColors = {"Black", "Liver"};
    if (arg1 == "Curly-Coated Retriever") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long i = 0; i < curlyCoatedRetrieverColors.size(); i++) {
            ui->colorBox->addItem(curlyCoatedRetrieverColors[i].data());
        }
        ui->hairLenBox->addItem("Medium");
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> foxhoundColors = {"White", "Tan", "Blue", "Tri-color",
                                              "White & Cream", "Red"};
    if (arg1 == "Foxhound") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long i = 0; i < foxhoundColors.size(); i++) {
            ui->colorBox->addItem(foxhoundColors[i].data());
        }
        ui->hairLenBox->addItem("Medium");
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> lakelandTerrierColors = {"Black", "Wheaten", "Black and Tan",
                                                      "Blue", "Grizzle & Tan", "Red"};
    if (arg1 == "Lakeland Terrier") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long i = 0; i < lakelandTerrierColors.size(); i++) {
            ui->colorBox->addItem(lakelandTerrierColors[i].data());
        }
        ui->hairLenBox->addItem("Long");
        ui->hairLenBox->addItem("Medium");
    }



    std::vector<std::string> abyssinianColors = {"Ruddy", "Sorrel", "Blue", "Fawn",
                                                "Chocolate", "Silver", "Lilac"};
    // handle cat breeds colors and hair length -- maybe use a map with key val pairs
    // loaded from the database?
    if (arg1 == "Abyssinian") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < abyssinianColors.size(); i++) {
            ui->colorBox->addItem(abyssinianColors[i].data());
        }
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> manxColors = {"White", "Blue", "Black", "Red",
                                                "Cream", "Silver", "Tortoiseshell",
                                          "Bluecream", "Brown"};
    if (arg1 == "Manx") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < manxColors.size(); i++) {
            ui->colorBox->addItem(manxColors[i].data());
        }
        ui->hairLenBox->addItem("Long");
        ui->hairLenBox->addItem("Medium");
    }

    std::vector<std::string> russianBlueColors = {"Silver", "Dark Grey"};
    if (arg1 == "Russian Blue") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < russianBlueColors.size(); i++) {
            ui->colorBox->addItem(russianBlueColors[i].data());
        }
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> sphynxColors = {"White", "Black", "Red", "Brown",
                                            "Lavender"};
    if (arg1 == "Sphynx") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < sphynxColors.size(); i++) {
            ui->colorBox->addItem(sphynxColors[i].data());
        }
        ui->hairLenBox->addItem("Hairless");
    }
}

void PetDisplay::on_pushButton_clicked()
{
    QString noticeString = "Search button clicked! Your pet type is ";
    noticeString.append(ui->typeBox->currentText());
    QMessageBox::information(this, "Hurray!", noticeString);
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
            q2.prepare("select * from Pet "
                       "inner join Shelter on Shelter.shelter_id = Pet.shelter_id "
                       "where Pet.pet_id = ?");
            q2.addBindValue(displayID);
            if (q2.exec()) {
                if (q2.next()) {
                    QString pName = q2.value(1).toString();
                    ui->label_name->setText(pName);

                    QString sName = q2.value(5).toString();
                    ui->label_shelter_name->setText(sName);
                }
            } else {
                qDebug() << "Error getting pet:" << q2.lastError().text();
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
            ui->label_user_name->setText("Welcome " + name + "!");
        }
    } else {
        qDebug() << "Error getting current user: " << query.lastError().text();
    }
}
