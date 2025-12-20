#include <cmath>
#include <iostream>
#include <vector>

int choose(int n, int m){
    unsigned long long numerator = 1;
    unsigned long long denominator = 1;
    for(int i = n - m + 1; i <= n; i++){
        numerator *= i;
    }
    for(int i = 1; i <= m; i++){
        denominator *= i;
    }
    return numerator / denominator;
}

int main(){
    int n, k;
    std::cin >> n >> k;
    int num_of_0s = 0;
    unsigned long long running_num_of_nums = 0;
    while(true){
        unsigned long long choose_thing = choose(num_of_0s + k - 1, k - 1);
        if(running_num_of_nums + choose_thing >= n){
            break;
        }
        running_num_of_nums += choose_thing;
        num_of_0s++;
    }
    std::vector<int> nums(k + num_of_0s, 0);
    nums[0] = 1;
    int num_of_1s = k - 1;
    for(int i = 1; i < nums.size(); i++){
        if(num_of_0s == 0){
            nums[i] = 1;
            num_of_1s--;
            continue;
        }
        if(num_of_1s == 0){
            nums[i] = 0;
            num_of_0s--;
            continue;
        }
        int choose_thing = choose(num_of_0s + num_of_1s - 1 , num_of_1s);
        if(running_num_of_nums + choose_thing >= n){
            nums[i] = 0;
            num_of_0s--;
        }
        else{
            running_num_of_nums += choose_thing;
            nums[i] = 1;
            num_of_1s--;
        }
    }
    for(int i = 0; i < nums.size(); i++){
        std::cout << nums[i];
    }
    std::cout << std::endl;
    return 0;
}
