#ifndef PLANE_H
#define PLANE_H
#include "icg_common.h"
#include "shape.h"

class Plane: public Shape
{
    typedef cv::Vec3b Colour;
private:
    vec3 _location = vec3(0,0,0);
    vec3 _eToc = vec3(0,0,0);
    Colour _colour = Colour(0,0,0);
    vec3 _normal = vec3(0,0,0);
    vec3 _camera = vec3(0,0,0);
    double _refl = 0;
public:
    Plane(vec3 location, vec3 normal, vec3 camera, Colour colour, double refl);

    ~Plane();

    virtual vec3 getEToC() override;

    virtual double getRadius() override;

    virtual Colour getColour() override;

    virtual double intersection(vec3 ray) override;

    virtual vec3 getNormal(vec3 intersection) override;

    virtual double getRefl() override;

};

#endif // PLANE_H
