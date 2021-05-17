#include "petownerhelp.h"
#include "ui_petownerhelp.h"
#include "petliked.h"
#include "petdisplay.h"
#include "createaccount.h"
#include "mainwindow.h"

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
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

void petownerhelp::on_actionQuit_triggered()
{
   QApplication::quit();
}

void petownerhelp::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
