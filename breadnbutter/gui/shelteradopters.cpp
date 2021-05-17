#include "shelteradopters.h"
#include "ui_shelteradopters.h"

ShelterAdopters::ShelterAdopters(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShelterAdopters)
{
    ui->setupUi(this);
}

ShelterAdopters::~ShelterAdopters()
{
    delete ui;
}

void ShelterAdopters::on_actionQuit_triggered()
{
   QApplication::quit();
}

void ShelterAdopters::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
