#ifndef SHELTERPROFILESQLMODEL_H
#define SHELTERPROFILESQLMODEL_H

#include <QSqlQueryModel>
#include <QtSql>

class ShelterProfileSqlModel : public QSqlQueryModel
{
public:
    ShelterProfileSqlModel();

    // handles editing of table.
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    // deletes selected row.
    bool removeRow(int row, const QModelIndex &parent);

private:
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // sets name of pet.
    bool setName(int petID, const QString &pName);

    // sets color of pet.
    bool setColor(int petID, const QString &pColor);

    // sets hair length of pet.
    bool setHairLength(int petID, const QString &pHairLen);

    // sets description of pet.
    bool setDescription(int petID, const QString &pDesc);

    // sets whether or not pet is a cat.
    bool setIsCat(int petID, const int &pIsCat);

    // sets age of pet.
    bool setAge(int petID, const int &pAge);

    // sets breed of pet.
    bool setBreed(int petID, const QString &pBreed);

    // sets weight of pet.
    bool setWeight(int petID, const float &pWeight);

    // sets origin of pet.
    bool setOrigin(int petID, const QString &pOrigin);

    // sets hypoallergenic status of pet.
    bool setHypo(int petID, const int &pHypo);
};

#endif // SHELTERPROFILESQLMODEL_H
