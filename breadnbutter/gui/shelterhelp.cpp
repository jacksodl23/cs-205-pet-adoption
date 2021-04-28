#include "shelterhelp.h"
#include "ui_shelterhelp.h"

shelterhelp::shelterhelp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterhelp)
{
    ui->setupUi(this);
}

shelterhelp::~shelterhelp()
{
    delete ui;
}
