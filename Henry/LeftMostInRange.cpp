#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

struct Interval{
    int start;
    int end;

    Interval(){
        this->start = 0;
        this->end = 0;
    }

    Interval(int start, int end){
        if(start > end){
            throw std::runtime_error("Critical Error: Interval given is wrong");
        }
        this->start = start;
        this->end = end;
    }

    bool operator==(const Interval& other)const{
        return this->start == other.start && this->end == other.end;
    }
};

template<>
struct std::hash<Interval> {
    size_t operator()(const Interval& interval)const{
        return std::hash<int>()(interval.start) ^ (std::hash<int>()(interval.end) << 1);
    }
};

struct OST{
    Interval base;
    std::unordered_map<Interval, int> interval_to_min;

    void split(const Interval& curr_interval, Interval& left, Interval& right){
        int mid = (curr_interval.start + curr_interval.end) / 2;
        left = Interval(curr_interval.start, mid);
        right = Interval(mid + 1, curr_interval.end);
    }

    int min(Interval interval, Interval curr_interval){
        if(curr_interval == interval){
            if(interval_to_min.count(curr_interval) == 0){
                return 10000001;
            }
            return interval_to_min[curr_interval];
        }
        Interval left;
        Interval right;
        split(curr_interval, left, right);
        if(interval.end <= left.end){
            return min(interval, left);
        }
        else if(interval.start >= right.start){
            return min(interval, right);
        }
        Interval interval_left = Interval(interval.start, left.end);
        Interval interval_right = Interval(right.start, interval.end);
        return std::min(min(interval_left, left), min(interval_right, right));
    }
    OST(int start, int end){
        this->base = Interval(start, end);
        this->interval_to_min[Interval(start, end)] = 10000001;
    }

    void insert(int n, int x){
        Interval curr_interval = base;
        while(true){
            if(interval_to_min.count(curr_interval) == 0){
                interval_to_min[curr_interval] = x;
            }
            else{
                interval_to_min[curr_interval] = std::min(x, interval_to_min[curr_interval]);
            }
            if(curr_interval.start == curr_interval.end){
                break;
            }
            Interval left;
            Interval right;
            split(curr_interval, left, right);
            if(n >= left.start && n <= left.end){
                curr_interval = left;
            }
            else if(n >= right.start && n <= right.end){
                curr_interval = right;
            }
            else{
                throw std::runtime_error("Critical Error: Inserted item not in range");
            }
        }
    }
    
    int min(Interval interval){
        return min(interval, base);
    }
};

int main(){
    try{
        int n;
        std::cin >> n;
        OST ost(-10000000, 10000000);
        for(int i = 0; i < n; i++){
            std::string action;
            int first;
            int second;
            std::cin >> action >> first >> second;
            if(action == "Insert"){
                ost.insert(second, first);
            }
            else if(action == "Query"){
                int min_x = ost.min(Interval(first, second));
                if(min_x != 10000001){
                    std::cout << min_x  << std::endl;
                }
                else{
                    std::cout << "No Data" << std::endl;
                }
            }
        }
        return 0;
    }
    catch(std::runtime_error err){
        return 1;
    }
}
