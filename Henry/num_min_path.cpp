#include <algorithm>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::optional<int> find_least_dist_to_start(std::unordered_map<int, int>& dist_to_start, std::unordered_set<int>& visited){
    int least_dist = 2100000000;
    std::optional<int> least_dist_field = std::nullopt;
    for(auto [field, dist] : dist_to_start){
        if(visited.count(field) == 0){
            if(dist < least_dist){
                least_dist = dist;
                least_dist_field = field;
            }
        }
    }
    return least_dist_field;
}

void update_neighbors(int seed, std::unordered_map<int, std::unordered_map<int, int>>& farm, std::unordered_map<int, int>& dist_to_start, std::unordered_map<int, int>& min_ways_to_node){
    for(auto [neighbor, dist] : farm[seed]){
        int through_seed = dist + dist_to_start[seed];
        if(dist_to_start.count(neighbor) == 0 || through_seed < dist_to_start[neighbor]){
            dist_to_start[neighbor] = through_seed;
            min_ways_to_node[neighbor] = min_ways_to_node[seed];
        }
        else if(through_seed == dist_to_start[neighbor]){
            min_ways_to_node[neighbor] += min_ways_to_node[seed];
        }
    }
}

void find_min_path(std::unordered_map<int, std::unordered_map<int, int>>& farm, int start, int end, std::optional<int>& min_dist, std::optional<int>& min_dist_ways){
    std::unordered_map<int, int> dist_to_start;
    dist_to_start[start] = 0;
    std::unordered_map<int, int> min_ways_to_node;
    min_ways_to_node[start] = 1;
    std::unordered_set<int> visited;
    while(true){
        std::optional<int> seed = find_least_dist_to_start(dist_to_start, visited);
        if(! seed.has_value()){
            break;
        }
        visited.insert(*seed);
        update_neighbors(*seed, farm, dist_to_start, min_ways_to_node);
    }
    if(dist_to_start.count(end) != 0){
        min_dist = dist_to_start[end];
        min_dist_ways = min_ways_to_node[end];
    }
    else{
        min_dist = std::nullopt;
        min_dist_ways = std::nullopt;
    }
}

int main(){
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    std::unordered_map<int, std::unordered_map<int, int>> farm;
    for(int i = 0; i < m; i++){
        int start, end, length;
        std::cin >> start >> end >> length;
        farm[start][end] = length;
    }
    std::optional<int> min_dist;
    std::optional<int> min_dist_ways;
    find_min_path(farm, s, t, min_dist, min_dist_ways);
    if(min_dist.has_value()){
        std::cout << *min_dist << " " << *min_dist_ways << std::endl;
    }
    else{
        std::cout << -1 << " " << 0 << std::endl;
    }
    return 0;
}
