#include "user.h"

User::User()
{

}

User::~User()
{

}

bool User::insertInDB()
{
    return false;
}

bool User::deleteFromDB()
{
    return false;
}

bool User::existsInDB()
{
    return false;
}

bool User::attemptLogin()
{
    return false;
}

int User::getID()
{
    return id;
}

QString User::getFirstName()
{
    return firstName;
}

void User::chooseID()
{
    std::cerr << "Choosing ID..." << std::endl;
}
