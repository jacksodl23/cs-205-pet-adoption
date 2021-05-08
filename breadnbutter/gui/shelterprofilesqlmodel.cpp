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
    qDebug() << "Att id is" << attID;

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
        break;
    case 8:
        ok = setIsCat(attID, value.toInt());
        break;
    case 9:
        ok = setAge(attID, value.toInt());
        break;
    case 10:
        ok = setBreed(attID, value.toString());
        break;
    case 11:
        ok = setWeight(attID, value.toFloat());
        break;
    case 12:
        ok = setOrigin(attID, value.toString());
        break;
    case 13:
        ok = setHypo(attID, value.toInt());
        break;
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
    } else {
        qDebug() << "Something went wrong while updating.";
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

bool ShelterProfileSqlModel::setIsCat(int attID, const int &pIsCat)
{
    QSqlQuery query;
    query.prepare("update pet_attributes set is_cat = ? where pet_att_id = ?");
    query.addBindValue(attID);
    query.addBindValue(pIsCat);
    return query.exec();
}

bool ShelterProfileSqlModel::setAge(int attID, const int &pAge)
{
    QSqlQuery query;
    query.prepare("update pet_attributes set age = ? where pet_att_id = ?");
    query.addBindValue(attID);
    query.addBindValue(pAge);
    return query.exec();
}

bool ShelterProfileSqlModel::setBreed(int attID, const QString &pBreed)
{
    QSqlQuery query;
    query.prepare("update pet_attributes set breed = ? where pet_att_id = ?");
    query.addBindValue(attID);
    query.addBindValue(pBreed);
    return query.exec();
}

bool ShelterProfileSqlModel::setWeight(int attID, const float &pWeight)
{
    QSqlQuery query;
    query.prepare("update pet_attributes set weight = ? where pet_att_id = ?");
    query.addBindValue(attID);
    query.addBindValue(pWeight);
    return query.exec();
}

bool ShelterProfileSqlModel::setOrigin(int attID, const QString &pOrigin)
{
    QSqlQuery query;
    query.prepare("update pet_attributes set origin = ? where pet_att_id = ?");
    query.addBindValue(attID);
    query.addBindValue(pOrigin);
    return query.exec();
}

bool ShelterProfileSqlModel::setHypo(int attID, const int &pHypo)
{
    QSqlQuery query;
    query.prepare("update pet_attributes set hypoallergenic = ? where pet_att_id = ?");
    query.addBindValue(attID);
    query.addBindValue(pHypo);
    return query.exec();
}

Qt::ItemFlags ShelterProfileSqlModel::ShelterProfileSqlModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}
