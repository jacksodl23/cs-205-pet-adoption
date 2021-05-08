#include "shelterprofilesqlmodel.h"

ShelterProfileSqlModel::ShelterProfileSqlModel()
{

}

bool ShelterProfileSqlModel::ShelterProfileSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int petID = data(primaryKeyIndex).toInt();

    QModelIndex attKeyIndex = QSqlQueryModel::index(index.row(), 3);
    int attID = data(attKeyIndex).toInt();

    QModelIndex shelterKeyIndex = QSqlQueryModel::index(index.row(), 2);
    int shelterID = data(shelterKeyIndex).toInt();

    clear();

    bool ok;
    switch (index.column()) {
    case 1:
        ok = setName(petID, value.toString());
        break;
    case 4:
        ok = setColor(petID, value.toString());
        break;
    case 5:
        ok = setHairLength(petID, value.toString());
        break;
    case 6:
        ok = setDescription(petID, value.toString());
    default:
        break;
    }

    if (ok) {
        QSqlQuery query;
        query.prepare("select * "
                      "from pet "
                      "inner join pet_attributes on pet_attributes.pet_att_id = pet.pet_attribute_id "
                      "where pet.shelter_id = ?");
        query.addBindValue(shelterID);

        setQuery(query);
    }

    return ok;
}

bool ShelterProfileSqlModel::setName(int petID, const QString &pName)
{
    QSqlQuery query;
    query.prepare("update pet set name = ? where pet_id = ?");
    query.addBindValue(pName);
    query.addBindValue(petID);
    return query.exec();
}

bool ShelterProfileSqlModel::setColor(int petID, const QString &pColor)
{
    QSqlQuery query;
    query.prepare("update pet set color = ? where pet_id = ?");
    query.addBindValue(pColor);
    query.addBindValue(petID);
    return query.exec();
}

bool ShelterProfileSqlModel::setHairLength(int petID, const QString &pHairLen)
{
    QSqlQuery query;
    query.prepare("update pet set hair_length = ? where pet_id = ?");
    query.addBindValue(pHairLen);
    query.addBindValue(petID);
    return query.exec();
}

bool ShelterProfileSqlModel::setDescription(int petID, const QString &pDesc)
{
    QSqlQuery query;
    query.prepare("update pet set description = ? where pet_id = ?");
    query.addBindValue(pDesc);
    query.addBindValue(petID);
    return query.exec();
}

Qt::ItemFlags ShelterProfileSqlModel::ShelterProfileSqlModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}
