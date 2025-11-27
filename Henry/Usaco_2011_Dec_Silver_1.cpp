#include <iostream>
#include <map>
#include <set>
#include <vector>

struct IsGreaterThan{
    // A is greater than B
    int a;
    int b;
};

std::vector<IsGreaterThan> find_comparators(
    std::vector<int>& photo1, 
    std::vector<int>& photo2, 
    std::vector<int>& photo3, 
    std::vector<int>& photo4, 
    std::vector<int>& photo5, 
    std::map<int, int>& cow_to_location1, 
    std::map<int, int>& cow_to_location2, 
    std::map<int, int>& cow_to_location3, 
    std::map<int, int>& cow_to_location4, 
    std::map<int, int>& cow_to_location5
){
    std::vector<IsGreaterThan> comparators;
    for(int i = 0; i < photo1.size(); i++){
        for(int j = 0; j < photo1.size(); j++){
            if(i < j){
                int num_times_first_less_than_second = 1;
                if(cow_to_location2[photo1[i]] < cow_to_location2[photo1[j]]){
                    num_times_first_less_than_second++;
                }
                if(cow_to_location3[photo1[i]] < cow_to_location3[photo1[j]]){
                    num_times_first_less_than_second++;
                }
                if(cow_to_location4[photo1[i]] < cow_to_location4[photo1[j]]){
                    num_times_first_less_than_second++;
                }
                if(cow_to_location5[photo1[i]] < cow_to_location5[photo1[j]]){
                    num_times_first_less_than_second++;
                }
                if(num_times_first_less_than_second <= 2){
                    comparators.push_back(IsGreaterThan{.a = photo1[i], .b = photo1[j]});
                }
                else{
                    comparators.push_back(IsGreaterThan{.a = photo1[j], .b = photo1[i]});
                }
            }
        }
    }
    return comparators;
}

int main(){
    int n;
    std::cin >> n;
    std::set<int> cows;
    std::vector<int> photo1;
    std::vector<int> photo2;
    std::vector<int> photo3;
    std::vector<int> photo4;
    std::vector<int> photo5;
    std::map<int, int> cow_to_location1;
    std::map<int, int> cow_to_location2;
    std::map<int, int> cow_to_location3;
    std::map<int, int> cow_to_location4;
    std::map<int, int> cow_to_location5;
    for(int i = 0; i < n; i++){
        int cow;
        std::cin >> cow;
        photo1.push_back(cow);
        cow_to_location1[cow] = i;
        cows.insert(cow);
    }
    for(int i = 0; i < n; i++){
        int cow;
        std::cin >> cow;
        photo2.push_back(cow);
        cow_to_location2[cow] = i;
    }
    for(int i = 0; i < n; i++){
        int cow;
        std::cin >> cow;
        photo3.push_back(cow);
        cow_to_location3[cow] = i;
    }
    for(int i = 0; i < n; i++){
        int cow;
        std::cin >> cow;
        photo4.push_back(cow);
        cow_to_location4[cow] = i;
    }
    for(int i = 0; i < n; i++){
        int cow;
        std::cin >> cow;
        photo5.push_back(cow);
        cow_to_location5[cow] = i;
    }
    std::vector<IsGreaterThan> comparators = find_comparators(photo1, photo2, photo3, photo4, photo5, cow_to_location1, cow_to_location2, cow_to_location3, cow_to_location4, cow_to_location5);
    std::map<int, int> cow_to_index;
    for(int i = 0; i < comparators.size(); i++){
        cow_to_index[comparators[i].a]++;
    }
    std::vector<int> row_of_cows (n, 0);
    for(auto [cow, index] : cow_to_index){
        row_of_cows[index] = cow;
    }
    for(int i = 1; i < n; i++){
        cows.erase(row_of_cows[i]);
    }
    for(auto cow : cows){
        row_of_cows[0] = cow;
    }
    for(int i = 0; i < n; i++){
        std::cout << row_of_cows[i] << std::endl;
    }
    return 0;
}
