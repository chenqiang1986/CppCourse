#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

long find_min_length(const std::vector<long>& breeds, const std::vector<long>& positions, int total_breed_count){
    long min_length = 500000000000000;
    int start = 0;
    int end = 0;
    std::map<int, int> running = {{breeds[0], 1}};
    while(end < breeds.size()){
        int breed_count = running.size();
        if(breed_count < total_breed_count){
            end++;
            if(end < breeds.size()){
                running[breeds[end]]++;
            }
        }
        else if(breed_count == total_breed_count){
            min_length = std::min(min_length, positions[end] - positions[start]);
            running[breeds[start]]--;
            if(running[breeds[start]] == 0){
                running.erase(breeds[start]);
            }
            start++;
        }
    }
    return min_length;
}

int main(){
    int n;
    std::cin >> n;
    std::vector<long> positions;
    std::vector<long> breeds;
    std::set<long> breed_types;
    std::map<long, long> pos_to_breed;
    for(int i = 0; i < n; i++){
        long pos, breed;
        std::cin >> pos >> breed;
        breed_types.insert(breed);
        pos_to_breed[pos] = breed;
    }
    for(auto [pos, breed] : pos_to_breed){
        positions.push_back(pos);
        breeds.push_back(breed);
    }
    std::cout << find_min_length(breeds, positions, breed_types.size()) << std::endl;
    return 0;
}
