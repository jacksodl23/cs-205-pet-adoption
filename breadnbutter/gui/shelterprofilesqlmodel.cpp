#include "shelterprofilesqlmodel.h"

ShelterProfileSqlModel::ShelterProfileSqlModel()
{

}

/* Handles editing the contents of the table.
 * Retrives both the ID of the pet and of its shelter.
 * Conducts a check as to which column is being edited.
 * Calls the appropriate update statement to edit the table.
 * Refreshes if an edit has successfully been made.
 */
bool ShelterProfileSqlModel::ShelterProfileSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int petID = data(primaryKeyIndex).toInt();

    QModelIndex shelterKeyIndex = QSqlQueryModel::index(index.row(), 2);
    int shelterID = data(shelterKeyIndex).toInt();

    QString queryStr = query().executedQuery(); // Retains the previously executed query to allow for refreshing the table.
    queryStr.replace("?", QString::number(shelterID));
    qDebug() << "Executed query" << queryStr;

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

    if (ok) {
        setQuery(queryStr);
    }

    return ok;
}

bool ShelterProfileSqlModel::removeRow(int row, const QModelIndex &parent)
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(row, 0);
    int petID = data(primaryKeyIndex).toInt();

    QModelIndex shelterIDIndex = QSqlQueryModel::index(row, 2);
    int shelterID = data(shelterIDIndex).toInt();

    QString queryStr = query().executedQuery();
    queryStr.replace("?", QString::number(shelterID));

    clear();

    QSqlQuery deleteQuery;
    deleteQuery.prepare("delete from pet where pet_id = ?");
    deleteQuery.addBindValue(petID);

    bool ok = deleteQuery.exec();

    if (ok) {
        setQuery(queryStr);
    }

    return ok;
}

// sets the name of a pet.
bool ShelterProfileSqlModel::setName(int petID, const QString &pName)
{
    QSqlQuery query;
    query.prepare("update pet set name = ? where pet_id = ?");
    query.addBindValue(pName);
    query.addBindValue(petID);
    return query.exec();
}

// sets the color of a pet.
bool ShelterProfileSqlModel::setColor(int petID, const QString &pColor)
{
    QSqlQuery query;
    query.prepare("update pet set color = ? where pet_id = ?");
    query.addBindValue(pColor);
    query.addBindValue(petID);
    return query.exec();
}

// sets the hair length of a pet.
bool ShelterProfileSqlModel::setHairLength(int petID, const QString &pHairLen)
{
    QSqlQuery query;
    query.prepare("update pet set hair_length = ? where pet_id = ?");
    query.addBindValue(pHairLen);
    query.addBindValue(petID);
    return query.exec();
}

// sets the description of a pet.
bool ShelterProfileSqlModel::setDescription(int petID, const QString &pDesc)
{
    QSqlQuery query;
    query.prepare("update pet set description = ? where pet_id = ?");
    query.addBindValue(pDesc);
    query.addBindValue(petID);
    return query.exec();
}

// sets whehter or not the pet is a cat.
bool ShelterProfileSqlModel::setIsCat(int petID, const int &pIsCat)
{
    QSqlQuery query;
    query.prepare("update pet set is_cat = ? where pet_id = ?");
    query.addBindValue(pIsCat);
    query.addBindValue(petID);
    return query.exec();
}

// sets the age of a pet.
bool ShelterProfileSqlModel::setAge(int petID, const int &pAge)
{
    QSqlQuery query;
    query.prepare("update pet set age = ? where pet_id = ?");
    query.addBindValue(pAge);
    query.addBindValue(petID);
    return query.exec();
}

// sets the breed of a pet.
bool ShelterProfileSqlModel::setBreed(int petID, const QString &pBreed)
{
    QSqlQuery query;
    query.prepare("update pet set breed = ? where pet_id = ?");
    query.addBindValue(pBreed);
    query.addBindValue(petID);
    return query.exec();
}

// sets the weight of a pet.
bool ShelterProfileSqlModel::setWeight(int petID, const float &pWeight)
{
    QSqlQuery query;
    query.prepare("update pet set weight = ? where pet_id = ?");
    query.addBindValue(pWeight);
    query.addBindValue(petID);
    return query.exec();
}

// sets the origin of a pet.
bool ShelterProfileSqlModel::setOrigin(int petID, const QString &pOrigin)
{
    QSqlQuery query;
    query.prepare("update pet set origin = ? where pet_id = ?");
    query.addBindValue(pOrigin);
    query.addBindValue(petID);
    return query.exec();
}

// sets the hypoallergenic status of a pet.
bool ShelterProfileSqlModel::setHypo(int petID, const int &pHypo)
{
    QSqlQuery query;
    query.prepare("update pet set hypoallergenic = ? where pet_id = ?");
    query.addBindValue(pHypo);
    query.addBindValue(petID);
    return query.exec();
}

// makes every column in the table editable.
Qt::ItemFlags ShelterProfileSqlModel::ShelterProfileSqlModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}
