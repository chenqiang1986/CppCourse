#include <iostream>
#include <map>

int find_intersection_count(std::map<int, int>& speeds, int laps){
    std::map<int, int>::iterator it = speeds.end();
    it--;
    int max_speed = it->first;
    int intersections = 0;
    while(true){
        if(it == speeds.begin()){
            break;
        }
        std::map<int, int>::iterator pair_it = it;
        pair_it--;
        while(true){
            intersections += (laps * (it->first - pair_it->first) / max_speed) * it->second * pair_it->second;
            if(pair_it == speeds.begin()){
                break;
            }
            pair_it--;
        }
        it--;
    }
    return intersections;
}

int main(){
    int n, l, c;
    std::cin >> n >> l >> c;
    std::map<int, int> speeds;
    for(int i = 0; i < n; i++){
        int speed;
        std::cin >> speed;
        speeds[speed]++;
    }
    std::cout << find_intersection_count(speeds, l) << std::endl;
    return 0;
}
