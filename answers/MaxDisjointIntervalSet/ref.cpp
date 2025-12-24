#include <iostream>
#include <set>
#include <map>

struct Interval{
    int start;
    int end;

    Interval(int start, int end)
        :start(start), end(end){
    }

    bool operator<(const Interval& other) const {
        return start < other.start || (start == other.start && end < other.end);
    }
};

int find_max_non_overlap(std::set<Interval>& interval_set) {
    std::map<Interval, int> max_size_if_first_choose;
    for (std::set<Interval>::reverse_iterator it = interval_set.rbegin(); it != interval_set.rend(); it++) {
        Interval interval = *it;

        int max_from_later = 0;
        for (std::set<Interval>::iterator jt = interval_set.find(interval);jt != interval_set.end(); jt++) {
            if (jt->start <= interval.end) {
                continue;
            }
            max_from_later = std::max(max_from_later, max_size_if_first_choose[*jt]);            
        }

        max_size_if_first_choose[interval] = 1 + max_from_later;
    }

    int max = 0; 
    std::set<Interval>::iterator jt = interval_set.begin();
    while (jt != interval_set.end()) {
        max = std::max(max, max_size_if_first_choose[*jt]);
        jt++;
    }
    return max;
}

int main() {
    int n;
    std::cin >> n;

    std::set<Interval> interval_set;
    for (int i =0; i < n; i++) {
        int start, end;
        std::cin >> start >>end;
        interval_set.insert(Interval(start, end));
    }

    std::cout << find_max_non_overlap(interval_set) << std::endl;
}