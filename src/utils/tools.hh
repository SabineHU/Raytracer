#pragma once

namespace tools {

template <typename T, typename U>
void get_max(T& x, T& y, U& x2, U& y2)
{
    if (x > y) {
        y = x;
        y2 = x2;
    }
}

template <typename T, typename U>
void get_min(T& x, T& y, U& x2, U& y2)
{
    if (x < y) {
        y = x;
        y2 = x2;
    }
}

template <typename T, typename U>
void modify_if_negative(T& t1, T& t2, U& u1, U& u2) {
    /* Results are stored in t1 and u1 */
    if (t1 < 0) {
        t1 = t2;
        u1 = u2;
    }
}

template <typename T, typename U>
void swap_min(T& t1, T& t2, U& u1, U& u2) {
    if (t1 < t2) {
        std::swap(t1, t2);
        u1 *= -1;
        u2 *= -1;
    }
}

}
