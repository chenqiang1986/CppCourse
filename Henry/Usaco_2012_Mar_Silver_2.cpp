#include <iostream>
#include <map>
#include <set>

struct MinMax{
    int min;
    int max;

    void insert(int num){
        if(num > this->max){
            this->max = num;
        }
        else if(num < this->min){
            this->min = num;
        }
    }
};

int find_min_width(std::map<int, MinMax>& x_to_min_max, std::set<int>& xs, int min_time){
    int min_width = 1000001;
    std::map<int, MinMax>::iterator start = x_to_min_max.begin();
    std::map<int, MinMax>::iterator end = x_to_min_max.begin();
    std::map<int, int> mins;
    std::map<int, int> maxes;
    mins[start->second.min]++;
    maxes[start->second.max]++;
    while(true){
        int min = mins.begin()->first;
        std::map<int, int>::iterator it = maxes.end();
        it--;
        int max = it->first;
        if(max - min >= min_time){
            min_width = std::min(min_width, end->first - start->first);
            if(min_width == 0){
                return 0;
            }
            mins[start->second.min]--;
            if(mins[start->second.min] == 0){
                mins.erase(start->second.min);
            }
            maxes[start->second.max]--;
            if(maxes[start->second.max] == 0){
                maxes.erase(start->second.max);
            }
            start++;
        }
        else{
            end++;
            if(end == x_to_min_max.end()){
                break;
            }
            mins[end->second.min]++;
            maxes[end->second.max]++;
        }
    }
    return min_width;
}

int main(){
    int n, d;
    std::cin >> n >> d;
    std::set<int> xs;
    std::map<int, MinMax> x_to_min_max;
    for(int i = 0; i < n; i++){
        int x, num;
        std::cin >> x >> num;
        xs.insert(x);
        if(x_to_min_max.count(x) == 0){
            x_to_min_max[x] = MinMax{.min = num, .max = num};
        }
        else{
            x_to_min_max[x].insert(num);
        }
    }
    int min_width = find_min_width(x_to_min_max, xs, d);
    std::cout << (min_width != 1000001 ? min_width : -1) << std::endl;
    return 0;
}
