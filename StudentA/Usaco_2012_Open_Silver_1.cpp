#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <deque>
#include <map>

struct Position {
    int x;
    int y;

    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool operator< (const Position& other) const {
        return this->x < other.x || (this->x == other.x && this->y < other.y);
    }
};

Position directions[4] = {
    Position(-1, 0),
    Position(+1, 0),
    Position(0, -1),
    Position(0, +1)
};

struct Piece {
    std::vector<Position> pos;

    void move(Position delta) {
        for (int i = 0; i < pos.size(); i++) {
            pos[i].x += delta.x;
            pos[i].y += delta.y;
        }
    }

    std::pair<Position, Position> bounding() const {
        int max_x = pos[0].x;
        int min_x = pos[0].x;
        int max_y = pos[0].y;
        int min_y = pos[0].y;

        for (int i = 0; i < pos.size(); i++) {
            max_x = std::max(max_x, pos[i].x);
            max_y = std::max(max_y, pos[i].y);
            min_x = std::min(min_x, pos[i].x);
            min_y = std::min(min_y, pos[i].y);
        }

        return std::make_pair(Position(min_x, min_y), Position(max_x, max_y));
    }

    bool has_overlap(const Piece& other) const {
        std::set<Position> this_covered;
        for (int i = 0; i < pos.size(); i++) {
            this_covered.insert(pos[i]);
        }

        for (int i = 0; i < other.pos.size(); i++) {
            if (this_covered.count(other.pos[i]) > 0) {
                return true;
            }
        }
        return false;
    }

    bool bounding_overlap(const Piece& other) const {
        std::pair<Position, Position> this_bound = this->bounding();
        std::pair<Position, Position> other_bound = other.bounding();

        if (this_bound.first.x > other_bound.second.x) {
            return false;
        }

        if (other_bound.first.x > this_bound.second.x) {
            return false;
        }


        if (this_bound.first.y > other_bound.second.y) {
            return false;
        }

        if (other_bound.first.y > this_bound.second.y) {
            return false;
        }

        return true;
    }
};

struct PieceSet {
    std::vector<Piece> pieces;
    
    bool operator< (const PieceSet& other) const {
        if (pieces.size() != other.pieces.size()) {
            return pieces.size() < other.pieces.size();
        }

        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i].pos.size() != other.pieces[i].pos.size()) {
                return pieces[i].pos.size() < other.pieces[i].pos.size();
            }

            for (int j = 0; j < pieces[i].pos.size(); j++) {
                if (pieces[i].pos[j] < other.pieces[i].pos[j]) {
                    return true;
                }
                else if (other.pieces[i].pos[j] < pieces[i].pos[j]) {
                    return false;
                }
            }
        }
        
        return false;
    }

    bool has_overlap() {
        for (int i =0; i < pieces.size(); i++) {
            for (int j = i+1; j < pieces.size(); j++) {
                if (pieces[i].has_overlap(pieces[j])) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_boundary_apart() {
        for (int i =0; i < pieces.size(); i++) {
            for (int j = i+1; j < pieces.size(); j++) {
                if (pieces[i].bounding_overlap(pieces[j])) {
                    return false;
                }
            }
        }
        return true;
    }
};

void debug_output(PieceSet& piece_set) {
    for (int i = 0; i< piece_set.pieces.size(); i++) {
        std::cout << i << std::endl;
        for (int j = 0; j < piece_set.pieces[i].pos.size(); j++) {
            std::cout << piece_set.pieces[i].pos[j].x <<' '<< piece_set.pieces[i].pos[j].y << std::endl;
        }
    }
}

void normalize(PieceSet& to) {
    Position normalize_d(-to.pieces[0].pos[0].x, -to.pieces[0].pos[0].y);
    for (int i = 0; i < to.pieces.size(); i++) {
        to.pieces[i].move(normalize_d);
    }

    // Remove the piece that are already apart from others
    std::vector<int> disjoint_index;
    for (int i = to.pieces.size() - 1; i >=0; i--) {
        bool is_ith_disjoint = true;
        for (int j = 0; j < to.pieces.size(); j++) {
            if (j != i && to.pieces[i].bounding_overlap(to.pieces[j])) {
                is_ith_disjoint = false;
            }
        }

        if (is_ith_disjoint){
            disjoint_index.push_back(i);
        }
    }

    for (int i : disjoint_index) {
        to.pieces.erase(to.pieces.begin()+i);
    }
}

void expand(const PieceSet& from, std::deque<PieceSet>& bfs, std::map<PieceSet, int>& set_to_steps) {
    int from_steps = set_to_steps[from];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < from.pieces.size(); j++) {
            PieceSet to = from;
            to.pieces[j].move(directions[i]);
            if (to.has_overlap()) {
                // Invalid move
                continue;
            }

            normalize(to);
            if (set_to_steps.count(to) == 0) {
                set_to_steps[to] = from_steps + 1;
                bfs.push_back(to);
            }
        }
    }    
}

int min_move_out(const PieceSet& initial) {
    std::deque<PieceSet> bfs;
    std::map<PieceSet, int> set_to_steps;

    bfs.push_back(initial);
    set_to_steps[initial] = 0;

    while (!bfs.empty()) {
        PieceSet piece_set = bfs.front();
        //debug_output(piece_set);
        bfs.pop_front();
        if (piece_set.is_boundary_apart()) {
            return set_to_steps[piece_set];
        }

        expand(piece_set, bfs, set_to_steps);
    }

    return -1;
}

int main() {
    int N[3];
    std::cin >> N[0] >> N[1] >> N[2];

    PieceSet initial;
    for (int i = 0; i < 3; i++) {
        Piece piece;
        for (int j = 0; j < N[i]; j++) {
            int x, y;
            std::cin >> x >> y;
            piece.pos.push_back(Position(x, y));
        }

        initial.pieces.push_back(piece);
    }
    normalize(initial);

    std::cout << min_move_out(initial) << std::endl;
}