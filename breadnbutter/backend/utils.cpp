#include "utils.h"
#include "globals.cpp"

float getScore(PetOwner po, Pet p) {
    if (po.getWantsCat() != p.getIs_cat() || po.getAllergy() != p.getHypoallergenic()) {
        return 0;
    } else {
        return 100;
    }
}

std::vector<std::pair<Pet, float>> sortByMatch(std::vector<Pet> pets) {
    std::vector<std::pair<Pet, float>> petScore;
    srand(time(0));

    PetOwner owner(currentUser.getID());
    for (auto& p : pets)
        petScore.push_back(std::make_pair(p, getScore(owner, p)));

    std::sort(petScore.begin(), petScore.end(),
              [](const std::pair<Pet, float>& a, const std::pair<Pet, float>& b) -> bool {
        return a.second > b.second;
    });

    return petScore;
}

double distance(double lat1, double long1, double lat2, double long2) {
    // Calculates in miles. Imperial system for the win.
    // Haversine Formula
    const double pi = 3.1415926535;
    const double R = 3958.8; // radius of Earth (mi)
    lat1 *= 0.0174533;  // to radians
    long1 *= 0.0174533; // to radians
    lat2 *= 0.0174533;  // to radians
    long2 *= 0.0174533; // to radians

    double a = std::pow(std::sin((lat2-lat1)/2), 2) + std::cos(lat1)*std::cos(lat2)*std::pow(std::sin((long2-long1)/2), 2);
    return 2 * R * std::atan2(std::sqrt(a), std::sqrt(1-a));
}

double distanceToUser(const Location& start, User user) {
    Location userLoc(user.getLocID());

    return distance(start.getLattitude(), start.getLongitude(), userLoc.getLattitude(), userLoc.getLongitude());
}
