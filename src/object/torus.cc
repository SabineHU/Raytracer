#include "torus.hh"
#include "unique.hh"
#include "vector3_op.hh"

Torus::Torus()
    : position(Vect())
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Torus::Torus(const Point3& p)
    : position(p)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Torus::Torus(const Point3& p, shared_texture t)
    : Object(t), position(p)
{}

Torus::Torus(const Point3& p, const Color& c)
    : Object(std::make_shared<Unique>(c)), position(p)
{}

Vect Torus::get_normal_at(const Vect& point) const {
    auto x = Vect(1, 1, -1) * position.x * position.x;
    auto y = point.square_length() - position.y * position.y;
    return (point * (x * -1 + y)).normalize();
}

bool Torus::find_intersection(const Ray& ray, double& t_min, double& t_max) {
    double po = 1.0;
    double Ra2 = position.x*position.x;
    double ra2 = position.y*position.y;
    double m = vector::dot(ray.origin,ray.origin);
    double n = vector::dot(ray.origin,ray.direction);
    double k = (m + Ra2 - ra2)/2.0;
    double k3 = n;
    double k2 = n*n - Ra2*(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y) + k;
    double k1 = n*k - Ra2*(ray.direction.x * ray.origin.x + ray.direction.y * ray.origin.y);
    double k0 = k*k - Ra2*(ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y);

    if( std::abs(k3*(k3*k3-k2)+k1) < 0.01 )
    {
        po = -1.0;
        double tmp=k1; k1=k3; k3=tmp;
        k0 = 1.0/k0;
        k1 = k1*k0;
        k2 = k2*k0;
        k3 = k3*k0;
    }

    double c2 = k2*2.0 - 3.0*k3*k3;
    double c1 = k3*(k3*k3-k2)+k1;
    double c0 = k3*(k3*(c2+2.0*k2)-8.0*k1)+4.0*k0;
    c2 /= 3.0;
    c1 *= 2.0;
    c0 /= 3.0;
    double Q = c2*c2 + c0;
    double R = c2*c2*c2 - 3.0*c2*c0 + c1*c1;
    double h = R*R - Q*Q*Q;

    if( h>=0.0 )  
    {
        h = sqrt(h);
        double v = (R + h > 0 ? 1 : -1) *pow(abs(R+h),1.0/3.0); // cube root
        double u = (R - h > 0 ? 1 : -1) *pow(abs(R-h),1.0/3.0); // cube root
        Vect s;
        s.x = (v+u)+4.0*c2;
        s.y = (v-u)*sqrt(3.0);
        double y = sqrt(0.5*(s.magnitude() +s.x));
        double x = 0.5*s.y/y;
        double r = 2.0*c1/(x*x+y*y);
        double t1 =  x - r - k3; t1 = (po<0.0)?2.0/t1:t1;
        double t2 = -x - r - k3; t2 = (po<0.0)?2.0/t2:t2;
        double t = 1e20;
        if( t1> t_min) t=t1;
        if( t2> t_min) t=std::min(t,t2);

        if (t <= t_min ||  t >= t_max)
            return false;
        t_max = t;
        return true;
    }

    double sQ = sqrt(Q);
    double w = sQ*cos( acos(-R/(sQ*Q)) / 3.0 );
    double d2 = -(w+c2); if( d2<0.0 ) return false;
    double d1 = sqrt(d2);
    double h1 = sqrt(w - 2.0*c2 + c1/d1);
    double h2 = sqrt(w - 2.0*c2 - c1/d1);
    double t1 = -d1 - h1 - k3; t1 = (po<0.0)?2.0/t1:t1;
    double t2 = -d1 + h1 - k3; t2 = (po<0.0)?2.0/t2:t2;
    double t3 =  d1 - h2 - k3; t3 = (po<0.0)?2.0/t3:t3;
    double t4 =  d1 + h2 - k3; t4 = (po<0.0)?2.0/t4:t4;
    double t = 1e20;
    if( t1>t_min ) t=t1;
    if( t2>t_min ) t=std::min(t,t2);
    if( t3>t_min ) t=std::min(t,t3);
    if( t4>t_min ) t=std::min(t,t4);

    if (t <= t_min || t >= t_max)
        return false;
    t_max = t;
    return true;
}

int Torus::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
