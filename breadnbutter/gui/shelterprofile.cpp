#include "shelterprofile.h"
#include "ui_shelterprofile.h"

shelterProfile::shelterProfile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterProfile)
{
    ui->setupUi(this);
}

shelterProfile::~shelterProfile()
{
    delete ui;
}
