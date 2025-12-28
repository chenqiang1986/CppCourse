#include <iostream>

void add_range(
    std::vector<long> & data,
    int l, int r
) {
    for (int i = l; i <=r; i++) {
        data[i] += i-l+1;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<long> data(n, 0);
    for (int i = 0; i <m; i++) {
        int l, r; 
        std::cin >> l >> r;
        add_range(data, l, r);
    }

    std::cout << data[0];
    for (int i = 1; i < n; i++) {
        
        std::cout << " " << data[i];
    }
    std::cout <<std::endl;
}