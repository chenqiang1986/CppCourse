#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

struct Coord{
    int row;
    int col;

    bool operator<(const Coord& other)const{
        return this->row < other.row || (this->row == other.row && this->col < other.col);
    }
};

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
        int rem = (curr_interval.start + curr_interval.end) % 2;
        int mid = (curr_interval.start + curr_interval.end - std::abs(rem)) / 2;
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
    OST():OST(-1000000, 1000000){
    }
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

class DoubleOST{
  private:
    Interval base;
    std::unordered_map<Interval, OST> interval_to_count;

    void split(const Interval& curr_interval, Interval& left, Interval& right){
        int rem = (curr_interval.start + curr_interval.end) % 2;
        int mid = (curr_interval.start + curr_interval.end - std::abs(rem)) / 2;
        left = Interval(curr_interval.start, mid);
        right = Interval(mid + 1, curr_interval.end);
    }

    int count(Interval interval_row, Interval interval_col, Interval curr_interval){
        if(curr_interval == interval_row){
            if(interval_to_count.count(curr_interval) == 0){
                return 0;
            }
            return interval_to_count[curr_interval].count(interval_col);
        }
        Interval left;
        Interval right;
        split(curr_interval, left, right);
        if(interval_row.end <= left.end){
            return count(interval_row, interval_col, left);
        }
        else if(interval_row.start >= right.start){
            return count(interval_row, interval_col, right);
        }
        Interval interval_left = Interval(interval_row.start, left.end);
        Interval interval_right = Interval(right.start, interval_row.end);
        return count(interval_left, interval_col, left) + count(interval_right, interval_col, right);
    }
  public:
    DoubleOST(int start, int end){
        this->base = Interval(start, end);
        this->interval_to_count[Interval(start, end)] = OST(-1000000, 1000000);
    }

    void insert(Coord point){
        int n = point.row;
        Interval curr_interval = base;
        while(true){
            if(interval_to_count.count(curr_interval) == 0){
                interval_to_count[curr_interval] = OST(-1000000, 1000000);

            }
            interval_to_count[curr_interval].insert(point.col);
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
    
    int count(Interval interval_row, Interval interval_col){
        return count(interval_row, interval_col, base);
    }
};

int main(){
    int t;
    std::cin >> t;
    DoubleOST double_ost(-1000000, 1000000);
    for(int i = 0; i < t; i++){
        std::string action;
        std::cin >> action;
        if(action == "Input"){
            Coord point;
            std::cin >> point.row >> point.col;
            double_ost.insert(point);
        }
        else if(action == "Query"){
            Interval row_interval;
            Interval col_interval;
            std::cin >> row_interval.start >> row_interval.end >> col_interval.start >> col_interval.end;
            std::cout << double_ost.count(row_interval, col_interval) << std::endl;
        }
    }
    return 0;
}
