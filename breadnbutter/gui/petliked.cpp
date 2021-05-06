#include "petliked.h"
#include "ui_petliked.h"
#include "petownerhelp.h"
#include "petdisplay.h"
#include "createaccount.h"
#include "mainwindow.h"

void PetLiked::fetchLikedPets()
{
    QSqlQuery query;
    query.prepare("select pet_id from liked_by where adopter_id = ?");
    query.addBindValue(currentUser.getID());


    // TODO add num of liked pets to this page as well
    ui->statusbar->showMessage("You have liked 1 pet.");

    if (query.exec()) {
        while (query.next()) {
            int pID = query.value(0).toInt();

            Pet p(pID);
            pets.push_back(p);
        }
    } else {
        qDebug() << "Error getting liked pets:" << query.lastError().text();
    }
}

void PetLiked::displayPet(Pet p)
{
    if (currentPos == 0)
        ui->button_prev->setEnabled(false);
    if (currentPos == pets.size())
        ui->button_next->setEnabled(false);

    ui->label_name->setText(p.getName());
    ui->label_age->setText(QString::number(p.getAge()));

    if (!p.getIs_cat())
        ui->label_type->setText("Dog");
    else
        ui->label_type->setText("Cat");

    ui->label_color->setText(p.getColor());
    ui->label_breed->setText(p.getBreed());

    if (!p.getHypoallergenic())
        ui->label_hypo->setText("No");
    else
        ui->label_hypo->setText("Yes");

    ui->label_origin->setText(p.getOrigin());

    QSqlQuery query;
    query.prepare("select location from Shelter "
                  "inner join Pet on Pet.shelter_id = Shelter.shelter_id "
                  "where Pet.pet_id = ?");
    query.addBindValue(p.getPet_id());

    if (query.exec()) {
        if (query.next()) {
            QString loc = query.value(0).toString();

            ui->label_location->setText(loc);
        } else {
            ui->button_next->setEnabled(false);
            ui->button_prev->setEnabled(false);
        }
    }

    ui->descriptionDisplay->setPlainText(p.getDescription());
}

PetLiked::PetLiked(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::petliked)
{
    ui->setupUi(this);
    currentPos = 0;
    ui->button_prev->setEnabled(false);

    fetchLikedPets();
    displayPet(pets.at(currentPos));
}

PetLiked::~PetLiked()
{
    delete ui;
}

void PetLiked::on_button_next_clicked()
{
    if (!(currentPos + 1 > pets.size() - 1)) {
        currentPos++;
        displayPet(pets.at(currentPos));

        if (!ui->button_prev->isEnabled())
            ui->button_prev->setEnabled(true);
    } else {
        ui->button_next->setEnabled(false);
    }
}

void PetLiked::on_button_prev_clicked()
{
    if (!(currentPos - 1 < 0)) {
        currentPos--;
        displayPet(pets.at(currentPos));

        if (!ui->button_next->isEnabled())
            ui->button_next->setEnabled(true);
    }
}

void PetLiked::on_actionLog_out_triggered()
{
    hide();
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

void PetLiked::on_actionHelp_triggered()
{
    hide();
    petownerhelp *helpUI = new petownerhelp(this);
    helpUI->setAttribute(Qt::WA_DeleteOnClose);
    helpUI->show();
}

void PetLiked::on_actionSearch_triggered()
{
    hide();
    PetDisplay *petUI = new PetDisplay(this);
    petUI->setAttribute(Qt::WA_DeleteOnClose);
    petUI->show();
}
