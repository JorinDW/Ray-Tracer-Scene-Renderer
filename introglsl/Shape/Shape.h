#ifndef SHAPE_H
#define SHAPE_H
#include "icg_common.h"

class Shape
{
public:
    Shape();
    virtual void draw() = 0;
    virtual void cleanup() = 0;
    virtual void init(std::vector<vec3> vpoint) = 0;
};

#endif // SHAPE_H
