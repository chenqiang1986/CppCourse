#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <vector>

struct Interval{
    long start;
    long end;
};

struct Expression{
    long coefficient;
    long constant;

    Interval before_shift(Interval& interval){
        Interval output;
        long only_shift_start = interval.start - this->constant;
        long only_shift_end = interval.end - this->constant;
        if(this->coefficient == -1){
            output.start = -only_shift_end;
            output.end = -only_shift_start;
        }
        else{
            output.start = only_shift_start;
            output.end = only_shift_end;
        }
        return output;
    }
};

struct Rule{
    long this_id;
    long other_id;
    long sum;
};

bool fill_neighbors(std::map<long, std::vector<Rule>>& rod_power_sums, std::map<long, Expression>& rod_to_expression, long rod, std::deque<long>& bfs, std::optional<long>& a_value){
    for(auto& rule : rod_power_sums[rod]){
        Expression projected = Expression{.coefficient = - rod_to_expression[rod].coefficient, .constant = rule.sum - rod_to_expression[rod].constant};
        if(rod_to_expression.count(rule.other_id) == 0){
            rod_to_expression[rule.other_id] = projected;
            bfs.push_back(rule.other_id);
        }
        else{
            if(projected.coefficient == rod_to_expression[rule.other_id].coefficient){
                if(projected.constant != rod_to_expression[rule.other_id].constant){
                    return false;
                }
            }
            else{
                long rhs = rod_to_expression[rule.other_id].constant - projected.constant;
                long lhs = projected.coefficient - rod_to_expression[rule.other_id].coefficient;
                if((rhs) % (lhs) != 0 || (a_value.has_value() && *a_value != (rhs) / (lhs))){
                    return false;
                }
                a_value = (rhs) / (lhs);
            }
        }
    }
    return true;
}

long find_count_given_a(std::map<long, Interval>& rod_ranges, std::set<long>& visited, std::map<long, Expression>& rod_to_expression, long a_value){
    long count = 0;
    for(auto& rod : visited){
        long power = rod_to_expression[rod].coefficient * a_value + rod_to_expression[rod].constant;
        if(power >= rod_ranges[rod].start && power <= rod_ranges[rod].end){
            count++;
        }
    }
    return count;
}

long find_max_count(std::map<long, Interval>& rod_ranges, std::set<long>& visited, std::map<long, Expression>& rod_to_expression){
    std::vector<Interval> intervals;
    for(auto& rod : visited){
        intervals.push_back(rod_to_expression[rod].before_shift(rod_ranges[rod]));
    }
    std::vector<long> start;
    std::vector<long> end;
    for(auto& interval : intervals){
        start.push_back(interval.start);
        end.push_back(interval.end);
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    long running_count = 0;
    long max = 0;
    long i = 0;
    long j = 0;
    while(i < start.size()){
        if(start[i] <= end[j]){
            running_count++;
            max = std::max(max, running_count);
            i++;
        }
        else{
            running_count--;
            j++;
        }
    }
    return max;
}

long find_generating_rods(std::map<long, Interval>& rod_ranges, std::map<long, std::vector<Rule>>& rod_power_sums, std::map<long, Expression>& rod_to_expression, long first){
    std::optional<long> a_value = std::nullopt;
    std::deque<long> bfs;
    std::set<long> visited;
    bfs.push_back(first);
    rod_to_expression[first] = Expression{.coefficient = 1, .constant = 0};
    while(! bfs.empty()){
        long front = bfs.front();
        bfs.pop_front();
        visited.insert(front);
        if(! fill_neighbors(rod_power_sums, rod_to_expression, front, bfs, a_value)){
            return -1;
        }
    }
    if(a_value.has_value()){
        return find_count_given_a(rod_ranges, visited, rod_to_expression, *a_value);
    }
    else{
        return find_max_count(rod_ranges, visited, rod_to_expression);
    }
}

long max_generating_rods(std::map<long, Interval>& rod_ranges, std::map<long, std::vector<Rule>>& rod_power_sums){
    long generating_rods = 0;
    std::map<long, Expression> rod_to_expression;
    for(auto& [rod, range] : rod_ranges){
        if(rod_to_expression.count(rod) != 0){
            continue;
        }
        long new_generating_rods = find_generating_rods(rod_ranges, rod_power_sums, rod_to_expression, rod);
        if(new_generating_rods == -1){
            return -1;
        }
        generating_rods += new_generating_rods;
    }
    return generating_rods;
}

int main(){
    long t;
    std::cin >> t;
    for(long j = 0; j < t; j++){
        long n, m;
        std::cin >> n >> m;
        std::map<long, Interval> rod_ranges;
        for(long i = 0; i < n; i++){
            long start;
            std::cin >> start;
            rod_ranges[i + 1] = Interval{.start = start};
        }
        for(long i = 0; i < n; i++){
            long end;
            std::cin >> end;
            rod_ranges[i + 1].end = end;
        }
        std::map<long, std::vector<Rule>> rod_power_sums;
        for(long i = 0; i < m; i++){
            long x, y, a;
            std::cin >> x >> y >> a;
            rod_power_sums[x].push_back(Rule{.this_id = x, .other_id = y, .sum = a});
            rod_power_sums[y].push_back(Rule{.this_id = y, .other_id = x, .sum = a});
        }
        std::cout << max_generating_rods(rod_ranges, rod_power_sums) << std::endl;
    }
    return 0;
}
