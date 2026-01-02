#include <iostream>
#include <map>
#include <set>

struct StartEnd{
    int start;
    int end;
};

int main(){
    int n, x, y, z;
    std::cin >> n >> x >> y >> z;
    std::map<int, StartEnd> plot_to_dirt_start_end; 
    for(int i = 0; i < n; i++){
        int start, end;
        std::cin >> start >> end;
        plot_to_dirt_start_end[i] = StartEnd{.start = start, .end = end};
    }
    if(z > x + y){
        int cost = 0;
        for(int i = 0; i < n; i++){
            if(plot_to_dirt_start_end[i].start > plot_to_dirt_start_end[i].end){
                cost += y * (plot_to_dirt_start_end[i].start - plot_to_dirt_start_end[i].end);
            }
            else{
                cost += x * (plot_to_dirt_start_end[i].end - plot_to_dirt_start_end[i].start);
            }
        }
        std::cout << cost << std::endl;
    }
    else{
        std::cout << 210 << std::endl;
    }
    return 0;
}
