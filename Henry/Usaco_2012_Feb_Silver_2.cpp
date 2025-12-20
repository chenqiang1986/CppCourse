#include <cmath>
#include <iostream>
#include <vector>

int choose(int n, int m){
    int numerator = 1;
    int denominator = 1;
    for(int i = n; i > n - m; i--){
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
    int running_num_of_nums = 0;
    while(true){
        int choose_thing = choose(num_of_0s + k - 1, k - 1);
        if(running_num_of_nums + choose_thing > n){
            break;
        }
        running_num_of_nums += choose_thing;
        if(running_num_of_nums == n){
            break;
        }
        num_of_0s++;
    }
    std::vector<int> space_to_num_of_0s(k, 0);
    space_to_num_of_0s[0] = num_of_0s;
    running_num_of_nums++;
    while(running_num_of_nums < n){
        int last_with_num_index_able_to_move = 0;
        for(int i = 0; i < k - 1; i++){
            if(space_to_num_of_0s[i] > 0){
                last_with_num_index_able_to_move = i;
            }
        }
        space_to_num_of_0s[last_with_num_index_able_to_move] -= 1;
        space_to_num_of_0s[last_with_num_index_able_to_move + 1] += 1;
        running_num_of_nums++;
    }
    for(int i = 0; i < k; i++){
        std::cout << 1;
        for(int j = 0; j < space_to_num_of_0s[i]; j++){
            std::cout << 0;
        }
    }
    std::cout << std::endl;
    return 0;
}
