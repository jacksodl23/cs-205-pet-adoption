#include "location.h"

Location::Location(int id)
{
    this->locID = id;

    QSqlQuery query;
    query.prepare("select * from location where location_id = ?");
    query.addBindValue(id);
    if (query.exec()) {
        if (query.next()) {
            int cityIndex = query.record().indexOf("city");
            int stateIndex = query.record().indexOf("state");
            int countryIndex = query.record().indexOf("country");
            int lattIndex = query.record().indexOf("lattitude");
            int longIndex = query.record().indexOf("longitude");

            this->city = query.value(cityIndex).toString();
            this->state = query.value(stateIndex).toString();
            this->country = query.value(countryIndex).toString();
            this->lattitude = query.value(lattIndex).toFloat();
            this->longitude = query.value(longIndex).toFloat();
        }
    } else {
        qDebug() << "Error getting location info:" << query.lastError().text();
    }
}

QString Location::getCity() const
{
    return city;
}

QString Location::getState() const
{
    return state;
}

QString Location::getCountry() const
{
    return country;
}

float Location::getLattitude() const
{
    return lattitude;
}

float Location::getLongitude() const
{
    return longitude;
}

int Location::getLocID() const
{
    return locID;
}
