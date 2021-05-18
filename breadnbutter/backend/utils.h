#include <vector>
#include <pair>
#include <algorithm>

std::vector<std::pair<Pet, float>> sortByMatch(std::vector<Pet> pets) {
  std::vector<std::pair<Pet, float>> petScore;
  
  for (auto& p : pets) 
    petScore.pushback(p, getScore(currentUser, p));
  
  std::sort(petScore.begin(), petScore.end(), 
    [](const std::pair<Pet, float>& a, const std::pair<Pet, float>& b) -> bool
    {
      return a.second > b.second; 
    });
  
  return petScore;
}

float getScore(user, pet) {
  return 1;
}
