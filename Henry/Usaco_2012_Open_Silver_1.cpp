#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <set>

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

bool is_seperated(std::vector<Shifts>& curr_shifts, Block& block1, Block& block2, Block& block3){
    int block1_top = block1.top + curr_shifts[0].col_shift;
    int block1_bottom = block1.bottom + curr_shifts[0].col_shift;
    int block1_left = block1.left + curr_shifts[0].row_shift;
    int block1_right = block1.right + curr_shifts[0].row_shift;
    int block2_top = block2.top + curr_shifts[1].col_shift;
    int block2_bottom = block2.bottom + curr_shifts[1].col_shift;
    int block2_left = block2.left + curr_shifts[1].row_shift;
    int block2_right = block2.right + curr_shifts[1].row_shift;
    int block3_top = block3.top + curr_shifts[2].col_shift;
    int block3_bottom = block3.bottom + curr_shifts[2].col_shift;
    int block3_left = block3.left + curr_shifts[2].row_shift;
    int block3_right = block3.right + curr_shifts[2].row_shift;
    if(! ((block1_bottom < block2_top || block1_top > block2_bottom) || (block1_left > block2_right || block1_right < block2_left))){
        return false;
    }
    if(! ((block1_bottom < block3_top || block1_top > block3_bottom) || (block1_left > block3_right || block1_right < block3_left))){
        return false;
    }
    if(! ((block2_bottom < block3_top || block2_top > block3_bottom) || (block2_left > block3_right || block2_right < block3_left))){
        return false;
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

int min_moves(Block& block1, Block& block2, Block& block3){
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
        if(is_seperated(curr_shifts, block1, block2, block3)){
            return shifts_to_min_moves[curr_shifts];
        }
        bfs.pop_front();
        find_all_possible_moves(bfs, shifts_to_min_moves, curr_shifts, block1, block2, block3);
    }
    return -1;
}

int main(){
    int blocks1, blocks2, blocks3;
    std::cin >> blocks1 >> blocks2 >> blocks3;
    Block block1;
    Block block2;
    Block block3;
    for(int i = 0; i < blocks1; i++){
        Coord component;
        std::cin >> component.row >> component.col;
        block1.components.insert(component);
    }
    for(int i = 0; i < blocks2; i++){
        Coord component;
        std::cin >> component.row >> component.col;
        block2.components.insert(component);
    }
    for(int i = 0; i < blocks3; i++){
        Coord component;
        std::cin >> component.row >> component.col;
        block3.components.insert(component);
    }
    block1.find_bounding_box();
    block2.find_bounding_box();
    block3.find_bounding_box();
    std::cout << min_moves(block1, block2, block3) << std::endl;
    return 0;
}
