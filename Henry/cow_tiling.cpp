#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int dfs(const std::vector<int>& curr_tiles, std::map<std::pair<int, int>, int>& cache, int target_area, int curr_index){
    std::pair<int, int> cache_key(target_area, curr_index);
    if(cache.count(cache_key) != 0){
        return cache[cache_key];
    }
    int min_cost = 1000000;
    if(curr_index >= curr_tiles.size()){
        if(target_area == 0){
            cache[cache_key] = 0;
            return 0;
        }
        else{
            cache[cache_key] = min_cost;
            return min_cost;
        }
    }
    for(int new_size = 1; new_size * new_size <= target_area; new_size++){
        int cost = (curr_tiles[curr_index] - new_size) * (curr_tiles[curr_index] - new_size) + dfs(curr_tiles, cache, target_area - new_size * new_size, curr_index + 1);
        min_cost = std::min(min_cost, cost);
    }
    cache[cache_key] = min_cost;
    return min_cost;
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
    std::map<std::pair<int, int>, int> cache;
    int min_cost = dfs(curr_tiles, cache, m, 0);
    if(min_cost >= 1000000){
        std::cout << -1 << std::endl;
    }
    else{
        std::cout << min_cost << std::endl;
    }
    return 0;
}
