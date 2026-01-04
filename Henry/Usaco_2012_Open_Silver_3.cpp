#include <iostream>
#include <map>

long find_intersection_count(std::map<long, long>& speeds, long laps){
    std::map<long, long>::iterator it = std::next(speeds.end(), -1);
    long max_speed = it->first;
    long intersections = 0;
    for(auto& [speed_one, count_one] : speeds){
        for(auto& [speed_two, count_two] : speeds){
            if(speed_one < speed_two){
                long one_to_one = ((laps * (speed_two - speed_one)) / max_speed);
                intersections += one_to_one * count_one * count_two;
            }
        }
    }
    return intersections;
}

int main(){
    long n, l, c;
    std::cin >> n >> l >> c;
    std::map<long, long> speeds;
    for(long i = 0; i < n; i++){
        long speed;
        std::cin >> speed;
        speeds[speed]++;
    }
    std::cout << find_intersection_count(speeds, l) << std::endl;
    return 0;
}
