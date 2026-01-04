#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Shifts{
    int row_shift;
    int col_shift;

    bool operator<(const Shifts& other)const{
        return this->row_shift < other.row_shift || (this->row_shift == other.row_shift && this->col_shift < other.col_shift);
    }

    Shifts operator+(const Shifts& other)const{
        return Shifts{.row_shift = this->row_shift + other.row_shift, .col_shift = this->col_shift + other.col_shift};
    }
    Shifts operator-(const Shifts& other)const{
        return Shifts{.row_shift = this->row_shift - other.row_shift, .col_shift = this->col_shift - other.col_shift};
    }
};

Shifts BASIC_SHIFTS[] = {
    Shifts{.row_shift = 0, .col_shift = -1},
    Shifts{.row_shift = 0, .col_shift = 1},
    Shifts{.row_shift = -1, .col_shift = 0},
    Shifts{.row_shift = 1, .col_shift = 0}
};

Shifts ZERO_SHIFT = Shifts{.row_shift = 0, .col_shift = 0};

struct Coord{
    int row;
    int col;

    bool operator<(const Coord& other)const{
        return this->row < other.row || (this->row == other.row && this->col < other.col);
    }

    Coord operator+(const Shifts& other)const{
        return Coord{.row = this->row + other.row_shift, .col = this->col + other.col_shift};
    }
};

struct Block{
    std::set<Coord> components;
    int min_col;
    int max_col;
    int min_row;
    int max_row;

    void find_bounding_box(){
        min_col = components.begin()->col;
        max_col = components.begin()->col;
        min_row = components.begin()->row;
        max_row = components.begin()->row;
        for(auto& coord : components){
            min_col = std::min(min_col, coord.col);
            max_col = std::max(max_col, coord.col);
            min_row = std::min(min_row, coord.row);
            max_row = std::max(max_row, coord.row);
        }
    }
};

bool is_seperated(const Shifts& first_shifts, const Block& first_block, const Shifts& second_shifts, const Block& second_block){
    int first_min_col = first_block.min_col + first_shifts.col_shift;
    int first_max_col = first_block.max_col + first_shifts.col_shift;
    int first_min_row = first_block.min_row + first_shifts.row_shift;
    int first_max_row = first_block.max_row + first_shifts.row_shift;
    int second_min_col = second_block.min_col + second_shifts.col_shift;
    int second_max_col = second_block.max_col + second_shifts.col_shift;
    int second_min_row = second_block.min_row + second_shifts.row_shift;
    int second_max_row = second_block.max_row + second_shifts.row_shift;
    if(first_min_col > second_max_col || second_min_col > first_max_col){
        return true;
    }
    if(first_min_row > second_max_row || second_min_row > first_max_row){
        return true;
    }
    return false;
}

bool is_seperated(const std::vector<Shifts>& curr_shifts, const std::vector<Block>& blocks){
    for(int i = 0; i < 3; i++){
        for(int j = i + 1; j < 3; j++){
            if(! is_seperated(curr_shifts[i], blocks[i], curr_shifts[j], blocks[j])){
                return false;
            }
        }
    }
    return true;
}

bool is_valid_move(const std::vector<Shifts>& curr_shifts, const std::vector<Block>& blocks, int moving_index, const Shifts& basic_shift){
    std::set<Coord> after_move_all;
    for(int i = 0; i < 3; i++){
        Shifts effective_shift = curr_shifts[i] + (i == moving_index ? basic_shift : ZERO_SHIFT);
        for(auto& component : blocks[i].components){
            Coord effective_component = component + effective_shift;
            if(after_move_all.count(effective_component) != 0){
                return false;
            }
            after_move_all.insert(effective_component);
        }
    }
    return true;
}

std::set<Shifts> find_possible_moves(std::vector<Shifts>& curr_shifts, std::vector<Block>& blocks, int moving_index){
    std::set<Shifts> possible_moves;
    for(int i = 0; i < 4; i++){
        if(is_valid_move(curr_shifts, blocks, moving_index, BASIC_SHIFTS[i])){
            possible_moves.insert(BASIC_SHIFTS[i]);
        }
    }
    return possible_moves;
}

std::vector<Shifts> normalize(const std::vector<Shifts>& shifts){
    std::vector<Shifts> result;
    Shifts base = shifts[0];
    for(int i = 0; i < shifts.size(); i++){
        result.push_back(shifts[i] - base);
    }
    return result;
}

bool is_in_range(std::vector<Shifts> shifts){
    for(int i = 0; i < shifts.size(); i++){
        if(std::abs(shifts[i].row_shift) > 10 || std::abs(shifts[i].col_shift) > 10){
            return false;
        }
    }
    return true;
}

void find_all_possible_moves(std::deque<std::vector<Shifts>>& bfs, std::map<std::vector<Shifts>, int>& shifts_to_min_moves, std::vector<Shifts>& curr_shifts, std::vector<Block>& blocks){
    for(int i = 0; i < 3; i++){
        std::set<Shifts> possible_shifts = find_possible_moves(curr_shifts, blocks, i);
        for(auto& shift : possible_shifts){
            std::vector<Shifts> new_shifts = curr_shifts;
            new_shifts[i] = new_shifts[i] + shift;
            new_shifts = normalize(new_shifts);
            if(shifts_to_min_moves.count(new_shifts) == 0 && is_in_range(new_shifts)){
                bfs.push_back(new_shifts);
                shifts_to_min_moves[new_shifts] = shifts_to_min_moves[curr_shifts] + 1;
            }
        }
    }
}

int min_moves(std::vector<Block> blocks){
    std::vector<Shifts> block_shifts;
    block_shifts.push_back(Shifts{.row_shift = 0, .col_shift = 0});
    block_shifts.push_back(Shifts{.row_shift = 0, .col_shift = 0});
    block_shifts.push_back(Shifts{.row_shift = 0, .col_shift = 0});
    std::map<std::vector<Shifts>, int> shifts_to_min_moves;
    std::deque<std::vector<Shifts>> bfs;
    bfs.push_back(block_shifts);
    shifts_to_min_moves[block_shifts] = 0;
    while(! bfs.empty()){
        std::vector<Shifts> curr_shifts = bfs.front();
        if(is_seperated(curr_shifts, blocks)){
            return shifts_to_min_moves[curr_shifts];
        }
        bfs.pop_front();
        find_all_possible_moves(bfs, shifts_to_min_moves, curr_shifts, blocks);
    }
    return -1;
}

int main(){
    std::vector<int> block_sizes;
    for(int i = 0; i < 3; i++){
        int block_size;
        std::cin >> block_size;
        block_sizes.push_back(block_size);
    }
    std::vector<Block> blocks (3, Block{});
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < block_sizes[i]; j++){
            Coord component;
            std::cin >> component.row >> component.col;
            blocks[i].components.insert(component);
        }
        blocks[i].find_bounding_box();
    }
    std::cout << min_moves(blocks) << std::endl;
    return 0;
}
