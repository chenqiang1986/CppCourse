#include <iostream>

long find_pos(long num, long t) {
    std::vector<long> jump_to;
    std::vector<long> jump_time;

    if (t < num+ num || t == 0) {
        return num;
    }

    if (num > 0) {
        jump_time.push_back(num+num);
        jump_to.push_back(num-1);
    } else {
        jump_time.push_back(1);
        jump_to.push_back(0);
    }

    while (true) {
        jump_time.push_back(jump_time[jump_time.size() - 1] + jump_to[jump_to.size() -1] + 1);
        jump_to.push_back(jump_time[jump_time.size() - 1] / 2);

        if (jump_time[jump_time.size() - 1] > t) {
            break;
        }
    }

    long ref_jump_time = jump_time[jump_time.size() -2];
    long ref_jump_to = jump_to[jump_to.size() -2];

    return ref_jump_to - (t-ref_jump_time);
}

std::vector<long> calculate_time_zero_at_begin_scale(long t) {
    std::vector<long> time_zero_at_begin;
    time_zero_at_begin.push_back(0);
    while (true) {
        long last_time_zero_at_begin = time_zero_at_begin[time_zero_at_begin.size() - 1];
        long new_time_zero_at_begin = last_time_zero_at_begin + (last_time_zero_at_begin + 1) /2 + 1;
        time_zero_at_begin.push_back(new_time_zero_at_begin);
        if (new_time_zero_at_begin > t) {
            break;
        }        
    }
    return time_zero_at_begin;
}

long find_value_at_begin(long t) {
    std::vector<long> time_zero_at_begin = calculate_time_zero_at_begin_scale(t);

    std::vector<long> grade_length;
    for (int i = 0; i < time_zero_at_begin.size() -1; i++) {
        grade_length.push_back(time_zero_at_begin[i+1] - time_zero_at_begin[i]);
    }

    std::vector<long> first_inserting_index;
    std::vector<long> last_inserting_index;
    first_inserting_index.push_back(-1);
    last_inserting_index.push_back(-1);

    std::vector<long> first_insert_value;
    first_insert_value.push_back(-1);
    for (int i = 1; i <time_zero_at_begin.size() -1; i++) {
        long new_first_inserting_index = (last_inserting_index[i-1] == grade_length[i-1] - 1 ? 2 : 1);
        first_inserting_index.push_back(new_first_inserting_index);

        long new_last_inserting_index = (grade_length[i] - 1 - new_first_inserting_index) % 3 == 0 ? grade_length[i] - 1 : grade_length[i] - 2;
        last_inserting_index.push_back(new_last_inserting_index);

        first_insert_value.push_back(grade_length[i-1]);
    }

    long grade_index = time_zero_at_begin.size() - 2;
    long grade_offset = t - time_zero_at_begin[grade_index];

    while (true) {
        if (grade_offset == 0) {
            return 0;
        }

        if ((grade_offset - first_inserting_index[grade_index]) % 3 == 0 ) {
            return first_insert_value[grade_index] + (grade_offset - first_inserting_index[grade_index]) / 3;
        }

        if (grade_offset >  first_inserting_index[grade_index]) {
            grade_offset -= (grade_offset - first_inserting_index[grade_index])/3 + 1;
        }
        grade_index--;
    }

    return -10000;
}

long find_value(long pos, long t) {
    if (t < pos + pos) {
        return pos;
    }
    return find_value_at_begin(t+pos);
}

int main() {
    long n;
    std::cin >> n;

    for (long i = 0; i < n; i++) {
        int op;
        std::cin >> op;
        if (op == 1) {
            long pos, t;
            std::cin >> pos >> t;
            std::cout << find_value(pos, t) << std::endl;
        }
        else if (op == 2) {
            long num, t;
            std::cin >> num >> t;
            std::cout << find_pos(num, t) << std::endl;
        }
    }

}