#include <algorithm>
#include <iostream>
#include <set>
#include <string>

struct Interval{
    int start;
    int end;

    bool operator<(const Interval& other)const{
        return this->start < other.start || (this->start == other.start && this->end < other.end);
    }

    bool has_intersection(const Interval& other)const{
        Interval intersection = Interval{.start = std::max(this->start, other.start), .end = std::min(this->end, other.end)};
        return intersection.start < intersection.end;
    }
};

struct IntervalSet{
    std::set<Interval> intervals;

    std::set<Interval>::iterator find_leftmost_intersect(const Interval& interval){
        std::set<Interval>::iterator left = this->intervals.lower_bound(Interval{.start = interval.start, .end = interval.start});
        std::set<Interval>::iterator first = left != intervals.begin() ? std::next(left, -1) : intervals.end();
        std::set<Interval>::iterator second = left;
        if(first != intervals.end() && first->has_intersection(interval)){
            return first;
        }
        if(second != intervals.end() && second->has_intersection(interval)){
            return second;
        }
        return intervals.end();
    }

    std::set<Interval>::iterator find_rightmost_intersect(const Interval& interval){
        std::set<Interval>::iterator right = this->intervals.lower_bound(Interval{.start = interval.end, .end = interval.end});
        std::set<Interval>::iterator first = right != intervals.begin() ? std::next(right, -1) : intervals.end();
        if(first != intervals.end() && first->has_intersection(interval)){
            return first;
        }
        return intervals.end();
    }

    void insert(const Interval& interval){
        if(this->intervals.size() == 0){
            this->intervals.insert(interval);
            return;
        }
        std::set<Interval>::iterator left = find_leftmost_intersect(interval);
        std::set<Interval>::iterator right = find_rightmost_intersect(interval);
        if(left == intervals.end() || right == intervals.end()){
            this->intervals.insert(interval);
            return;
        }
        Interval replacement = Interval{.start = std::min(interval.start, left->start), .end = std::max(interval.end, right->end)};
        intervals.erase(left, std::next(right, 1));
        intervals.insert(replacement);
    }

    void cut(const Interval& interval){
        if(this->intervals.size() == 0){
            return;
        }
        std::set<Interval>::iterator left = find_leftmost_intersect(interval);
        std::set<Interval>::iterator right = find_rightmost_intersect(interval);
        if(left == intervals.end() || right == intervals.end()){
            return;
        }
        Interval changed_left = Interval{.start = left->start, .end = interval.start};
        Interval changed_right = Interval{.start = interval.end, .end = right->end};
        intervals.erase(left, std::next(right, 1));
        if(changed_left.start < changed_left.end){
            intervals.insert(changed_left);
        }
        if(changed_right.start < changed_right.end){
            intervals.insert(changed_right);
        }
    }
};

void debug_output(IntervalSet& interval_set){
    std::cout << "Interval Set:" << std::endl;
    for(auto& interval : interval_set.intervals){
        std::cout << interval.start << " " << interval.end << std::endl;
    }
}

int find_length(IntervalSet& interval_set){
    int length = 0;
    for(auto& interval : interval_set.intervals){
        length += interval.end - interval.start;
    }
    return length;
}

int main(){
    int n;
    std::cin >> n;
    IntervalSet interval_set;
    for(int i = 0; i < n; i++){
        std::string action;
        Interval action_interval;
        std::cin >> action >> action_interval.start >> action_interval.end;
        if(action == "Union"){
            interval_set.insert(action_interval);
        }
        else if(action == "Subtract"){
            interval_set.cut(action_interval);
        }
        else{
            throw;
        }
    }
    std::cout << find_length(interval_set) << std::endl;
    return 0;
}
