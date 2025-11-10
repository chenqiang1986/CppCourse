#include <algorithm>
#include <iostream>
#include <vector>

int find_count_cows_under_single(const std::vector<int>& stalls, const std::vector<int>& cows, int init, int i){
    for(int j = init; j < cows.size(); j++){
        if(stalls[i] < cows[j]){
            return j;
        }
    }
    return cows.size();
}

std::vector<int> find_count_cows_under(const std::vector<int>& stalls, const std::vector<int>& cows){
    std::vector<int> count_cows_under;
    for(int i = 0; i < stalls.size(); i++){
        int count = find_count_cows_under_single(stalls, cows, i == 0 ? 0 : count_cows_under[i - 1], i);
        count_cows_under.push_back(count);
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
    for(int i = 0; i < count_cows_under.size(); i++){
        num_ways *= std::max(0, count_cows_under[i] - i);
    }
    std::cout << num_ways << std::endl;
    return 0;
}
