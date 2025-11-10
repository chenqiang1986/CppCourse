#include <algorithm>
#include <iostream>
#include <vector>

int find_count_cows_under_single(const std::vector<int>& stalls, const std::vector<int>& cows, int init, int i){
    int count = init;
    for(int j = init; j < cows.size(); j++){
        if(stalls[i] >= cows[j]){
            count++;
        }
        else{
            break;
        }
    }
    return count;
}

std::vector<int> find_count_cows_under(const std::vector<int>& stalls, const std::vector<int>& cows){
    std::vector<int> count_cows_under;
    for(int i = 0; i < stalls.size(); i++){
        if(i == 0){
            int count = find_count_cows_under_single(stalls, cows, 0, i);
            count_cows_under.push_back(count);
        }
        else{
            int count = find_count_cows_under_single(stalls, cows, count_cows_under[i - 1], i);
            count_cows_under.push_back(count);
        }
    }
    return count_cows_under;
}

int main(){
    int n;
    std::cin >> n;
    std::vector<int> cows;
    std::vector<int> stalls;
    for(int i = 0; i < n; i++){
        int cow;
        std::cin >> cow;
        cows.push_back(cow);
    }
    for(int i = 0; i < n; i++){
        int stall;
        std::cin >> stall;
        stalls.push_back(stall);
    }
    std::sort(cows.begin(), cows.end());
    std::sort(stalls.begin(), stalls.end());
    std::vector<int> count_cows_under = find_count_cows_under(stalls, cows);
    long long num_ways = 1;
    bool broken_out = false;
    for(int i = 0; i < count_cows_under.size(); i++){
        num_ways *= count_cows_under[i] - i;
        if(num_ways <= 0){
            broken_out = true;
            break;
        }
    }
    if(broken_out){
        std::cout << 0 << std::endl;
    }
    else{
        std::cout << num_ways << std::endl;
    }
    return 0;
}
