#include <iostream>
#include <set>
#include <algorithm>

struct Interval {
    int start, end;
    Interval(int start, int end):start(start), end(end) {}

    bool operator< (const Interval& other) const {
        return start < other.start || (start == other.start && end < other.end);
    }
};

bool has_intersection(const Interval& i1, const Interval& i2) {
    return std::max(i1.start, i2.start) < std::min(i1.end, i2.end);
}

std::pair<std::set<Interval>::iterator, std::set<Interval>::iterator> 
find_intersection_limit(const Interval& interval, std::set<Interval>& data) {
    std::set<Interval>::iterator left = data.lower_bound(Interval(interval.start, interval.start));
    if (left != data.begin()) {
        left--;
    }
    if (left != data.end() && !has_intersection(*left, interval)) {
        left++;
    }
    if (left != data.end() && !has_intersection(*left, interval)) {
        left = data.end();
    }


    std::set<Interval>::iterator right = data.lower_bound(Interval(interval.end, interval.end));
    if (right != data.begin()) {
        right--;
    }
    if (right != data.end() && !has_intersection(*right, interval)) {
        right = data.end();
    }

    return std::make_pair(left, right);
}

void union_into(const Interval& interval, std::set<Interval>& data) {
    auto [left, right] = find_intersection_limit(interval, data);
    if (left == data.end()) {
        data.insert(interval);
        return;
    }

    Interval union_one(std::min(interval.start, left->start), std::max(interval.end, right->end));
    data.erase(left, std::next(right));
    data.insert(union_one);
}


void delete_from(const Interval& interval, std::set<Interval>& data) {
    auto [left, right] = find_intersection_limit(interval, data);
    if (left == data.end()) {
        // No intersection at all. Skip.        
        return;
    }

    Interval left_remainder(left->start, interval.start);
    Interval right_remainder(interval.end, right->end);

    data.erase(left, std::next(right));
    if (left_remainder.start < left_remainder.end) {
        data.insert(left_remainder);
    }
    if (right_remainder.start < right_remainder.end) {
        data.insert(right_remainder);
    }
}

int total_length(const std::set<Interval>& data) {
    int length = 0;
    for (const Interval& interval : data) {
        if (interval.end > interval.start) {
            length += interval.end - interval.start;
        }
    }
    return length;
}

void debug_output(std::set<Interval>& data) {
    for (const Interval& interval : data) {
        std::cout << "[" << interval.start << "," << interval.end << ") ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cin >> n;

    std::set<Interval> data;

    for (int i=0; i<n; i++) {
        std::string op;
        int start, end;

        std::cin >> op >> start >>end;
        if (op == "Union") {
            union_into(Interval(start, end), data);            
        }
        else {
            delete_from(Interval(start, end), data);
        }
        //debug_output(data);
    }

    std::cout << total_length(data) << std::endl;
}