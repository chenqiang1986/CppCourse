#include <iostream>
#include <map>
#include <deque>
#include <cassert>

struct Bound {
    long lower;
    long upper;
};

struct Equation {
    long this_id;
    long other_id;
    long sum;
};

struct Expression {
    // Represents the expression
    // coeff * value[letter_id] + constant
    long coeff;
    long letter_id;
    long constant;

    long evaluate(long letter_value) {
        return constant + coeff * letter_value;
    }
};

Expression operator-(long number, Expression exp) {
    return Expression{
        .constant=number - exp.constant,
        .letter_id = exp.letter_id,
        .coeff = -exp.coeff
    };
}

bool assign(
    std::map<long, Expression>& id_to_exp,
    std::map<long, long>& id_to_fixed_value,
    long to_id,
    const Expression& to_expression,
    std::deque<long>& bfs
) {
    if (id_to_exp.count(to_id)==0) {
        id_to_exp[to_id] = to_expression;
        bfs.push_back(to_id);
        return true;
    }

    Expression old_expression = id_to_exp[to_id];
    assert(old_expression.letter_id == to_expression.letter_id);

    // Same coefficient, either duplication expression, or contradiction.
    if (old_expression.coeff == to_expression.coeff) {
        return old_expression.constant == to_expression.constant;
    }

    // Different coefficient, solution will exist in R
    // value[letter_id] = (to_expression.constant - old_expression.constant) / (- to_expression.coeff + old_expression.coeff)
    if ( (to_expression.constant - old_expression.constant) % (- to_expression.coeff + old_expression.coeff) != 0) {
        // Cannot perform integer division, no solution in Z
        return false;
    }

    long potential_fixed_value = (to_expression.constant - old_expression.constant) / (- to_expression.coeff + old_expression.coeff);

    if (id_to_fixed_value.count(old_expression.letter_id) == 0) {
        id_to_fixed_value[old_expression.letter_id] = potential_fixed_value;
        return true;
    }
    else {
        return  id_to_fixed_value[old_expression.letter_id] == potential_fixed_value;
    }
}

// Returns False if contradiction found
bool expand(
    std::map<long, std::vector<Equation>>& id_to_equ,
    std::map<long, Expression>& id_to_exp,
    std::map<long, long>& id_to_fixed_value,
    long from_id,
    std::deque<long>& bfs
) {
    for (Equation equ : id_to_equ[from_id]) {
        long to_id = equ.other_id;
        Expression to_expression = equ.sum - id_to_exp[from_id];

        if (!assign(id_to_exp, id_to_fixed_value, to_id, to_expression, bfs)) {
            return false;
        }
    }
    return true;
}

long calculate_fixed_valued_working(
    std::vector<long>& ids_in_component,
    std::map<long, Bound>& active_condition,
    std::map<long, Expression>& id_to_exp,
    long letter_value
) {
    long counter = 0;
    for (long id : ids_in_component) {
        long value_at_id = id_to_exp[id].evaluate(letter_value);
        if (value_at_id >= active_condition[id].lower && value_at_id <= active_condition[id].upper) {
            counter++;
        }
    }
    return counter;
}

long calculate_ranged_working(
    std::vector<long>& ids_in_component,
    std::map<long, Bound>& active_condition,
    std::map<long, Expression>& id_to_exp
) {
    std::vector<Bound> bound_on_original;
    for (long id : ids_in_component) {
        Bound bound_on_target = active_condition[id];
        Expression exp = id_to_exp[id];

        if (exp.coeff > 0) {
            assert(exp.coeff == 1);
            bound_on_original.push_back(
                Bound{
                    .lower = (bound_on_target.lower - exp.constant) / exp.coeff,
                    .upper = (bound_on_target.upper - exp.constant) / exp.coeff,
                }
            );
        }
        else {
            assert(exp.coeff == -1);
            bound_on_original.push_back(
                Bound{
                    .lower = (bound_on_target.upper - exp.constant) / exp.coeff,
                    .upper = (bound_on_target.lower - exp.constant) / exp.coeff,
                }
            );
        }
    }

    std::vector<long> lower_bounds;
    std::vector<long> upper_bounds;

    for (Bound& bound : bound_on_original) {
        lower_bounds.push_back(bound.lower);
        upper_bounds.push_back(bound.upper);
    }

    std::sort(lower_bounds.begin(), lower_bounds.end());
    std::sort(upper_bounds.begin(), upper_bounds.end());

    int i = 0;
    int j = 0;
    int layers = 0;
    int max_layers = 0;
    while (i < lower_bounds.size() && j < upper_bounds.size()) {
        if (upper_bounds[j] < lower_bounds[i]) {
            layers--;
            j++;
        }
        else {
            layers++;
            i++;
            max_layers = std::max(max_layers, layers);
        }
    }
    return max_layers;
}

