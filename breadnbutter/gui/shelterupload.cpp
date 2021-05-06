#include "shelterupload.h"
#include "ui_shelterupload.h"
#include "shelterhelp.h"
#include "shelterprofile.h"
#include "createaccount.h"
#include "mainwindow.h"

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

void shelterUpload::on_typeBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Dog"){
        this->is_cat = false;
        ui->breedBox->clear();
        ui->breedBox->addItem("German Shepherd");
        ui->breedBox->addItem("Golden Retriever");
        ui->breedBox->addItem("Bulldog");
        ui->breedBox->addItem("Poodle");
        ui->breedBox->addItem("Chihuahua");
    }
    else if(arg1 == "Cat"){
        this->is_cat = true;
        ui->breedBox->clear();
        ui->breedBox->addItem("Persian cat");
        ui->breedBox->addItem("Bengal cat");
        ui->breedBox->addItem("Siamese cat");
        ui->breedBox->addItem("Sphynx cat");
        ui->breedBox->addItem("Siberian cat");
    }
    else if(arg1 == "Snake"){
        this->is_cat = false;
        ui->breedBox->clear();
        ui->breedBox->addItem("Cobra");
        ui->breedBox->addItem("Python");
        ui->breedBox->addItem("Copperhead");
    }
    else if(arg1 == "Hamster"){
        this->is_cat = false;
        ui->breedBox->clear();
        ui->breedBox->addItem("Syrian hamster");
        ui->breedBox->addItem("Winter White hamster");
        ui->breedBox->addItem("Chinese hamster");
        ui->breedBox->addItem("Roborowski hamster");
        ui->breedBox->addItem("Campbell's Dwarf hamster");
    }
}

void shelterUpload::on_colorBox_activated(const QString &arg1)
{
    this->color = arg1;
}

void shelterUpload::on_hairLenBox_activated(const QString &arg1)
{
    this->hairLength = arg1;
}

void shelterUpload::on_breedBox_activated(const QString &arg1)
{
    this->breed = arg1;
}

void shelterUpload::on_hypoBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Yes"){
        this->hypoallergenic = true;
    }
    else{
        this->hypoallergenic = false;
    }
}

void shelterUpload::on_cancelButton_clicked()
{
    hide();
    parentWidget()->show();
}

void shelterUpload::on_addButton_clicked()
{
    this->name = ui->nameField->text();
    this->age = ui->ageField->text().toInt();
    this->weight = ui->weightField->text().toFloat();
    this->origin = ui->originField->text();
    this->description = ui->descriptionTextEdit->toPlainText();

    Pet newPet(is_cat,name,age,breed,color,hairLength,weight,origin,hypoallergenic,description);

    bool check = newPet.insertIntoDB(shelter->getShelterID());

    if(check){
        QMessageBox::information(this, "Successful!", "Yay! You've added a new pet!");
    }
}

void shelterUpload::setShelter(Shelter *value)
{
    shelter = value;
}

void shelterUpload::on_actionProfile_triggered()
{
    shelterProfile *w = new shelterProfile(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void shelterUpload::on_actionHelp_triggered()
{
    shelterhelp *w = new shelterhelp(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void shelterUpload::on_actionLog_out_triggered()
{
    hide();
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}
