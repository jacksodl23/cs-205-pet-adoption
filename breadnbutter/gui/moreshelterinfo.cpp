#include "moreshelterinfo.h"
#include "ui_moreshelterinfo.h"

MoreShelterInfo::MoreShelterInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoreShelterInfo)
{
    ui->setupUi(this);
}

MoreShelterInfo::~MoreShelterInfo()
{
    delete ui;
}
