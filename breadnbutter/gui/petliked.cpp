#include "petliked.h"
#include "ui_petliked.h"

void PetLiked::fetchLikedPets()
{
    QSqlQuery query;
    query.prepare("select pet_id from liked_by where adopter_id = ?");
    query.addBindValue(currentUser.getID());

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

    fetchLikedPets();
    displayPet(pets.at(currentPos));
}

PetLiked::~PetLiked()
{
    delete ui;
}

void PetLiked::on_button_next_clicked()
{

}

void PetLiked::on_button_prev_clicked()
{

}
