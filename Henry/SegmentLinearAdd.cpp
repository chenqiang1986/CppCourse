#include <iostream>
#include <map>

/**
 * Describes the interval [start, end]
 */
struct Interval{
    int start;
    int end;

    bool operator<(const Interval& other)const{
        return this->start < other.start || (this->start == other.start && this->end < other.end);
    }

    void split(Interval& left, Interval& right)const{
        left.start = this->start;
        left.end = (this->start + this->end) / 2;
        right.start = (this->start + this->end) / 2 + 1;
        right.end = this->end;
    }
};

struct IntervalAdd{
    Interval root;
    std::map<Interval, int> interval_to_base;
    std::map<Interval, int> interval_to_increment;

    void insert_given_search(const Interval& interval, const Interval& search){
        if(search.end < interval.start || search.start > interval.end){
            return;
        }
        if(interval.start <= search.start && search.end <= interval.end){
            interval_to_base[search] += search.start - interval.start + 1;
            interval_to_increment[search]++;
            return;
        }
        Interval search_left;
        Interval search_right;
        search.split(search_left, search_right);
        insert_given_search(interval, search_left);
        insert_given_search(interval, search_right);
    }

    void insert(const Interval& interval){
        insert_given_search(interval, root);
    }

    int retrieve_given_search(int pos, const Interval& search){
        int sol = 0;
        sol += interval_to_base[search] + interval_to_increment[search] * (pos - search.start);
        if(search.start == search.end){
            return sol;
        }
        Interval left_search;
        Interval right_search;
        search.split(left_search, right_search);
        if(left_search.start <= pos && pos <= left_search.end){
            sol += retrieve_given_search(pos, left_search);
        }
        else if(right_search.start <= pos && pos <= right_search.end){
            sol += retrieve_given_search(pos, right_search);
        }
        else{
            throw;
        }
        return sol;
    }

    int retrieve(int pos){
        return retrieve_given_search(pos, root);
    }
};

int main(){
    int n, m;
    std::cin >> n >> m;
    IntervalAdd interval_add;
    interval_add.root = Interval{.start = 0, .end = n - 1};
    for(int i = 0; i < m; i++){
        Interval increment_add_interval;
        std::cin >> increment_add_interval.start >> increment_add_interval.end;
        interval_add.insert(increment_add_interval);
    }
    for(int i = 0; i < n; i++){
        std::cout << interval_add.retrieve(i);
        if(i != n - 1){
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
