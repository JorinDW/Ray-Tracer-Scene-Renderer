#ifndef SHAPE_H
#define SHAPE_H
#include "icg_common.h"

class Shape
{
    typedef cv::Vec3b Colour;
public:
    Shape();
    virtual vec3 getEToC() = 0;
    virtual double getRadius() = 0;
    virtual Colour getColour() = 0;
    virtual double intersection(vec3 ray) = 0;
    virtual vec3 getNormal(vec3 intersection) = 0;
    virtual double getRefl() = 0;
};

#endif // SHAPE_H
