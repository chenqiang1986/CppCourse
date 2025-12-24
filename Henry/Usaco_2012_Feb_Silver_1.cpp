#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Coord{
    long long num1;
    long long num2;

    bool operator<(const Coord& other)const{
        return this->num1 < other.num1 || (this->num1 == other.num1 && this->num2 < other.num2);
    }
};

struct Interval{
    long long start;
    long long end;

    bool operator<(const Interval& other)const{
        return this->start < other.start || (this->start == other.start && this->end < other.end);
    }
};

struct Rectangle{
    Coord top_left;
    Coord bottom_right;
};

std::vector<Interval> find_intervals(std::vector<Rectangle>& rectangles, long long col, long long col2){
    std::vector<Interval> intervals;
    for(long long i = 0; i < rectangles.size(); i++){
        if(rectangles[i].top_left.num2 >= col2 && rectangles[i].bottom_right.num2 <= col){
            Interval interval = Interval{.start = rectangles[i].top_left.num1, .end = rectangles[i].bottom_right.num1};
            intervals.push_back(interval);
        }
    }
    return intervals;
}

long long find_length(std::vector<Rectangle>& rectangles, long long col, long long col2){
    std::vector<Interval> intervals = find_intervals(rectangles, col, col2);
    std::sort(intervals.begin(), intervals.end());
    std::vector<Interval> disjoint_intervals;
    disjoint_intervals.push_back(intervals[0]);
    for(long long i = 1; i < intervals.size(); i++){
        if(intervals[i].start < disjoint_intervals[disjoint_intervals.size() - 1].end){
            disjoint_intervals[disjoint_intervals.size() - 1].end = std::max(disjoint_intervals[disjoint_intervals.size() - 1].end, intervals[i].end);
        }
        else{
            disjoint_intervals.push_back(intervals[i]);
        }
    }
    long long length = 0;
    for(long long i = 0; i < disjoint_intervals.size(); i++){
        length += disjoint_intervals[i].end - disjoint_intervals[i].start;
    }
    return length;
}

long long find_total_area(std::vector<Rectangle>& rectangles, std::vector<int>& cols){
    long long total_area = 0;
    for(long long i = 0; i < cols.size() - 1; i++){
        long long width = cols[i + 1] - cols[i];
        long long length = find_length(rectangles, cols[i], cols[i + 1]);
        total_area += width * length;
    }
    return total_area;
}

int main(){
    long long n;
    std::cin >> n;
    std::vector<Rectangle> rectangles;
    std::vector<int> cols;
    for(long long i = 0; i < n; i++){
        Rectangle rectangle;
        std::cin >> rectangle.top_left.num1 >> rectangle.top_left.num2 >> rectangle.bottom_right.num1 >> rectangle.bottom_right.num2;
        cols.push_back(rectangle.top_left.num2);
        cols.push_back(rectangle.bottom_right.num2);
        rectangles.push_back(rectangle);
    }
    std::sort(cols.begin(), cols.end());
    std::cout << find_total_area(rectangles, cols) << std::endl;
    return 0;
}
