#include "shelterprofilesqlmodel.h"

ShelterProfileSqlModel::ShelterProfileSqlModel()
{

}

bool ShelterProfileSqlModel::ShelterProfileSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int petID = data(primaryKeyIndex).toInt();

    QModelIndex shelterKeyIndex = QSqlQueryModel::index(index.row(), 2);
    int shelterID = data(shelterKeyIndex).toInt();

    clear();

    bool ok;
    switch (index.column()) {
    case 1:
        ok = setName(petID, value.toString());
        break;
    case 3:
        ok = setColor(petID, value.toString());
        break;
    case 4:
        ok = setHairLength(petID, value.toString());
        break;
    case 5:
        ok = setIsCat(petID, value.toInt());
        break;
    case 6:
        ok = setAge(petID, value.toInt());
        break;
    case 7:
        ok = setBreed(petID, value.toString());
        break;
    case 8:
        ok = setWeight(petID, value.toFloat());
        break;
    case 9:
        ok = setOrigin(petID, value.toString());
        break;
    case 10:
        ok = setHypo(petID, value.toInt());
        break;
    case 11:
        ok = setDescription(petID, value.toString());
        break;
    default:
        break;
    }

    /*if (ok) {
        QSqlQuery query;
        query.prepare("select * "
                      "from pet "
                      "where pet.shelter_id = ?");
        query.addBindValue(shelterID);

        setQuery(query);
    } else {
        qDebug() << "Something went wrong while updating.";
    } */

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
    qDebug() << "Setting hair length to" << pHairLen;

    QSqlQuery query;
    query.prepare("update pet set hair_length = ? where pet_id = ?");
    query.addBindValue(pHairLen);
    query.addBindValue(petID);
    return query.exec();
}

bool ShelterProfileSqlModel::setDescription(int petID, const QString &pDesc)
{
    qDebug() << "Setting description to" << pDesc;

    QSqlQuery query;
    query.prepare("update pet set description = ? where pet_id = ?");
    query.addBindValue(pDesc);
    query.addBindValue(petID);
    return query.exec();
}

bool ShelterProfileSqlModel::setIsCat(int petID, const int &pIsCat)
{
    QSqlQuery query;
    query.prepare("update pet set is_cat = ? where pet_id = ?");
    query.addBindValue(petID);
    query.addBindValue(pIsCat);
    return query.exec();
}

bool ShelterProfileSqlModel::setAge(int petID, const int &pAge)
{
    qDebug() << "Setting age to" << pAge;

    QSqlQuery query;
    query.prepare("update pet set age = ? where pet_id = ?");
    query.addBindValue(petID);
    query.addBindValue(pAge);
    return query.exec();
}

bool ShelterProfileSqlModel::setBreed(int petID, const QString &pBreed)
{
    QSqlQuery query;
    query.prepare("update pet set breed = ? where pet_id = ?");
    query.addBindValue(petID);
    query.addBindValue(pBreed);
    return query.exec();
}

bool ShelterProfileSqlModel::setWeight(int petID, const float &pWeight)
{
    qDebug() << "Setting weight to" << pWeight;

    QSqlQuery query;
    query.prepare("update pet set weight = ? where pet_id = ?");
    query.addBindValue(petID);
    query.addBindValue(pWeight);
    return query.exec();
}

bool ShelterProfileSqlModel::setOrigin(int petID, const QString &pOrigin)
{
    qDebug() << "Setting origin to" << pOrigin;

    QSqlQuery query;
    query.prepare("update pet set origin = ? where pet_id = ?");
    query.addBindValue(petID);
    query.addBindValue(pOrigin);
    return query.exec();
}

bool ShelterProfileSqlModel::setHypo(int petID, const int &pHypo)
{
    QSqlQuery query;
    query.prepare("update pet set hypoallergenic = ? where pet_id = ?");
    query.addBindValue(petID);
    query.addBindValue(pHypo);
    return query.exec();
}

Qt::ItemFlags ShelterProfileSqlModel::ShelterProfileSqlModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}
