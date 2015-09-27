#include "plane.h"
typedef cv::Vec3b Colour;
Plane::Plane(vec3 location, vec3 normal, vec3 camera)
{
    _location = location;
    _normal = normal;
    _camera = camera;
}

Plane::~Plane(){
    cout << "~Plane()" << endl;
}
vec3 Plane::getEToC(){
    return _eToc;
}

double Plane::getRadius(){
    double d = 0.0;
    return d;
}

Colour Plane::getColour(){
    return _colour;
}

double Plane::intersection(vec3 ray){
    double l = 0.0;
    return l;
}
