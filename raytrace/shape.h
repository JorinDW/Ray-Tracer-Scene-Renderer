#ifndef SHAPE_H
#define SHAPE_H
#include "icg_common.h"

class Shape
{
public:
    Shape();
    virtual vec3 getEToC() = 0;
    virtual double getRadius() = 0;
    virtual cv::Vec3f getColour() = 0;
    virtual double intersection(vec3 ray) = 0;
    virtual vec3 getNormal(vec3 intersection) = 0;
    virtual double getRefl() = 0;
};

#endif // SHAPE_H
