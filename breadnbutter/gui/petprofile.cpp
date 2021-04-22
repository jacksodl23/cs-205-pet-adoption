#include "petprofile.h"
#include "ui_petprofile.h"

PetProfile::PetProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetProfile)
{
    ui->setupUi(this);
}

PetProfile::~PetProfile()
{
    delete ui;
}
