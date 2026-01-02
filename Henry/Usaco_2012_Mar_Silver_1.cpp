#include <algorithm>
#include <iostream>
#include <map>
#include <set>

int drow[] = {-1, 1, 0, 0};
int dcol[] = {0, 0, -1, 1};

struct Coord{
    int row;
    int col;

    bool operator<(const Coord& other)const{
        return this->row < other.row || (this->row == other.row && this->col < other.col);
    }
};

struct NodeDistPair{
    Coord node;
    int dist;

    bool operator<(const NodeDistPair& other)const{
        return this->dist < other.dist || (this->dist == other.dist && this->node < other.node);
    }
};

void update_neighbors(std::set<Coord>& haybales, Coord seed_node, std::map<Coord, int>& distance_to_s, std::set<NodeDistPair>& to_be_visited){
    for(int i = 0; i < 4; i++){
        Coord neighbor = Coord{.row = seed_node.row + drow[i], .col = seed_node.col + dcol[i]};
        if(neighbor.row < -1 || neighbor.row > 1001 || neighbor.col < -1 || neighbor.col > 1001){
            continue;
        }
        int new_distance = distance_to_s[seed_node] + (haybales.count(neighbor) != 0 ? 1 : 0);
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

int calculate_min_path(std::set<Coord>& haybales, Coord start, Coord end){
    std::set<NodeDistPair> to_be_visited;
    std::map<Coord, int> distance_to_s;
    distance_to_s[start] = 0;
    to_be_visited.insert(NodeDistPair{.node = start, .dist = 0});
    while(! to_be_visited.empty()){
        Coord seed_node = to_be_visited.begin()->node;
        to_be_visited.erase(to_be_visited.begin());
        update_neighbors(haybales, seed_node, distance_to_s, to_be_visited);
    }
    return distance_to_s[end];
}

int main(){
    int n;
    Coord tractor;
    std::cin >> n >> tractor.row >> tractor.col;
    std::set<Coord> haybales;
    for(int i = 0; i < n; i++){
        Coord haybale;
        std::cin >> haybale.row >> haybale.col;
        haybales.insert(haybale);
    }
    Coord end = {.row = 0, .col = 0};
    std::cout << calculate_min_path(haybales, tractor, end) << std::endl;
    return 0;
}
