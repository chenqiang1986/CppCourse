#include <iostream>
#include <map>
#include <unordered_map>
#include <stdexcept>

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

    void insert(long n, long count){
        Interval curr_interval = base;
        while(true){
            interval_to_count[curr_interval] += count;
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

void find_smaller_greater(std::map<long, long>& speed_to_count, std::map<long, long>& nums_smaller_than, std::map<long, long>& nums_greater_than, long total_count){
    long smaller_running = 0;
    for(auto& [speed, count] : speed_to_count){
        nums_smaller_than[speed] = smaller_running;
        smaller_running += count;
    }
    for(auto& [speed, count] : nums_smaller_than){
        nums_greater_than[speed] = total_count - count - speed_to_count[speed];
    }
}

long find_greatest_key(std::map<long, long>& some_map){
    std::map<long, long>::iterator it = some_map.end();
    it--;
    return it->first;
}

void find_quotients_and_remainders(std::map<long, long>& speed_to_count, long laps, long fastest, std::map<long, long>& quotients, std::map<long, long>& remainders){
    for(auto& [speed, count] : speed_to_count){
        quotients[speed] = (speed * laps) / fastest;
        remainders[speed] = (speed * laps) - fastest * quotients[speed];
    }
}

long find_intersection_count(std::map<long, long>& speed_to_count, long laps, long total_count){
    std::map<long, long> nums_smaller_than;
    std::map<long, long> nums_greater_than;
    find_smaller_greater(speed_to_count, nums_smaller_than, nums_greater_than, total_count);
    long fastest = find_greatest_key(speed_to_count);
    std::map<long, long> quotients;
    std::map<long, long> remainders;
    find_quotients_and_remainders(speed_to_count, laps, fastest, quotients, remainders);
    long intersections = 0;
    for(auto& [speed, count] : speed_to_count){
        intersections += (nums_smaller_than[speed] - nums_greater_than[speed]) * quotients[speed];
    }
    OST remainder_tree (0, fastest - 1);
    for(auto& [speed, remainder] : remainders){
        if(remainder == fastest - 1){
            remainder_tree.insert(remainder, speed_to_count[speed]);
            continue;
        }
        Interval search_interval(remainder + 1, fastest - 1);
        intersections -= remainder_tree.count(search_interval);
        remainder_tree.insert(remainder, speed_to_count[speed]);
    }
    return intersections;
}

int main(){
    try{
        long n, l, c;
        std::cin >> n >> l >> c;
        std::map<long, long> speed_to_count;
        for(long i = 0; i < n; i++){
            long speed;
            std::cin >> speed;
            speed_to_count[speed]++;
        }
        std::cout << find_intersection_count(speed_to_count, l, n) << std::endl;
        return 0;
    }
    catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
}
