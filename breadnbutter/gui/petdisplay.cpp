#include "petdisplay.h"
#include "ui_petdisplay.h"

PetDisplay::PetDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PetDisplay)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("page number here");
}

PetDisplay::~PetDisplay()
{
    delete ui;
}
