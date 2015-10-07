#include "plane.h"
Plane::Plane(vec3 location, vec3 normal, vec3 camera, cv::Vec3f colour, double refl)
{
    cout << "Plane()"<< endl;
    _location = location;
    _normal = normal;
    _camera = camera;
    _eToc = _camera - location;
    _colour = colour;
    _refl = refl;
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

cv::Vec3f Plane::getColour(){
    return _colour;
}

vec3 Plane::getNormal(vec3 intersection){
    return _normal;
}

double Plane::getRefl(){
    return _refl;
}

double Plane::intersection(vec3 ray){
    double test = -1;
    double denominator = ray.dot(_normal);
    double numerator = (_camera - _location).dot(_normal);
    if(denominator == 0 || numerator == 0){
        return -3;
    } else {
        test = - numerator/denominator;
        return test;
    }
    //cout<<"what?"<<endl;
}
