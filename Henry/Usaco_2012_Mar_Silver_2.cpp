#include <iostream>
#include <map>
#include <set>

struct MinMax{
    int min;
    int max;

    void insert(int num){
        if(num > max){
            max = num;
        }
        else if(num < min){
            min = num;
        }
    }
};

int find_min_width(std::map<int, MinMax>& x_to_min_max, std::set<int>& xs, int min_time){
    int min_width = 1000001;
    std::map<int, MinMax>::iterator start = x_to_min_max.begin();
    std::map<int, MinMax>::iterator end = x_to_min_max.begin();
    std::set<int> mins;
    std::set<int> maxes;
    mins.insert(start->second.min);
    maxes.insert(start->second.max);
    while(end != x_to_min_max.end()){
        int min = *(mins.begin());
        std::set<int>::iterator it = maxes.end();
        it--;
        int max = *it;
        if(max - min >= min_time){
            min_width = std::min(min_width, end->first - start->first);
            if(min_width == 0){
                return 0;
            }
            mins.erase(start->second.min);
            maxes.erase(start->second.max);
            start++;
        }
        else{
            end++;
            mins.insert(end->second.min);
            maxes.insert(end->second.max);
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
