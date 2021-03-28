#include "noise.hh"
#include "random_color.hh"
#include "vector3_op.hh"

static void permute(int* p, int n) {
    for (int i = n-1; i > 0; i--) {
        int target = r_random::random_int(0, i);
        std::swap(p[i], p[target]);
    }
}

Noise::Noise() {
    for (int i = 0; i < count; ++i)
        ranvec[i] = r_random::random_vector(-1, 1).normalize();

    for (int i = 0; i < count; ++i) {
        perm_x[i] = i;
        perm_y[i] = i;
        perm_z[i] = i;
    }

    permute(perm_x, count);
    permute(perm_y, count);
    permute(perm_z, count);
}

static double perlin_interp(Vect c[2][2][2], double u, double v, double w) {
    auto uu = u*u*(3-2*u);
    auto vv = v*v*(3-2*v);
    auto ww = w*w*(3-2*w);
    auto accum = 0.0;

    for (int i=0; i < 2; i++)
        for (int j=0; j < 2; j++)
            for (int k=0; k < 2; k++) {
                Vect weight_v(u-i, v-j, w-k);
                accum += (i*uu + (1-i)*(1-uu))
                    * (j*vv + (1-j)*(1-vv))
                    * (k*ww + (1-k)*(1-ww))
                    * vector::dot(c[i][j][k], weight_v);
            }

    return accum;
}

double Noise::noise(const Point3& point) const {

    auto u = point.x - std::floor(point.x);
    auto v = point.y - std::floor(point.y);
    auto w = point.z - std::floor(point.z);

    auto i = static_cast<int>(floor(point.x));
    auto j = static_cast<int>(floor(point.y));
    auto k = static_cast<int>(floor(point.z));
    Vect c[2][2][2];

    for (int di=0; di < 2; di++)
        for (int dj=0; dj < 2; dj++)
            for (int dk=0; dk < 2; dk++)
                c[di][dj][dk] = ranvec[
                    perm_x[(i+di) & 255] ^
                        perm_y[(j+dj) & 255] ^
                        perm_z[(k+dk) & 255]
                ];

    return perlin_interp(c, u, v, w);
}

double Noise::turb(const Point3& p, int depth) const {
    auto accum = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for (int i = 0; i < depth; i++) {
        accum += weight*noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}
