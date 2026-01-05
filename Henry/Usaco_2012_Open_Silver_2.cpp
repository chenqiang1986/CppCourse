#include <iostream>
#include <map>
#include <vector>

struct Book{
    int height;
    int width;
};

int find_min_height(std::vector<Book>& books, int start_index, int max_width, std::map<int, int>& cache){
    if(start_index >= books.size()){
        return 0;
    }
    if(cache.count(start_index) != 0){
        return cache[start_index];
    }
    int running_width = 0;
    int running_level_height = 0;
    int min_height = 2100000000;
    for(int i = start_index; i < books.size(); i++){
        running_width += books[i].width;
        running_level_height = std::max(running_level_height, books[i].height);
        if(running_width > max_width){
            break;
        }
        min_height = std::min(min_height, running_level_height + find_min_height(books, i + 1, max_width, cache));
    }
    cache[start_index] = min_height;
    return cache[start_index];
}

int main(){
    int n, l;
    std::cin >> n >> l;
    std::vector<Book> books;
    for(int i = 0; i < n; i++){
        Book book;
        std::cin >> book.height >> book.width;
        books.push_back(book);
    }
    std::map<int, int> cache;
    std::cout << find_min_height(books, 0, l, cache) << std::endl;
    return 0;
}
