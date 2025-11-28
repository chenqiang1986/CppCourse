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

void update_neighbors(int seed, std::unordered_map<int, std::unordered_map<int, int>>& farm, std::unordered_map<int, int>& dist_to_start, std::unordered_map<int, int>& num_ways){
    for(auto [neighbor, dist] : farm[seed]){
        int through_seed = dist + dist_to_start[seed];
        if(dist_to_start.count(neighbor) == 0 || through_seed < dist_to_start[neighbor]){
            dist_to_start[neighbor] = through_seed;
            num_ways[neighbor] = num_ways[seed];
        }
        else if (through_seed == dist_to_start[neighbor]) {
            num_ways[neighbor] += num_ways[seed];
        }
    }
}

void find_min_path(std::unordered_map<int, std::unordered_map<int, int>>& farm, int start, int end, std::optional<int>& min_dist, int& ways_min_dist){
    std::unordered_map<int, int> dist_to_start;
    dist_to_start[start] = 0;
    std::unordered_map<int, int> num_ways;
    num_ways[start] = 1;

    std::unordered_set<int> visited;

    while(true){
        std::optional<int> seed = find_least_dist_to_start(dist_to_start, visited);
        if(! seed.has_value()){
            break;
        }
        visited.insert(*seed);
        update_neighbors(*seed, farm, dist_to_start, num_ways);
    }
    if(dist_to_start.count(end) != 0){
        min_dist = dist_to_start[end];
        ways_min_dist = num_ways[end];
    }
    else{
        min_dist = std::nullopt;
        ways_min_dist = 0;
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
    int ways_min_dist;
    find_min_path(farm, s, t, min_dist, ways_min_dist);

    std::cout << (min_dist.has_value() ? * min_dist : -1) << " " << ways_min_dist << std::endl;
    return 0;
}