#include <iostream>
#include <vector>

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<int> thing (n, 0);
    for(int i = 0; i < m; i++){
        std::string action;
        std::cin >> action;
        if(action == "Flip"){
            int start, end;
            std::cin >> start >> end;
            for(int i = start; i <= end; i++){
                thing[i] = 1 - thing[i];
            }
        }
        else if(action == "Query"){
            int pos;
            std::cin >> pos;
            std::cout << thing[pos] << std::endl;
        }
    }
    return 0;
}
