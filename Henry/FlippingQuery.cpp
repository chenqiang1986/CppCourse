#include <algorithm>
#include <iostream>
#include <map>
#include <string>

struct Interval{
    int start;
    int end;

    bool operator<(const Interval& other)const{
        return this->start < other.start || (this->start == other.start && this->end < other.end);
    }
};

void split(const Interval& interval, Interval& left, Interval& right){
    left = Interval{.start = interval.start, .end = (interval.start + interval.end) / 2};
    right = Interval{.start = (interval.start + interval.end) / 2 + 1, .end = interval.end}; 
}

void execute_flip(std::map<Interval, int>& interval_to_flips, const Interval& flipped_interval, const Interval& search_zone){
    if(flipped_interval.start > flipped_interval.end){
        return;
    }
    if(flipped_interval.start == search_zone.start && flipped_interval.end == search_zone.end){
        interval_to_flips[search_zone]++;
    }
    else{
        Interval search_left;
        Interval search_right;
        split(search_zone, search_left, search_right);
        Interval flipped_left = Interval{.start = flipped_interval.start, .end = std::min(search_left.end, flipped_interval.end)};
        Interval flipped_right = Interval{.start = std::max(search_right.start, flipped_interval.start), .end = flipped_interval.end};
        execute_flip(interval_to_flips, flipped_left, search_left);
        execute_flip(interval_to_flips, flipped_right, search_right);
    }
}

int execute_query(std::map<Interval, int>& interval_to_flips, int pos, Interval& search_zone){
    int flips_at_layer = interval_to_flips[search_zone];
    if(search_zone.start == search_zone.end && search_zone.end == pos){
        return flips_at_layer;
    }
    else{
        Interval search_left;
        Interval search_right;
        split(search_zone, search_left, search_right);
        if(pos >= search_left.start && pos <= search_left.end){
            return execute_query(interval_to_flips, pos, search_left) + flips_at_layer;
        }
        else{
            return execute_query(interval_to_flips, pos, search_right) + flips_at_layer;
        }
    }
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::map<Interval, int> interval_to_flips;
    Interval whole = Interval{.start = 0, .end = n - 1};
    interval_to_flips[whole] = 0;
    for(int i = 0; i < m; i++){
        std::string action;
        std::cin >> action;
        if(action == "Flip"){
            Interval flipped_interval;
            std::cin >> flipped_interval.start >> flipped_interval.end;
            execute_flip(interval_to_flips, flipped_interval, whole);
        }
        else if(action == "Query"){
            int pos;
            std::cin >> pos;
            int output = execute_query(interval_to_flips, pos, whole);
            std::cout << output % 2 << std::endl;
        }
    }
    return 0;
}
