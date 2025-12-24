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

void execute_query(std::map<Interval, int>& interval_to_flips, int pos, Interval& search_zone, int flips){
    flips += interval_to_flips[search_zone];
    if(search_zone.start == search_zone.end && search_zone.end == pos){
        std::cout << (flips) % 2 << std::endl;
    }
    else{
        Interval search_left;
        Interval search_right;
        split(search_zone, search_left, search_right);
        if(pos >= search_left.start && pos <= search_left.end){
            execute_query(interval_to_flips, pos, search_left, flips);
        }
        else{
            execute_query(interval_to_flips, pos, search_right, flips);
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
            execute_query(interval_to_flips, pos, whole, 0);
        }
    }
    return 0;
}
