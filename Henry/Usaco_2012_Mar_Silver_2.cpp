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

int find_min_width(std::map<int, MinMax>& x_to_min_max, int min_time){
    int min_width = 1000001;
    int start = 0;
    int end = 0;
    std::map<int, MinMax>::iterator it = x_to_min_max.end();
    it--;
    int max_pos_end = it->first;
    std::set<int> mins;
    std::set<int> maxes;
    mins.insert(x_to_min_max[start].min);
    maxes.insert(x_to_min_max[start].max);
    while(end <= max_pos_end){
        int min = *(mins.begin());
        std::set<int>::iterator it = maxes.end();
        it--;
        int max = *it;
        if(max - min >= min_time){
            min_width = std::min(min_width, end - start);
            if(min_width == 0){
                return 0;
            }
            mins.erase(x_to_min_max[start].min);
            maxes.erase(x_to_min_max[start].max);
            start++;
        }
        else{
            end++;
            mins.insert(x_to_min_max[end].min);
            maxes.insert(x_to_min_max[end].max);
        }
    }
    return min_width;
}

int main(){
    int n, d;
    std::cin >> n >> d;
    std::map<int, MinMax> x_to_min_max;
    for(int i = 0; i < n; i++){
        int x, num;
        std::cin >> x >> num;
        if(x_to_min_max.count(x) == 0){
            x_to_min_max[x] = MinMax{.min = num, .max = num};
        }
        else{
            x_to_min_max[x].insert(num);
        }
    }
    int min_width = find_min_width(x_to_min_max, d);
    std::cout << (min_width != 1000001 ? min_width : -1) << std::endl;
    return 0;
}
