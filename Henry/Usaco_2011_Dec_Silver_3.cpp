#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int find_min_cost(const std::vector<int>& cow_positions, std::map<int, int> size_to_cost, int starting_index){
    if(starting_index >= cow_positions.size()){
        return 0;
    }
    int min_cost = size_to_cost[size_to_cost.size()];
    for(int i = starting_index; i < cow_positions.size(); i++){
        int width = cow_positions[i] - cow_positions[starting_index] + 1;
        min_cost = std::min(min_cost, size_to_cost[width] + find_min_cost(cow_positions, size_to_cost, i + 1));
    }
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
    std::cout << find_min_cost(cow_positions, size_to_cost, 0) << std::endl;
    return 0;
}
