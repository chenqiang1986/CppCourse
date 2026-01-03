#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>


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

class OST{
  private:
    Interval base;
    std::unordered_map<Interval, int> interval_to_count;

    void split(const Interval& curr_interval, Interval& left, Interval& right){
        int mid = (curr_interval.start + curr_interval.end) / 2;
        left = Interval(curr_interval.start, mid);
        right = Interval(mid + 1, curr_interval.end);
    }

    int count(Interval interval, Interval curr_interval){
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
    OST(int start, int end){
        this->base = Interval(start, end);
        this->interval_to_count[Interval(start, end)] = 0;
    }

    void insert(int n){
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
    
    int count(Interval interval){
        return count(interval, base);
    }
};

struct Cow{
    long speed;
    long speed_lap_product;

    // speed_lap_product = q * fastest_speed + r;
    long q;
    long r;

    bool operator<(const Cow& other) const {
        return this->speed > other.speed;
    }
};

void preprocess(long fastest_speed, long L, std::vector<Cow>& cows) {
    for (int i = 0; i < cows.size(); i++) {
        cows[i].speed_lap_product = cows[i].speed * L;
        cows[i].q = cows[i].speed_lap_product / fastest_speed;
        cows[i].r = cows[i].speed_lap_product % fastest_speed;
    }
}


/**
 * Essentially calculate (q0-q1)+(q0-q2)+...(q0-q[n-1])+(q1-q2)+.....
 */
long calculate_q_part_overtakes(const std::vector<Cow>& cows) {
    long coeffecient = cows.size() - 1;
    long result = 0;
    for (int i = 0; i < cows.size(); i++) {
        result += coeffecient * cows[i].q;
        coeffecient -= 2;
    }
    return result;
}

/**
 * Essentially calculate sum{(r[i] < r[j] && i < j) ? -1: 0} 
 */
long calculate_r_part_overtakes(const std::vector<Cow>& cows) {
    OST ost(0, cows[0].speed);
    long result = 0;
    for (int i = 0; i < cows.size(); i++) {
        if (cows[i].r > 0) {
            result -= ost.count(Interval(0, cows[i].r - 1));
        }
        ost.insert(cows[i].r);
    }
    return result;
}

long calculate_overtakes(const std::vector<Cow>& cows) {
    return calculate_q_part_overtakes(cows) + calculate_r_part_overtakes(cows);
}

void debug_output(const std::vector<Cow>& cows) {
    
    for (long i = 0;i < cows.size(); i++) {
        std:: cout << cows[i].speed << ' ' << cows[i].speed_lap_product << ' ' << cows[i].q << ' ' << cows[i].r << std::endl;
    }
}


int main() {
    long N, L, C;
    std::cin >> N >> L >> C;

    std::vector<Cow> cows;

    for (long i =0; i< N; i++) {
        long s;
        std::cin >> s;
        cows.push_back(Cow {.speed = s});
    }

    std::sort(cows.begin(), cows.end());

    long fastest_speed = cows[0].speed;
    preprocess(fastest_speed, L, cows);

    //debug_output(cows);

    std::cout << calculate_overtakes(cows) << std::endl;

    return 0;
}