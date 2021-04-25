#include "shelterupload.h"
#include "ui_shelterupload.h"

shelterUpload::shelterUpload(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterUpload)
{
    ui->setupUi(this);
}

shelterUpload::~shelterUpload()
{
    delete ui;
}

void shelterUpload::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Dog"){
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("German Shepherd");
        ui->comboBox_2->addItem("Golden Retriever");
        ui->comboBox_2->addItem("Bulldog");
        ui->comboBox_2->addItem("Poodle");
        ui->comboBox_2->addItem("Chihuahua");
    }
    else if(arg1 == "Cat"){
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("Persian cat");
        ui->comboBox_2->addItem("Bengal cat");
        ui->comboBox_2->addItem("Siamese cat");
        ui->comboBox_2->addItem("Sphynx cat");
        ui->comboBox_2->addItem("Siberian cat");
    }
    else if(arg1 == "Snake"){
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("Cobra");
        ui->comboBox_2->addItem("Python");
        ui->comboBox_2->addItem("Copperhead");
    }
    else if(arg1 == "Hamster"){
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("Syrian hamster");
        ui->comboBox_2->addItem("Winter White hamster");
        ui->comboBox_2->addItem("Chinese hamster");
        ui->comboBox_2->addItem("Roborowski hamster");
        ui->comboBox_2->addItem("Campbell's Dwarf hamster");
    }
}


void shelterUpload::on_comboBox_2_activated(const QString &arg1)
{
    this->breed = arg1;
}

void shelterUpload::on_comboBox_3_activated(const QString &arg1)
{
    this->color = arg1;
}

void shelterUpload::on_comboBox_4_activated(const QString &arg1)
{
    this->allergy = arg1;
}

void shelterUpload::on_comboBox_5_activated(const QString &arg1)
{
    this->hairLength = arg1;
}

void shelterUpload::on_pushButton_clicked()
{
    this->name = ui->lineEdit_4->text();
    this->age = ui->lineEdit->text().toInt();
    this->weight = ui->lineEdit_2->text().toFloat();
    this->origin = ui->lineEdit_3->text();
    this->description = ui->lineEdit_5->text();

    Pet newPet(name, age, breed, color, hairLength, weight, origin, allergy, description);
    bool check = newPet.insertIntoDB();

    if(check){
        QMessageBox::information(this, "Successful!", "Yay! You've added a new pet!");
    }
}
