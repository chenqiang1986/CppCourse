#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <unordered_map>
#include <vector>

struct Interval{
    long start;
    long end;

    Interval(){
        this->start = 0;
        this->end = 0;
    }

    Interval(long start, long end){
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
        return std::hash<long>()(interval.start) ^ (std::hash<long>()(interval.end) << 1);
    }
};

class OST{
  private:
    Interval base;
    std::unordered_map<Interval, long> interval_to_count;

    void split(const Interval& curr_interval, Interval& left, Interval& right){
        long mid = (curr_interval.start + curr_interval.end) / 2;
        left = Interval(curr_interval.start, mid);
        right = Interval(mid + 1, curr_interval.end);
    }

    long count(Interval interval, Interval curr_interval){
        if(curr_interval == interval){
            if(interval_to_count.count(curr_interval) == 0){
                return 0;
            }
            return interval_to_count[curr_interval];
        }
        Interval left;
        Interval right;
        split(curr_interval, left, right);
        if(interval.end <= left.end){
            return count(interval, left);
        }
        else if(interval.start >= right.start){
            return count(interval, right);
        }
        Interval interval_left = Interval(interval.start, left.end);
        Interval interval_right = Interval(right.start, interval.end);
        return count(interval_left, left) + count(interval_right, right);
    }
  public:
    OST(long start, long end){
        this->base = Interval(start, end);
        this->interval_to_count[Interval(start, end)] = 0;
    }

    void insert(long n){
        Interval curr_interval = base;
        while(true){
            interval_to_count[curr_interval]++;
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
    
    long count(Interval interval){
        return count(interval, base);
    }
};

void find_quotients_and_remainders(std::vector<long>& speeds, long laps, long fastest, std::vector<long>& quotients, std::vector<long>& remainders){
    for(int i = 0; i < speeds.size(); i++){
        quotients.push_back((speeds[i] * laps) / fastest);
        remainders.push_back((speeds[i] * laps) % fastest);
    }
}

long find_intersection_count(std::vector<long>& speeds, long laps, long total_count){
    long fastest = speeds[speeds.size() - 1];
    std::vector<long> quotients;
    std::vector<long> remainders;
    find_quotients_and_remainders(speeds, laps, fastest, quotients, remainders);
    long intersections = 0;
    for(int i = 0; i < speeds.size(); i++){
        intersections += ((2 * i) - (total_count - 1)) * quotients[i];
    }
    OST remainder_tree (0, fastest - 1);
    for(int i = 0; i < remainders.size(); i++){
        if(remainders[i] == fastest - 1){
            remainder_tree.insert(remainders[i]);
            continue;
        }
        Interval search_interval(remainders[i] + 1, fastest - 1);
        intersections -= remainder_tree.count(search_interval);
        remainder_tree.insert(remainders[i]);
    }
    return intersections;
}

int main(){
    try{
        long n, l, c;
        std::cin >> n >> l >> c;
        std::vector<long> speeds;
        for(long i = 0; i < n; i++){
            long speed;
            std::cin >> speed;
            speeds.push_back(speed);
        }
        std::sort(speeds.begin(), speeds.end());
        std::cout << find_intersection_count(speeds, l, n) << std::endl;
        return 0;
    }
    catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
}
