#include "petliked.h"
#include "ui_petliked.h"
#include "petownerhelp.h"
#include "petdisplay.h"
#include "createaccount.h"
#include "mainwindow.h"

void PetLiked::fetchLikedPets()
{
    QSqlQuery query;
    query.prepare("select pet_id from liked_by where adopter_id = ?");
    query.addBindValue(currentUser.getID());

    if (query.exec()) {
        while (query.next()) {
            int pID = query.value(0).toInt();

            Pet p(pID);
            pets.push_back(p);
        }

        if (pets.size() == 1)
            ui->statusbar->showMessage("You have liked 1 pet.");
        else
            ui->statusbar->showMessage("You have liked " + QString::number(pets.size()) + " pets.");
    } else {
        qDebug() << "Error getting liked pets:" << query.lastError().text();
    }
}

void PetLiked::displayPet(Pet p)
{
    ui->label_name->setText(p.getName());
    ui->label_age->setText(QString::number(p.getAge()));

    if (!p.getIs_cat())
        ui->label_type->setText("Dog");
    else
        ui->label_type->setText("Cat");

    ui->label_color->setText(p.getColor());
    ui->label_breed->setText(p.getBreed());
    ui->label_hair->setText(p.getHairLength());
    ui->label_weight->setText(QString::number(p.getWeight()));

    if (!p.getHypoallergenic())
        ui->label_hypo->setText("No");
    else
        ui->label_hypo->setText("Yes");

    ui->label_origin->setText(p.getOrigin());

    QSqlQuery query;
    query.prepare("select shelter.owner_id, shelter.location "
                  "from pet "
                  "inner join shelter on shelter.shelter_id = pet.shelter_id "
                  "where pet.pet_id = ?");
    query.addBindValue(p.getPet_id());

    if (query.exec()) {
        if (query.next()) {
            int ownerIndex = query.record().indexOf("owner_id");
            int ownerID = query.value(ownerIndex).toInt();

            int locIndex = query.record().indexOf("location");
            QString loc = query.value(locIndex).toString();
            ui->label_location->setText(loc);

            ShelterOwner owner(ownerID);
            ui->label_owner_name->setText(owner.getFirstName() + " " + owner.getLastName());
            ui->label_owner_email->setText(owner.getEmail());
            ui->label_owner_phone->setText(owner.getPhoneNumber());
        }
    }

    ui->descriptionDisplay->setPlainText(p.getDescription());
}

PetLiked::PetLiked(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::petliked)
{
    ui->setupUi(this);
    currentPos = 0;

    fetchLikedPets();
    displayPet(pets.at(currentPos));

    // adding icons to the page
    QPixmap icon;

    QString iconName(":/icons/icons/Name.png");
    icon.load(iconName);
    int width = ui->icon_name->width();
    int height = ui->icon_name->height();
    ui->icon_name->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconType(":/icons/icons/Type.png");
    icon.load(iconType);
    width = ui->icon_type->width();
    height = ui->icon_type->height();
    ui->icon_type->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconBreed(":/icons/icons/Breed.png");
    icon.load(iconBreed);
    width = ui->icon_breed->width();
    height = ui->icon_breed->height();
    ui->icon_breed->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconAge(":/icons/icons/Age.png");
    icon.load(iconAge);
    width = ui->icon_age->width();
    height = ui->icon_age->height();
    ui->icon_age->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconColor(":/icons/icons/Color.png");
    icon.load(iconColor);
    width = ui->icon_color->width();
    height = ui->icon_color->height();
    ui->icon_color->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconHair(":/icons/icons/Hair.png");
    icon.load(iconHair);
    width = ui->icon_hair->width();
    height = ui->icon_hair->height();
    ui->icon_hair->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconWeight(":/icons/icons/Weight.png");
    icon.load(iconWeight);
    width = ui->icon_weight->width();
    height = ui->icon_weight->height();
    ui->icon_weight->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconAllergy(":/icons/icons/Allergy.png");
    icon.load(iconAllergy);
    width = ui->icon_allergy->width();
    height = ui->icon_allergy->height();
    ui->icon_allergy->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconHypo(":/icons/icons/Hypoallergenic.png");
    icon.load(iconHypo);
    width = ui->icon_hypo->width();
    height = ui->icon_hypo->height();
    ui->icon_hypo->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconOrigin(":/icons/icons/Origin.png");
    icon.load(iconOrigin);
    width = ui->icon_origin->width();
    height = ui->icon_origin->height();
    ui->icon_origin->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconLocation(":/icons/icons/Location.png");
    icon.load(iconLocation);
    width = ui->icon_location->width();
    height = ui->icon_location->height();
    ui->icon_location->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconShelter(":/icons/icons/Shelter.png");
    icon.load(iconShelter);
    width = ui->icon_shelter->width();
    height = ui->icon_shelter->height();
    ui->icon_shelter->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconPhone(":/icons/icons/Phone.png");
    icon.load(iconPhone);
    width = ui->icon_phone->width();
    height = ui->icon_phone->height();
    ui->icon_phone->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconEmail(":/icons/icons/Email.png");
    icon.load(iconEmail);
    width = ui->icon_email->width();
    height = ui->icon_email->height();
    ui->icon_email->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

}

PetLiked::~PetLiked()
{
    delete ui;
}

void PetLiked::on_button_next_clicked()
{
    if (currentPos < pets.size() - 1) {
        currentPos++;
        displayPet(pets.at(currentPos));
    } else {
        QMessageBox::warning(this, "No More Pets!", "There are no more pets that you have liked beyond this point.");
    }
}

void PetLiked::on_button_prev_clicked()
{
    if (currentPos > 0) {
        currentPos--;
        displayPet(pets.at(currentPos));
    } else {
        QMessageBox::warning(this, "No More Pets!", "There are no more pets that you have liked beyond this point.");
    }
}

void PetLiked::on_actionLog_out_triggered()
{
    hide();
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

void PetLiked::on_actionHelp_triggered()
{
    hide();
    petownerhelp *helpUI = new petownerhelp(this);
    helpUI->setAttribute(Qt::WA_DeleteOnClose);
    helpUI->show();
}

void PetLiked::on_actionSearch_triggered()
{
    hide();
    PetDisplay *petUI = new PetDisplay(this);
    petUI->setAttribute(Qt::WA_DeleteOnClose);
    petUI->show();
}

void PetLiked::on_actionQuit_triggered()
{
    QApplication::quit();
}

void PetLiked::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
