#ifndef PLANE_H
#define PLANE_H
#include "icg_common.h"
#include "shape.h"

class Plane: public Shape
{
private:
    vec3 _location = vec3(0,0,0);
    vec3 _eToc = vec3(0,0,0);
    cv::Vec3f _colour = cv::Vec3f(0,0,0);
    vec3 _normal = vec3(0,0,0);
    vec3 _camera = vec3(0,0,0);
    double _refl = 0;
public:
    Plane(vec3 location, vec3 normal, vec3 camera, cv::Vec3f colour, double refl);

    ~Plane();

    virtual vec3 getEToC() override;

    virtual double getRadius() override;

    virtual cv::Vec3f getColour() override;

    virtual double intersection(vec3 ray, vec3 origin) override;

    virtual vec3 getNormal(vec3 intersection) override;

    virtual double getRefl() override;

};

#endif // PLANE_H
