#include "plane.h"
typedef cv::Vec3b Colour;
Plane::Plane(vec3 location, vec3 normal, vec3 camera, Colour colour)
{
    _location = location;
    _normal = normal;
    _camera = camera;
    _eToc = _camera - location;
    _colour = colour;
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
    double test = -1;
    double denominator = ray.dot(_normal);
    double numerator = (_camera - _location).dot(_normal);
    if(denominator == 0 || numerator == 0){
        return test;
    } else {
        test = - numerator/denominator;
        return test;
    }
    cout<<"what?"<<endl;
}