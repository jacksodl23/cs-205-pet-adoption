#include "petownerhelp.h"
#include "ui_petownerhelp.h"

petownerhelp::petownerhelp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::petownerhelp)
{
    ui->setupUi(this);
}

petownerhelp::~petownerhelp()
{
    delete ui;
}
