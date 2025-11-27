#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Segment{
    int endpoint1;
    int endpoint2;
    int length;

    bool operator<(const Segment& other)const{
        return this->endpoint1 < other.endpoint1 || (this->endpoint1 == other.endpoint1 && this->endpoint2 < other.endpoint2);
    }
    bool operator==(const Segment& other)const{
        return (this->endpoint1 == other.endpoint1 && this->endpoint2 == other.endpoint2);
    }
};

long find_best(std::map<int, std::set<Segment>>& start_to_segment, int start, int end, std::set<int>& visited){
    if(start == end){
        return 0;
    }
    long best = 1000000000000000000;
    for(auto segment : start_to_segment[start]){
        if(visited.count(segment.endpoint2) == 0){
            visited.insert(segment.endpoint2);
            best = std::min(best, find_best(start_to_segment, segment.endpoint2, end, visited) + segment.length);
            visited.erase(segment.endpoint2);
        }
    }
    return best;
}

long find_best_double(std::map<int, std::set<Segment>>& start_to_segment, int start, int end, std::set<int>& visited, Segment& doubled_segment1, Segment& doubled_segment2){
    if(start == end){
        return 0;
    }
    long best = 1000000000000000000;
    for(auto segment : start_to_segment[start]){
        if(visited.count(segment.endpoint2) == 0){
            visited.insert(segment.endpoint2);
            best = std::min(best, find_best_double(start_to_segment, segment.endpoint2, end, visited, doubled_segment1, doubled_segment2) + (segment == doubled_segment1 || segment == doubled_segment2 ? segment.length * 2 : segment.length));
            visited.erase(segment.endpoint2);
        }
    }
    return best;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::map<int, std::set<Segment>> start_to_segment;
    for(int i = 0; i < m; i++){
        int start, end, length;
        std::cin >> start >> end >> length;
        start_to_segment[start].insert(Segment{.endpoint1 = start, .endpoint2 = end, .length = length});
        start_to_segment[end].insert(Segment{.endpoint1 = end, .endpoint2 = start, .length = length});
    }
    std::set<int> visited = {1};
    long shortest_path = find_best(start_to_segment, 1, n, visited);
    long max_shortest_path_after_roadblock = 0;
    for(auto [start, segments] : start_to_segment){
        for(auto segment : segments){
            for(auto other_segment : start_to_segment[segment.endpoint2]){
                if(other_segment.endpoint2 == start){
                    max_shortest_path_after_roadblock = std::max(find_best_double(start_to_segment, 1, n, visited, segment, other_segment), max_shortest_path_after_roadblock);
                }
            }
        }
    }
    std::cout << max_shortest_path_after_roadblock - shortest_path << std::endl;
    return 0;
}
