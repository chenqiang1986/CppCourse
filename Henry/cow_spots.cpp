#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int drow[] = {-1, 1, 0, 0};
int dcol[] = {0, 0, -1, 1};

struct Coord{
    int row;
    int col;

    bool operator<(const Coord& other)const{
        return this->row < other.row || (this->row == other.row && this->col < other.col);
    }
};

struct CCPair{
    int cc1;
    int cc2;

    void normalize(){
        if(this->cc1 <= this->cc2){
            return;
        }
        int new_cc1 = this->cc2;
        int new_cc2 = this->cc1;
        this->cc1 = new_cc1;
        this->cc2 = new_cc2;
    }

    bool operator<(const CCPair& other)const{
        return this->cc1 < other.cc1 || (this->cc1 == other.cc1 && this->cc2 < other.cc2);
    }
};

bool is_valid(Coord& point, const std::vector<std::string>& cow, std::map<Coord, int>& point_to_cc){
    return (point.row >= 0 && point.row < cow.size()) && (point.col >= 0 && point.col < cow[0].size()) && cow[point.row][point.col] == 'X' && point_to_cc.count(point) == 0;
}

void floodfill(Coord& point, const std::vector<std::string>& cow, std::map<Coord, int>& point_to_cc, std::map<int, std::set<Coord>>& cc_to_points, int id){
    point_to_cc[point] = id;
    cc_to_points[id].insert(point);
    for(int i = 0; i < 4; i++){
        Coord new_point = Coord{.row = point.row + drow[i], .col = point.col + dcol[i]};
        if(is_valid(new_point, cow, point_to_cc)){
            floodfill(new_point, cow, point_to_cc, cc_to_points, id);
        }
    }
}

void find_cc(const std::vector<std::string>& cow, std::map<Coord, int>& point_to_cc, std::map<int, std::set<Coord>>& cc_to_points){
    int id = 1;
    for(int i = 0; i < cow.size(); i++){
        for(int j = 0; j < cow[i].size(); j++){
            Coord point = Coord{.row = i, .col = j};
            if(is_valid(point, cow, point_to_cc)){
                floodfill(point, cow, point_to_cc, cc_to_points, id);
                id++;
            }
        }
    }
}

int find_shortest_dist(CCPair& cc_pair, std::map<int, std::set<Coord>>& cc_to_points){
    int min_dist = 1000000;
    for(auto& point1 : cc_to_points[cc_pair.cc1]){
        for(auto& point2 : cc_to_points[cc_pair.cc2]){
            int manhattan_dist = std::max(point1.row, point2.row) - std::min(point1.row, point2.row) + std::max(point1.col, point2.col) - std::min(point1.col, point2.col);
            int blocks_went_over = manhattan_dist - 1;
            min_dist = std::min(blocks_went_over, min_dist);
        }
    }
    return min_dist;
}

int find_shortest_total_seperate(std::map<int, std::set<Coord>>& cc_to_points){
    int total = 0;
    int added_in = 0;
    std::map<CCPair, int> cc_pair_to_shortest_dist;
    for(auto& [ccid1, points1] : cc_to_points){
        for(auto& [ccid2, points2] : cc_to_points){
            CCPair cc_pair = CCPair{.cc1 = ccid1, .cc2 = ccid2};
            cc_pair.normalize();
            if(ccid1 == ccid2 || cc_pair_to_shortest_dist.count(cc_pair) != 0){
                continue;
            }
            cc_pair_to_shortest_dist[cc_pair] = find_shortest_dist(cc_pair, cc_to_points);
        }
    }
    std::vector<int> shortest_dists;
    for(auto [cc_pair, dist] : cc_pair_to_shortest_dist){
        shortest_dists.push_back(dist);
    }
    std::sort(shortest_dists.begin(), shortest_dists.end());
    for(auto dist : shortest_dists){
        if(added_in < 2){
            total += dist;
            added_in++;
        }
    }
    return total;
}

int find_shortest_dist_point_cc(std::set<Coord>& points, Coord& point1){
    int min_dist = 10000000;
    for(auto& point2 : points){
        int manhattan_dist = std::abs(point1.row - point2.row) + std::abs(point1.col - point2.col);
        min_dist = std::min(manhattan_dist, min_dist);
    }
    return min_dist;
}

int find_shortest_total_combined(std::map<int, std::set<Coord>>& cc_to_points, int n, int m){
    int shortest_dist = 10000000;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            Coord point = Coord{.row = i, .col = j};
            int dist = 1;
            for(auto& [ccid, points] : cc_to_points){
                dist += find_shortest_dist_point_cc(points, point) - 1;
            }
            shortest_dist = std::min(shortest_dist, dist);
        }
    }
    return shortest_dist;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> cow;
    for(int i = 0; i < n; i++){
        std::string row;
        std::cin >> row;
        cow.push_back(row);
    }
    std::map<Coord, int> point_to_cc;
    std::map<int, std::set<Coord>> cc_to_points;
    find_cc(cow, point_to_cc, cc_to_points);

    int separate_min = find_shortest_total_seperate(cc_to_points);
    int combined_min = find_shortest_total_combined(cc_to_points, n, m);
    std::cout << std::min(separate_min, combined_min) << std::endl;
    return 0;
}
