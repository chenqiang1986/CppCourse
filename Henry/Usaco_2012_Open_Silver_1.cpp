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
    int top;
    int bottom;
    int left;
    int right;

    void find_bounding_box(){
        top = components.begin()->col;
        bottom = components.begin()->col;
        left = components.begin()->row;
        right = components.begin()->row;
        for(auto& coord : components){
            top = std::min(top, coord.col);
            bottom = std::max(bottom, coord.col);
            left = std::min(left, coord.row);
            right = std::max(right, coord.row);
        }
    }
};

bool is_seperated(const Shifts& first_shifts, const Block& first_block, const Shifts& second_shifts, const Block& second_block){
    int first_top = first_block.top + first_shifts.col_shift;
    int first_bottom = first_block.bottom + first_shifts.col_shift;
    int first_left = first_block.left + first_shifts.row_shift;
    int first_right = first_block.right + first_shifts.row_shift;
    int second_top = second_block.top + second_shifts.col_shift;
    int second_bottom = second_block.bottom + second_shifts.col_shift;
    int second_left = second_block.left + second_shifts.row_shift;
    int second_right = second_block.right + second_shifts.row_shift;
    if(first_top > second_bottom || second_top > first_bottom){
        return true;
    }
    if(first_left > second_right || second_left > first_right){
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



/*
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Coord{
    int row;
    int col;

    bool operator<(const Coord& other)const{
        return this->row < other.row || (this->row == other.row && this->col < other.col);
    }
};

struct Shifts{
    int row_shift;
    int col_shift;

    bool operator<(const Shifts& other)const{
        return this->row_shift < other.row_shift || (this->row_shift == other.row_shift && this->col_shift < other.col_shift);
    }
};

struct Block{
    std::set<Coord> components;
    int top;
    int bottom;
    int left;
    int right;

    void find_bounding_box(){
        top = components.begin()->col;
        bottom = components.begin()->col;
        left = components.begin()->row;
        right = components.begin()->row;
        for(auto& coord : components){
            top = std::min(top, coord.col);
            bottom = std::max(bottom, coord.col);
            left = std::min(left, coord.row);
            right = std::max(right, coord.row);
        }
    }
};

bool is_seperated(const Shifts& first_shifts, const Block& first_block, const Shifts& second_shifts, const Block& second_block){
    int first_top = first_block.top + first_shifts.col_shift;
    int first_bottom = first_block.bottom + first_shifts.col_shift;
    int first_left = first_block.left + first_shifts.row_shift;
    int first_right = first_block.right + first_shifts.row_shift;
    int second_top = second_block.top + second_shifts.col_shift;
    int second_bottom = second_block.bottom + second_shifts.col_shift;
    int second_left = second_block.left + second_shifts.row_shift;
    int second_right = second_block.right + second_shifts.row_shift;
    if(first_top > second_bottom || second_top > first_bottom){
        return true;
    }
    if(first_left > second_right || second_left > first_right){
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

std::set<Shifts> find_possible_moves(Block& moving_block, Shifts& moving_block_shifts, Block& other1, Shifts& other1_shifts, Block& other2, Shifts& other2_shifts){
    std::set<Shifts> possible_moves;
    possible_moves.insert(Shifts{.row_shift = 0, .col_shift = -1});
    possible_moves.insert(Shifts{.row_shift = 0, .col_shift = 1});
    possible_moves.insert(Shifts{.row_shift = -1, .col_shift = 0});
    possible_moves.insert(Shifts{.row_shift = 1, .col_shift = 0});
    for(auto& component : moving_block.components){
        Coord other1_up = Coord{.row = component.row + moving_block_shifts.row_shift - other1_shifts.row_shift, .col = component.col + moving_block_shifts.col_shift - other1_shifts.col_shift - 1};
        Coord other1_down = Coord{.row = component.row + moving_block_shifts.row_shift - other1_shifts.row_shift, .col = component.col + moving_block_shifts.col_shift - other1_shifts.col_shift + 1};
        Coord other1_left = Coord{.row = component.row + moving_block_shifts.row_shift - other1_shifts.row_shift - 1, .col = component.col + moving_block_shifts.col_shift - other1_shifts.col_shift};
        Coord other1_right = Coord{.row = component.row + moving_block_shifts.row_shift - other1_shifts.row_shift + 1, .col = component.col + moving_block_shifts.col_shift - other1_shifts.col_shift};
        Coord other2_up = Coord{.row = component.row + moving_block_shifts.row_shift - other2_shifts.row_shift, .col = component.col + moving_block_shifts.col_shift - other2_shifts.col_shift - 1};
        Coord other2_down = Coord{.row = component.row + moving_block_shifts.row_shift - other2_shifts.row_shift, .col = component.col + moving_block_shifts.col_shift - other2_shifts.col_shift + 1};
        Coord other2_left = Coord{.row = component.row + moving_block_shifts.row_shift - other2_shifts.row_shift - 1, .col = component.col + moving_block_shifts.col_shift - other2_shifts.col_shift};
        Coord other2_right = Coord{.row = component.row + moving_block_shifts.row_shift - other2_shifts.row_shift + 1, .col = component.col + moving_block_shifts.col_shift - other2_shifts.col_shift};
        if(other1.components.count(other1_up) != 0 || other2.components.count(other2_up) != 0){
            possible_moves.erase(Shifts{.row_shift = 0, .col_shift = -1});
        }
        if(other1.components.count(other1_down) != 0 || other2.components.count(other2_down) != 0){
            possible_moves.erase(Shifts{.row_shift = 0, .col_shift = 1});
        }
        if(other1.components.count(other1_left) != 0 || other2.components.count(other2_left) != 0){
            possible_moves.erase(Shifts{.row_shift = -1, .col_shift = 0});
        }
        if(other1.components.count(other1_right) != 0 || other2.components.count(other2_right) != 0){
            possible_moves.erase(Shifts{.row_shift = 1, .col_shift = 0});
        }
    }
    return possible_moves;
}

void find_all_possible_moves(std::deque<std::vector<Shifts>>& bfs, std::map<std::vector<Shifts>, int>& shifts_to_min_moves, std::vector<Shifts>& curr_shifts, Block& block1, Block& block2, Block& block3){
    std::set<Shifts> block1_moves = find_possible_moves(block1, curr_shifts[0], block2, curr_shifts[1], block3, curr_shifts[2]);
    std::set<Shifts> block2_moves = find_possible_moves(block2, curr_shifts[1], block1, curr_shifts[0], block3, curr_shifts[2]);
    std::set<Shifts> block3_moves = find_possible_moves(block3, curr_shifts[2], block1, curr_shifts[0], block2, curr_shifts[1]);
    for(auto& move : block1_moves){
        std::vector<Shifts> new_shifts = curr_shifts;
        new_shifts[0].row_shift += move.row_shift;
        new_shifts[0].col_shift += move.col_shift;
        if(shifts_to_min_moves.count(new_shifts) == 0 && (new_shifts[0].row_shift < 10 && new_shifts[0].row_shift > -10) && (new_shifts[0].col_shift < 10 && new_shifts[0].col_shift > -10)){
            bfs.push_back(new_shifts);
            shifts_to_min_moves[new_shifts] = shifts_to_min_moves[curr_shifts] + 1;
        }
    }
    for(auto& move : block2_moves){
        std::vector<Shifts> new_shifts = curr_shifts;
        new_shifts[1].row_shift += move.row_shift;
        new_shifts[1].col_shift += move.col_shift;
        if(shifts_to_min_moves.count(new_shifts) == 0 && (new_shifts[1].row_shift < 10 && new_shifts[1].row_shift > -10) && (new_shifts[1].col_shift < 10 && new_shifts[1].col_shift > -10)){
            bfs.push_back(new_shifts);
            shifts_to_min_moves[new_shifts] = shifts_to_min_moves[curr_shifts] + 1;
        }
    }
    for(auto& move : block3_moves){
        std::vector<Shifts> new_shifts = curr_shifts;
        new_shifts[2].row_shift += move.row_shift;
        new_shifts[2].col_shift += move.col_shift;
        if(shifts_to_min_moves.count(new_shifts) == 0 && (new_shifts[2].row_shift < 10 && new_shifts[2].row_shift > -10) && (new_shifts[2].col_shift < 10 && new_shifts[2].col_shift > -10)){
            bfs.push_back(new_shifts);
            shifts_to_min_moves[new_shifts] = shifts_to_min_moves[curr_shifts] + 1;
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
        find_all_possible_moves(bfs, shifts_to_min_moves, curr_shifts, blocks[0], blocks[1], blocks[2]);
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
*/
