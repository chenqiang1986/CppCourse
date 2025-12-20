#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

int find_non_visited_node_closest_to_s(std::map<int, int> & distance_to_s, std::unordered_set<int>& visited){
    int answer = -1;
    int min_distance = 2100000000;

    for (auto& [node, distance]: distance_to_s) {
        if (visited.count(node) > 0) {
            continue;
        }

        if (distance < min_distance) {
            min_distance = distance;
            answer = node;
        }
    }

    return answer;
}

void update_neighbors(std::map<int, std::map<int, int>>& edge_length, int seed_node, std::map<int, int>& distance_to_s){
    for (auto& [neighbor, length_to_neighbor] : edge_length[seed_node]) {
        int new_distance = distance_to_s[seed_node] + length_to_neighbor;
        if (distance_to_s.count(neighbor) == 0 || new_distance < distance_to_s[neighbor]) {
            distance_to_s[neighbor] = new_distance;
        }
    }
}

std::map<int, int> calculate_min_path(std::map<int, std::map<int, int>>& edge_length, int start){
    std::map<int, int> distance_to_s;
    distance_to_s[start] = 0;

    std::unordered_set<int> visited;

    while (true) {
        int seed_node = find_non_visited_node_closest_to_s(distance_to_s, visited);
        if (seed_node < 0) {
            break;
        }
        visited.insert(seed_node);

        update_neighbors(edge_length, seed_node, distance_to_s);
    }

    return distance_to_s;
}

std::vector<std::vector<int>> find_orders(std::unordered_set<int>& markets){
    std::vector<std::vector<int>> orders;
    if(markets.size() == 1){
        std::vector<int> order;
        for(auto& market : markets){
            order.push_back(market);
        }
        orders.push_back(order);
        return orders;
    }
    for(auto& market : markets){
        std::unordered_set<int> market_copy = markets;
        market_copy.erase(market);
        std::vector<std::vector<int>> other_orders = find_orders(market_copy);
        for(auto order : other_orders){
            order.push_back(market);
            orders.push_back(order);
        }
    }
    return orders;
}

int find_min_dist_through_markets(std::unordered_set<int>& markets, std::map<int, std::map<int, int>>& edge_length){
    std::map<int, std::map<int, int>> market_to_other_towns_dist;
    for(auto& market : markets){
        market_to_other_towns_dist[market] = calculate_min_path(edge_length, market);
    }
    int min_dist = 2147483647;
    std::vector<std::vector<int>> orders = find_orders(markets);
    for(auto& [town, trash] : edge_length){
        if(markets.count(town) != 0){
            continue;
        }
        for(auto& order : orders){
            int dist = market_to_other_towns_dist[order[0]][town] + market_to_other_towns_dist[order[order.size() - 1]][town];
            for(int i = 0; i < order.size() - 1; i++){
                dist += market_to_other_towns_dist[order[i]][order[i + 1]];
            }
            min_dist = std::min(min_dist, dist);
        }
    }
    return min_dist;
}

int main(){
    int n, m, k;
    std::cin >> n >> m >> k;
    std::unordered_set<int> markets;
    for(int i = 0; i < k; i++){
        int market;
        std::cin >> market;
        markets.insert(market);
    }
    std::map<int, std::map<int, int>> edge_length;
    for(int i = 0; i < m; i++){
        int start, end, l;
        std::cin >> start >> end >> l;
        edge_length[start][end] = l;
        edge_length[end][start] = l;
    }
    std::cout << find_min_dist_through_markets(markets, edge_length) << std::endl;
    return 0;
}
