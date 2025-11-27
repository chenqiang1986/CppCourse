#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Cow{
    int id;
    std::vector<std::map<int, int>>* cow_to_locations;

    bool operator<(const Cow& other)const{
        int num_times_less_than = 0;
        for(int i = 0; i < 5; i++){
            if((*cow_to_locations)[i][id] < (*cow_to_locations)[i][other.id]){
                num_times_less_than++;
            }
        }
        return num_times_less_than >= 3;
    }
};

int main(){
    int n;
    std::cin >> n;
    std::set<int> cows;
    std::vector<std::map<int, int>> cow_to_locations;
    for(int j = 0; j < 5; j++){
        std::map<int, int> cow_to_location;
        for(int i = 0; i < n; i++){
            int cow;
            std::cin >> cow;
            cow_to_location[cow] = i;
            cows.insert(cow);
        }
        cow_to_locations.push_back(cow_to_location);
    }
    std::vector<Cow> row_of_cows;
    for(auto cow : cows){
        row_of_cows.push_back(Cow{.id = cow, .cow_to_locations = &cow_to_locations});
    }
    std::sort(row_of_cows.begin(), row_of_cows.end());
    for(int i = 0; i < n; i++){
        std::cout << row_of_cows[i].id << std::endl;
    }
    return 0;
}
