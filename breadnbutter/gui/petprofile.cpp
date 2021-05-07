#include "petprofile.h"
#include "ui_petprofile.h"

PetProfile::PetProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PetProfile)
{
    ui->setupUi(this);

    int numberOfPhotos = 8;

    srand(time(0));
    int photoNum = rand() % numberOfPhotos;

    QString photoString = QString::number(photoNum);

    QString tempPath(":/resources/imgs/petPhoto");
    tempPath.append(photoString);
    QString filePath = tempPath.append(".jpg");
    qDebug() << filePath;

    petPic.load(filePath);
    int width = ui->animalDisplay->width();
    int height = ui->animalDisplay->height();
    ui->animalDisplay->setPixmap(petPic.scaled(width, height, Qt::KeepAspectRatio));

    // adding icons to the page
    QPixmap icon;

    QString iconName(":/icons/icons/Name.png");
    icon.load(iconName);
    width = ui->icon_name->width();
    height = ui->icon_name->height();
    ui->icon_name->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

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

    QString iconHypo(":/icons/icons/Hypoallergenic.png");
    icon.load(iconHypo);
    width = ui->icon_hypoallergenica->width();
    height = ui->icon_hypoallergenic->height();
    ui->icon_hypoallergenic->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString iconLocation(":/icons/icons/Color.png");
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

PetProfile::~PetProfile()
{
    delete ui;
}


void PetProfile::setPDisplay(const Pet &value)
{
    pDisplay = value;

    fetchPet();
}

void PetProfile::fetchPet()
{
    ui->label_name->setText(pDisplay.getName());
    ui->label_breed->setText(pDisplay.getBreed());
    ui->label_age->setText(QString::number(pDisplay.getAge()));
    ui->label_color->setText(pDisplay.getColor());

    if (pDisplay.getHypoallergenic())
        ui->label_hypo->setText("Yes");
    else
        ui->label_hypo->setText("No");

    // Note for the future: see if inner joins can be used to cut down on the amount of queries.
    QSqlQuery query;
    query.prepare("select shelter_id from pet where pet_id = ?");
    query.addBindValue(pDisplay.getPet_id());

    if (query.exec()) {
        if (query.next()) {
            int shelterID = query.value(0).toInt();

            Shelter s(shelterID);
            ui->label_location->setText(s.getLocation());

            QSqlQuery q2;
            q2.prepare("select owner_id from shelter where shelter_id = ?");
            q2.addBindValue(shelterID);

            if (q2.exec()) {
                if (q2.next()) {
                    int ownerID = q2.value(0).toInt();

                    ShelterOwner owner(ownerID);
                    ui->label_shelter->setText(owner.getFirstName() + " " + owner.getLastName());
                }
            }
        }
    }
}

void PetProfile::on_backToSearchButton_clicked()
{
    close();
}
