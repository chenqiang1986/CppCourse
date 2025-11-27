#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

void optimize(std::map<int, int>& size_to_cost){
    int min = 2100000000;
    for(int i = size_to_cost.size(); i > 0; i--){
        min = std::min(min, size_to_cost[i]);
        size_to_cost[i] = min;
    }
}

int find_min_cost(const std::vector<int>& cow_positions, std::map<int, int>& size_to_cost, int starting_index, std::map<int, int>& cache){
    if(cache.count(starting_index) != 0){
        return cache[starting_index];
    }
    if(starting_index >= cow_positions.size()){
        cache[starting_index] = 0;
        return 0;
    }
    int min_cost = size_to_cost[size_to_cost.size()];
    for(int i = starting_index; i < cow_positions.size(); i++){
        int width = cow_positions[i] - cow_positions[starting_index] + 1;
        min_cost = std::min(min_cost, size_to_cost[width] + find_min_cost(cow_positions, size_to_cost, i + 1, cache));
    }
    cache[starting_index] = min_cost;
    return min_cost;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cow_positions;
    std::map<int, int> size_to_cost;
    for(int i = 0; i < n; i++){
        int cow_pos;
        std::cin >> cow_pos;
        cow_positions.push_back(cow_pos);
    }
    std::sort(cow_positions.begin(), cow_positions.end());
    for(int i = 1; i <= m; i++){
        int cost;
        std::cin >> cost;
        size_to_cost[i] = cost;
    }
    optimize(size_to_cost);
    std::map<int, int> cache;
    std::cout << find_min_cost(cow_positions, size_to_cost, 0, cache) << std::endl;
    return 0;
}
