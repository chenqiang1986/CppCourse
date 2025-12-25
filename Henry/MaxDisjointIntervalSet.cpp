#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Interval{
    int start;
    int end;

    bool operator<(const Interval& other)const{
        return this->start < other.start || (this->start == other.start && this->end < other.end);
    }

    bool has_intersection(const Interval& other)const{
        Interval intersection = Interval{.start = std::max(this->start, other.start), .end = std::min(this->end, other.end)};
        return intersection.start <= intersection.end;
    }
};

int smart(std::vector<Interval>& intervals, std::map<Interval, int> leftmost_to_length){
    for(int i = intervals.size() - 1; i >= 0; i--){
        int max_length_behind = 0;
        for(int j = i; j < intervals.size(); j++){
            if(! intervals[i].has_intersection(intervals[j])){
                max_length_behind = std::max(max_length_behind, leftmost_to_length[intervals[j]]);
            }
        }
        leftmost_to_length[intervals[i]] = max_length_behind + 1;
    }
    int max_length = 0;
    for(int i = 0; i < intervals.size(); i++){
        max_length = std::max(max_length, leftmost_to_length[intervals[i]]);
    }
    return max_length;
}

int main(){
    int n;
    std::cin >> n;
    std::vector<Interval> intervals;
    for(int i = 0; i < n; i++){
        Interval interval;
        std::cin >> interval.start >> interval.end;
        intervals.push_back(interval);
    }
    std::sort(intervals.begin(), intervals.end());
    std::map<Interval, int> leftmost_to_length;
    std::cout << smart(intervals, leftmost_to_length) << std::endl; 
    return 0;
}
