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
