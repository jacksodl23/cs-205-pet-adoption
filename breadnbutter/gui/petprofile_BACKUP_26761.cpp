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
}

PetProfile::~PetProfile()
{
    delete ui;
}

<<<<<<< HEAD
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
=======
void PetProfile::on_backToSearchButton_clicked()
{
    close();
>>>>>>> refs/heads/gui
}