long calculate_most_working(
    std::map<long, Bound>& active_condition,
    std::map<long, std::vector<Equation>>& id_to_equ,
    std::map<long, Expression>& id_to_exp,
    std::map<long, long>& id_to_fixed_value,
    long id
) {
    std::vector<long> ids_in_component;
    std::deque<long> bfs;
    bfs.push_back(id);
    id_to_exp[id]=Expression{.coeff=1, .letter_id=id, .constant=0};

    while(!bfs.empty()) {
        long from_id = bfs.front();
        bfs.pop_front();
        ids_in_component.push_back(from_id);
        if (!expand(id_to_equ, id_to_exp, id_to_fixed_value, from_id, bfs)) {
            return -1;
        }
    }

    // Fixed Value Case
    if (id_to_fixed_value.count(id) > 0) {
        return calculate_fixed_valued_working(ids_in_component, active_condition, id_to_exp, id_to_fixed_value[id]);
    }
    
    // Range Case
    return calculate_ranged_working(ids_in_component, active_condition, id_to_exp);

}

void debug_output(
    std::map<long, std::vector<Equation>> id_to_equ,
    std::map<long, Expression> id_to_exp,
    std::map<long, long> id_to_fixed_value
) {
     for (auto& [id, equs] : id_to_equ) {
        std::cout <<id << std::endl;
        for (auto equ : equs) {
            std::cout << equ.this_id << " " << equ.other_id << " " << equ.sum << std::endl;
        }
    }

    for (auto& [id, exp] : id_to_exp) {
        std::cout <<"v["<< id << "]=" << exp.coeff<<"v["<<exp.letter_id<<"]+" << exp.constant << std::endl; 
    }

    for (auto& [id, v] : id_to_fixed_value) {
        std::cout <<"v["<< id << "]=" << v << std::endl; 
    }
}

void run_case() {
    long n, m;
    std::cin >> n >> m;
    std::map<long, Bound> active_condition;
    std::map<long, std::vector<Equation>> id_to_equ;
    for (long i = 1; i <= n; i++) {
        std::cin >> active_condition[i].lower;
    }
    for (long i = 1; i <= n; i++) {
        std::cin >> active_condition[i].upper;
    }

    for (long i = 0; i < m; i++) {
        long id1, id2, sum;
        std::cin >> id1 >> id2 >> sum;

        id_to_equ[id1].push_back(Equation{.this_id=id1, .other_id=id2, .sum=sum});
        if (id2 != id1) {
            id_to_equ[id2].push_back(Equation{.this_id=id2, .other_id=id1, .sum=sum});
        }
    }

    std::map<long, Expression> id_to_exp;
    std::map<long, long> id_to_fixed_value;
    long most_working = 0;
    for (long i = 1; i <=n; i++) {
        if (id_to_exp.count(i) > 0) {
            continue;
        }
        
        long most_working_in_component = calculate_most_working(active_condition, id_to_equ, id_to_exp, id_to_fixed_value, i);
        //debug_output(id_to_equ, id_to_exp, id_to_fixed_value);

        if (most_working_in_component == -1) {
            std::cout << -1 << std::endl;
            return;
        }
        most_working += most_working_in_component;
    }
    std::cout << most_working << std::endl;
}

int main() {
    long Q;
    std::cin >> Q;
    for (long i = 0; i < Q; i++) {
        run_case();
    }
}