#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Earth{
    int quantity;
    int pos;
};

struct CacheKey{
    int index;
    int extra_earth;

    bool operator<(const CacheKey& other)const{
        return this->index < other.index || (this->index == other.index && this->extra_earth < other.extra_earth);
    }
};

std::vector<Earth> find_earths(std::map<int, int>& plot_to_diff){
    std::vector<Earth> earths;
    for(auto& [plot, diff] : plot_to_diff){
        for(int i = 0; i < std::abs(diff); i++){
            earths.push_back(Earth{.quantity = (diff > 0 ? 1 : -1), .pos = plot});
        }
    }
    return earths;
}

int cost(std::vector<Earth>& earths, int index, int extra_earth, int add, int remove, int move, std::map<CacheKey, int>& cache){
    CacheKey cache_key = CacheKey{.index = index, .extra_earth = extra_earth};
    if(cache.count(cache_key) != 0){
        return cache[cache_key];
    }
    if(index == earths.size() - 1){
        int earth_amount = extra_earth + earths[index].quantity;
        int output = std::abs(earth_amount) * (earth_amount > 0 ? add : remove);
        cache[cache_key] = output;
        return output;
    }
    int sell_or_buy_cost = (earths[index].quantity == 1 ? add : remove);
    int moving_base = (earths[index + 1].pos - earths[index].pos) * move;
    int output = std::min(
        sell_or_buy_cost + cost(earths, index + 1, extra_earth, add, remove, move, cache) + std::abs(extra_earth) * moving_base,
        cost(earths, index + 1, extra_earth + earths[index].quantity, add, remove, move, cache) + std::abs(extra_earth + earths[index].quantity) * moving_base
    );
    cache[cache_key] = output;
    return output;
}

int cost_no_pre(std::map<int, int>& plot_to_diff, int index, int extra_earth, int add, int remove, int move, std::map<CacheKey, int>& cache){
    CacheKey cache_key = CacheKey{.index = index, .extra_earth = extra_earth};
    if(cache.count(cache_key) != 0){
        return cache[cache_key];
    }
    if(index == plot_to_diff.size() - 1){
        int earth_amount = extra_earth + plot_to_diff[index];
        int output = std::abs(earth_amount) * (earth_amount > 0 ? add : remove);
        cache[cache_key] = output;
        return output;
    }
    int sell_or_buy_cost = (plot_to_diff[index] > 0 ? add : remove);
    int output = 2100000000;
    for(int i = 0; i <= std::abs(plot_to_diff[index]); i++){
        int new_extra_earth = extra_earth + plot_to_diff[index] - i * (plot_to_diff[index] > 0 ? 1 : -1);
        output = std::min(output, i * sell_or_buy_cost + cost_no_pre(plot_to_diff, index + 1, new_extra_earth, add, remove, move, cache) + std::abs(new_extra_earth) * move);
    }
    cache[cache_key] = output;
    return output;
}

int find_min_cost(std::map<int, int>& plot_to_diff, int add, int remove, int move){
    std::vector<Earth> earths = find_earths(plot_to_diff);
    std::map<CacheKey, int> cache;
    return cost_no_pre(plot_to_diff, 0, 0, add, remove, move, cache);
}

int main(){
    int n, x, y, z;
    std::cin >> n >> x >> y >> z;
    std::map<int, int> plot_to_diff; 
    for(int i = 0; i < n; i++){
        int start, end;
        std::cin >> start >> end;
        plot_to_diff[i] = end - start;
    }
    std::cout << find_min_cost(plot_to_diff, x, y, z) << std::endl;
    return 0;
}
