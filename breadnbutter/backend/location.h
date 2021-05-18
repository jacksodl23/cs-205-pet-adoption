#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QtSql>

class Location
{
public:
    Location(int id);
    ~Location();

    QString getCity() const;

    QString getState() const;

    QString getCountry() const;

    float getLattitude() const;

    float getLongitude() const;

    int getLocID() const;

private:
    int locID;

    QString city;
    QString state;
    QString country;
    float lattitude;
    float longitude;
};

#endif // LOCATION_H
