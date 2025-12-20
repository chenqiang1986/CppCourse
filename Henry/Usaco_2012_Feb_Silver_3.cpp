#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

struct NodeDistPair{
    int node;
    int dist;

    bool operator<(const NodeDistPair& other)const{
        return this->dist < other.dist || (this->dist == other.dist && this->node < other.node);
    }
};

void update_neighbors(std::map<int, std::map<int, int>>& edge_length, int seed_node, std::map<int, int>& distance_to_s, std::set<NodeDistPair>&to_be_visited){
    for (auto& [neighbor, length_to_neighbor] : edge_length[seed_node]) {
        int new_distance = distance_to_s[seed_node] + length_to_neighbor;
        if(distance_to_s.count(neighbor) == 0){
            distance_to_s[neighbor] = new_distance;
            to_be_visited.insert(NodeDistPair{.node = neighbor, .dist = new_distance});
        }
        else if(new_distance < distance_to_s[neighbor]){
            to_be_visited.erase(NodeDistPair{.node = neighbor, .dist = distance_to_s[neighbor]});
            distance_to_s[neighbor] = new_distance;
            to_be_visited.insert(NodeDistPair{.node = neighbor, .dist = new_distance});
        }
    }
}

std::map<int, int> calculate_min_path(std::map<int, std::map<int, int>>& edge_length, int start){
    std::set<NodeDistPair> to_be_visited;
    std::map<int, int> distance_to_s;
    distance_to_s[start] = 0;
    to_be_visited.insert(NodeDistPair{.node = start, .dist = 0});

    while (! to_be_visited.empty()) {
        int seed_node = to_be_visited.begin()->node;
        to_be_visited.erase(to_be_visited.begin());
        update_neighbors(edge_length, seed_node, distance_to_s, to_be_visited);
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
    std::cout << find_min_dist_through_markets(markets, edge_length) << "\r\n";
    return 0;
}
