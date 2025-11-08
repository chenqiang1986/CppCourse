#include <algorithm>
#include <iostream>
#include <vector>
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

bool is_valid(const std::vector<std::vector<int>>& map, const Coord& point, const std::set<Coord>& visited){
    return (point.row >= 0 && point.row < map.size()) && (point.col >= 0 && point.col < map[0].size()) && (map[point.row][point.col] == 0 && visited.count(point) == 0);
}

int dfs(const std::vector<std::vector<int>>& map, const Coord& start, std::set<Coord>& visited){
    int total_count = 1;
    visited.insert(start);
    for(int i = 0; i < 4; i++){
        Coord new_start = Coord{.row = start.row + drow[i], .col = start.col + dcol[i]};
        if(is_valid(map, new_start, visited)){
            total_count += dfs(map, new_start, visited);
        }
    }
    return total_count;
}

int find_greatest_lake_size(const std::vector<std::vector<int>>& map){
    std::set<Coord> visited;
    int max_size = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            Coord start = Coord{.row = i, .col = j};
            if(is_valid(map, start, visited)){
                max_size = std::max(dfs(map, start, visited), max_size);
            }
        }
    }
    return max_size;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> map(n, std::vector<int> (m, 1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cin >> map[i][j];
        }
    }
    std::cout << find_greatest_lake_size(map) << std::endl;
    return 0;
}
