#include "petprofile.h"
#include "ui_petprofile.h"

PetProfile::PetProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PetProfile)
{
    ui->setupUi(this);

    QString photoFilePath(":/resources/imgs/petPhoto0.jpg");
    petPic.load(photoFilePath);
    int width = ui->animalDisplay->width();
    int height = ui->animalDisplay->height();
    ui->animalDisplay->setPixmap(petPic.scaled(width, height, Qt::KeepAspectRatio));
}

PetProfile::~PetProfile()
{
    delete ui;
}

void PetProfile::on_backToSearchButton_clicked()
{
    close();
}
