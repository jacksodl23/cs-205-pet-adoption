#include "petownerhelp.h"
#include "ui_petownerhelp.h"
#include "petliked.h"
#include "petdisplay.h"
#include "login.h"

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

void petownerhelp::on_actionLiked_triggered()
{
    hide();
    PetLiked *likedUI = new PetLiked(this);
    likedUI->setAttribute(Qt::WA_DeleteOnClose);
    likedUI->show();
}

void petownerhelp::on_actionSearch_triggered()
{
    hide();
    PetDisplay *petUI = new PetDisplay(this);
    petUI->setAttribute(Qt::WA_DeleteOnClose);
    petUI->show();
}

void petownerhelp::on_actionLog_out_triggered()
{
    hide();
    Login *login = new Login(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}
