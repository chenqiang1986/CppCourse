#include <algorithm>
#include <iostream>
#include <vector>

int dfs(const std::vector<int>& curr_tiles, int target_area, int curr_index){
    int min_cost = 1000000;
    if(curr_index >= curr_tiles.size()){
        if(target_area == 0){
            return 0;
        }
        else{
            return min_cost;
        }
    }
    for(int new_size = 1; new_size * new_size <= target_area; new_size++){
        int cost = (curr_tiles[curr_index] - new_size) * (curr_tiles[curr_index] - new_size) + dfs(curr_tiles, target_area - new_size * new_size, curr_index + 1);
        min_cost = std::min(min_cost, cost);
    }
    return min_cost;
}

int find_min_cost(const std::vector<int>& curr_tiles, int m){
    int min_cost = 1000000000;

}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<int> curr_tiles;
    for(int i = 0; i < n; i++){
        int tile;
        std::cin >> tile;
        curr_tiles.push_back(tile);
    }
    int min_cost = find_min_cost(curr_tiles, m);
    if(min_cost >= 1000000){
        std::cout << -1 << std::endl;
    }
    else{
        std::cout << min_cost << std::endl;
    }
    return 0;
}
