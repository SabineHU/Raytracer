#pragma once

#include "object.hh"

enum ObjectOperator : int {
    UNION = 1,
    INTERSECTION = 1 << 1,
    MINUS = 1 << 2,
    DIFFERENCE = 1 << 3
};

class CSG : public Object {
public:
    CSG() = delete;
    CSG(ObjectOperator, shared_object, shared_object);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

private:
    /* Attributes */
    ObjectOperator op;
    shared_object obj1;
    shared_object obj2;
};
