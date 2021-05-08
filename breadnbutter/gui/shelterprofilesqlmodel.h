#ifndef SHELTERPROFILESQLMODEL_H
#define SHELTERPROFILESQLMODEL_H

#include <QSqlQueryModel>
#include <QtSql>

class ShelterProfileSqlModel : public QSqlQueryModel
{
public:
    ShelterProfileSqlModel();
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setName(int petID, const QString &pName);
    bool setColor(int petID, const QString &pColor);
    bool setHairLength(int petID, const QString &pHairLen);
    bool setDescription(int petID, const QString &pDesc);

    bool setIsCat(int attID, const int &pIsCat);
    bool setAge(int attID, const int &pAge);
    bool setBreed(int attID, const QString &pBreed);
    bool setWeight(int attID, const float &pWeight);
    bool setOrigin(int attID, const QString &pOrigin);
    bool setHypo(int attID, const int &pHypo);
};

#endif // SHELTERPROFILESQLMODEL_H
