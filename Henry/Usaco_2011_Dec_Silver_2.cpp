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

void update_neighbors(int seed, std::unordered_map<int, std::unordered_map<int, int>>& farm, std::unordered_map<int, int>& dist_to_start, std::unordered_map<int, int>& from_node){
    for(auto [neighbor, dist] : farm[seed]){
        int through_seed = dist + dist_to_start[seed];
        if(dist_to_start.count(neighbor) == 0 || through_seed < dist_to_start[neighbor]){
            dist_to_start[neighbor] = through_seed;
            from_node[neighbor] = seed;
        }
    }
}

void find_min_path(std::unordered_map<int, std::unordered_map<int, int>>& farm, int start, int end, std::optional<int>& min_dist, std::vector<int>& min_path){
    std::unordered_map<int, int> dist_to_start;
    dist_to_start[start] = 0;
    std::unordered_map<int, int> from_node;
    std::unordered_set<int> visited;
    while(true){
        std::optional<int> seed = find_least_dist_to_start(dist_to_start, visited);
        if(! seed.has_value()){
            break;
        }
        visited.insert(*seed);
        update_neighbors(*seed, farm, dist_to_start, from_node);
    }
    if(dist_to_start.count(end) != 0){
        min_dist = dist_to_start[end];
        int field = end;
        while(field != start){
            min_path.push_back(field);
            field = from_node[field];
        }
        min_path.push_back(start);
    }
    else{
        min_dist = std::nullopt;
    }
}

int find_max_raise(std::unordered_map<int, std::unordered_map<int, int>>& farm, int start, int end, int min_dist, std::vector<int>& min_path){
    int max_min_dist = min_dist;
    for(int i = 1; i < min_path.size(); i++){
        farm[min_path[i - 1]][min_path[i]] *= 2;
        farm[min_path[i]][min_path[i - 1]] *= 2;
        std::optional<int> new_min_dist;
        std::vector<int> new_min_path;
        find_min_path(farm, start, end, new_min_dist, new_min_path);
        max_min_dist = std::max(max_min_dist, *new_min_dist);
        farm[min_path[i - 1]][min_path[i]] /= 2;
        farm[min_path[i]][min_path[i - 1]] /= 2;
    }
    return max_min_dist - min_dist;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::unordered_map<int, std::unordered_map<int, int>> farm;
    for(int i = 0; i < m; i++){
        int start, end, length;
        std::cin >> start >> end >> length;
        farm[start][end] = length;
        farm[end][start] = length;
    }
    std::optional<int> min_dist;
    std::vector<int> min_path;
    find_min_path(farm, 1, n, min_dist, min_path);
    if(min_dist.has_value()){
        std::cout << find_max_raise(farm, 1, n, *min_dist, min_path) << std::endl;
    }
    return 0;
}
