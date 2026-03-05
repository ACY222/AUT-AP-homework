#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1 {

template <typename T, typename Callable>
T gradient_descent(T init_idx, T step_size, Callable func) {
    T curr = init_idx;
    T left{curr - step_size}, right{curr + step_size};

    while (func(curr) > func(left) or func(curr) > func(right)) {
        curr = (func(right) < func(left)) ? right : left;
        left = curr - step_size;
        right = curr + step_size;
    }

    return curr;
}

template <typename T>
T gradient_descent(T init_idx, T step_size, double (*func)(double)) {
    return gradient_descent<T, double (*)(double)>(init_idx, step_size, func);
}

template <typename T, typename Callable>
T gradient_descent(T init_idx, T step_size) {
    Callable func;
    return gradient_descent(init_idx, step_size, func);
}

} // namespace q1

#endif // Q1_H
