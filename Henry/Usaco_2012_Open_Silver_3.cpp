#include <iostream>
#include <unordered_map>

long find_intersection_count(std::unordered_map<long, long>& speeds, long laps){
    std::unordered_map<long, long>::iterator it = std::next(speeds.end(), -1);
    long max_speed = it->first;
    long intersections = 0;
    for(std::unordered_map<long, long>::iterator i = speeds.begin(); i != speeds.end(); i++){
        for(std::unordered_map<long, long>::iterator j = i; j != speeds.end(); j++){
            if(i != j){
                long one_to_one = ((laps * (j->first - i->first)) / max_speed);
                intersections += one_to_one * j->second * i->second;
            }
        }
    }
    return intersections;
}

int main(){
    long n, l, c;
    std::cin >> n >> l >> c;
    std::unordered_map<long, long> speeds;
    for(long i = 0; i < n; i++){
        long speed;
        std::cin >> speed;
        speeds[speed]++;
    }
    std::cout << find_intersection_count(speeds, l) << std::endl;
    return 0;
}
