#include <iostream>
#include <map>
#include <cassert>

struct Interval {
    int start;
    int end;

    Interval() {
        this->start = 0;
        this->end = 0;
    }

    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }

    bool operator< (const Interval& other) const {
        return start < other.start || (start == other.start && end < other.end);
    }
};

struct SegmentManager {
    // flip_record[interval] == 1 if we have an overall flip on interval
    std::map<Interval, int> flip_record;

    Interval root;

    SegmentManager(const Interval& root) {
        this -> root = root;
    }

    std::pair<Interval, Interval> split(const Interval& interval) {        
        assert(interval.end > interval.start);
        int mid = (interval.end + interval.start) / 2;
        return std::make_pair(Interval(interval.start, mid), Interval(mid+1, interval.end));
    }

    void flip_helper(const Interval& interval, const Interval& aligned_interval) {
        if (aligned_interval.end == aligned_interval.start) {
            flip_record[aligned_interval] = 1 - flip_record[aligned_interval];
            return;
        }

        if (aligned_interval.start >= interval.start && aligned_interval.end <= interval.end) {
            flip_record[aligned_interval] = 1 - flip_record[aligned_interval];
            return;
        }

        std::pair<Interval, Interval> splitted_aligned_intervals = split(aligned_interval);
        Interval left = splitted_aligned_intervals.first;
        Interval right = splitted_aligned_intervals.second;

        if (interval.start <= left.end) {
            flip_helper(interval, left);
        }
        if (interval.end >= right.start) {         
            flip_helper(interval, right);
        }        
    }

    void flip(const Interval& interval) {
        flip_helper(interval, root);
    }

    int query_helper(int position, const Interval& aligned_interval) {
        if (aligned_interval.start == aligned_interval.end) {
            return flip_record[aligned_interval];
        }
        
        std::pair<Interval, Interval> splitted_aligned_intervals = split(aligned_interval);
        Interval left = splitted_aligned_intervals.first;
        Interval right = splitted_aligned_intervals.second;

        int underlying_value = position <= left.end ? query_helper(position, left) : query_helper(position, right);
        int value =  flip_record[aligned_interval] == 0 ? underlying_value : 1 - underlying_value;
        return value;
    }

    int query(int position) {
        return query_helper(position, root);
    }

    void debug_output() {
        for (auto & interval : flip_record) {
            std::cout << interval.first.start << " " << interval.first.end << " : " << interval.second << std::endl;
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    SegmentManager segment_manager(Interval(0, n));
    for (int i = 0; i < m; i++) {
        std::string op;
        std::cin >> op;

        if (op == std::string("Flip")) {
            int start, end;
            std::cin >> start >> end;
            segment_manager.flip(Interval(start, end));
        }
        else {
            int pos;
            std::cin >> pos;
            std::cout << segment_manager.query(pos) << std::endl;
        }
    }
}