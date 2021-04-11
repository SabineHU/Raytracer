#pragma once

struct ImageSquare {
    ImageSquare(double a, double b, double c, double d)
        : i_min(a), j_min(b), i_max(c), j_max(d)
    {}

    double i_min;
    double j_min;

    double i_max;
    double j_max;
};
