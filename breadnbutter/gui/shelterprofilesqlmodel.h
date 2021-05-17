#ifndef SHELTERPROFILESQLMODEL_H
#define SHELTERPROFILESQLMODEL_H

#include <QSqlQueryModel>
#include <QtSql>

class ShelterProfileSqlModel : public QSqlQueryModel
{
public:
    ShelterProfileSqlModel();
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRow(int row, const QModelIndex &parent);

private:
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setName(int petID, const QString &pName);
    bool setColor(int petID, const QString &pColor);
    bool setHairLength(int petID, const QString &pHairLen);
    bool setDescription(int petID, const QString &pDesc);

    bool setIsCat(int petID, const int &pIsCat);
    bool setAge(int petID, const int &pAge);
    bool setBreed(int petID, const QString &pBreed);
    bool setWeight(int petID, const float &pWeight);
    bool setOrigin(int petID, const QString &pOrigin);
    bool setHypo(int petID, const int &pHypo);
};

#endif // SHELTERPROFILESQLMODEL_H
