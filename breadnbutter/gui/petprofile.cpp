#include "petprofile.h"
#include "ui_petprofile.h"
#include "petdisplay.h"

/* Constructor of the PetProfile class with photo, icons, and progress bar addtions
 * along with setup code
 */
PetProfile::PetProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PetProfile)
{
    ui->setupUi(this);

    srand(time(0));

    // Get the currently selected pet's image from the parent pet display screen.
    PetDisplay *parentWidget = (PetDisplay *)parent;
    QPixmap petPic = parentWidget->getPetPic();

    ui->animalDisplay->setPixmap(petPic.scaled(ui->animalDisplay->width(), ui->animalDisplay->height(), Qt::KeepAspectRatio));

    // adding icons to the page
    QPixmap icon;

    QString iconName(":/icons/icons/Name.png");
    icon.load(iconName);
    ui->icon_name->setPixmap(icon.scaled(ui->icon_name->width(), ui->icon_name->height(), Qt::KeepAspectRatio));

    QString iconType(":/icons/icons/Type.png");
    icon.load(iconType);
    ui->icon_type->setPixmap(icon.scaled(ui->icon_type->width(), ui->icon_type->height(), Qt::KeepAspectRatio));

    QString iconBreed(":/icons/icons/Breed.png");
    icon.load(iconBreed);
    ui->icon_breed->setPixmap(icon.scaled(ui->icon_breed->width(), ui->icon_breed->height(), Qt::KeepAspectRatio));

    QString iconAge(":/icons/icons/Age.png");
    icon.load(iconAge);
    ui->icon_age->setPixmap(icon.scaled(ui->icon_age->width(), ui->icon_age->height(), Qt::KeepAspectRatio));

    QString iconColor(":/icons/icons/Color.png");
    icon.load(iconColor);
    ui->icon_color->setPixmap(icon.scaled(ui->icon_color->width(), ui->icon_color->height(), Qt::KeepAspectRatio));

    QString iconHair(":/icons/icons/Hair.png");
    icon.load(iconHair);
    ui->icon_hair->setPixmap(icon.scaled(ui->icon_hair->width(), ui->icon_hair->height(), Qt::KeepAspectRatio));

    QString iconWeight(":/icons/icons/Weight.png");
    icon.load(iconWeight);
    ui->icon_weight->setPixmap(icon.scaled(ui->icon_weight->width(), ui->icon_weight->height(), Qt::KeepAspectRatio));

    QString iconHypo(":/icons/icons/Hypoallergenic.png");
    icon.load(iconHypo);
    ui->icon_hypoallergenic->setPixmap(icon.scaled(ui->icon_hypoallergenic->width(), ui->icon_hypoallergenic->height(), Qt::KeepAspectRatio));

    QString iconOrigin(":/icons/icons/Origin.png");
    icon.load(iconOrigin);
    ui->icon_origin->setPixmap(icon.scaled(ui->icon_origin->width(), ui->icon_origin->height(), Qt::KeepAspectRatio));

    QString iconDistance(":/icons/icons/Distance.png");
    icon.load(iconDistance);
    ui->icon_distance->setPixmap(icon.scaled(ui->icon_distance->width(), ui->icon_distance->height(), Qt::KeepAspectRatio));

    QString iconLocation(":/icons/icons/Location.png");
    icon.load(iconLocation);
    ui->icon_location->setPixmap(icon.scaled(ui->icon_location->width(), ui->icon_location->height(), Qt::KeepAspectRatio));

    QString iconShelter(":/icons/icons/Shelter.png");
    icon.load(iconShelter);
    ui->icon_shelter->setPixmap(icon.scaled(ui->icon_shelter->width(), ui->icon_shelter->height(), Qt::KeepAspectRatio));

    QString iconPhone(":/icons/icons/Phone.png");
    icon.load(iconPhone);
    ui->icon_phone->setPixmap(icon.scaled(ui->icon_phone->width(), ui->icon_phone->height(), Qt::KeepAspectRatio));

    QString iconEmail(":/icons/icons/Email.png");
    icon.load(iconEmail);
    ui->icon_email->setPixmap(icon.scaled(ui->icon_email->width(), ui->icon_email->height(), Qt::KeepAspectRatio));
}

/* Default destructor
 */
PetProfile::~PetProfile()
{
    delete ui;
}


void PetProfile::setPDisplay(const Pet &value)
{
    pDisplay = value;

    fetchPet();
}

/* Method that fetches all the details about the pet and displays them
 * on pet's profile popup window
 */
void PetProfile::fetchPet()
{
    // Populates labels with the pet's information
    ui->label_name->setText(pDisplay.getName());
    ui->label_breed->setText(pDisplay.getBreed());
    ui->label_age->setText(QString::number(pDisplay.getAge()));
    ui->label_color->setText(pDisplay.getColor());
    ui->label_weight->setText(QString::number(pDisplay.getWeight()));
    ui->label_origin->setText(pDisplay.getOrigin());
    ui->label_hair->setText(pDisplay.getHairLength());
    ui->descriptionBox->setPlainText(pDisplay.getDescription());

    // Checks if the pet is cat and displays its type
    if (pDisplay.getIs_cat())
        ui->label_type->setText("Cat");
    else
        ui->label_type->setText("Dog");

    // Checks if the pet is hypoallergenic and displays it
    if (pDisplay.getHypoallergenic())
        ui->label_hypo->setText("Yes");
    else
        ui->label_hypo->setText("No");

    QSqlQuery query;
    query.prepare("select shelter.owner_id, shelter.location_id "
                  "from pet "
                  "inner join shelter on shelter.shelter_id = pet.shelter_id "
                  "where pet.pet_id = ?");
    query.addBindValue(pDisplay.getPet_id());

    if (query.exec()) {
        if (query.next()) {
            int ownerIndex = query.record().indexOf("owner_id");
            int ownerID = query.value(ownerIndex).toInt();

            int locIndex = query.record().indexOf("location_id");
            int locID = query.value(locIndex).toInt();

            Location loc(locID);
            ui->label_location->setText(loc.getCity());

            double distance = distanceToUser(loc, currentUser); // distance between the user's and the pet's locations
            // Display the distance
            if (distance == 1)
                ui->label_distance->setText("1 mile");
            else
                ui->label_distance->setText(QString::number(distance) + " miles");

            ShelterOwner owner(ownerID); // creates an instance of ShelterOwner class
            ui->label_shelter->setText(owner.getFirstName() + " " + owner.getLastName());
            ui->label_email->setText(owner.getEmail());
            ui->label_phone->setText(owner.getPhoneNumber());
        }
    }
}

/* Method to jump back to Search page and close the pet profile
 * popup window
 */
void PetProfile::on_backToSearchButton_clicked()
{
    close();
}
