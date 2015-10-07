#include "icg_common.h"
#include <Eigen/Geometry>
#include "sphere.h"
#include "shape.h"
#include "plane.h"
#include <cmath>
#include <vector>

Sphere::Sphere(vec3 location, double radius, vec3 camera, cv::Vec3f colour, double refl)
//Sphere::Sphere(int u, int v, int w, double r)
{
    cout << "Sphere()"<< endl;
    _location = location;
    _radius = radius;
    _eToc = camera - _location;
    _colour = colour;
    _refl = refl;
    //cout << _eToc << endl;
}

Sphere::~Sphere(){
    cout << "~Sphere()" << endl;
}


Sphere &Sphere::operator=(const Sphere &Sphere){
    cout << "Sphere::operator=" << endl;
    this->_location = Sphere._location;
    this->_radius = Sphere._radius;
    return *this;
}

//get radius
double Sphere::getRadius(){
    return _radius;
}

//get eToc
vec3 Sphere::getEToC(){
    return _eToc;
}

//get colour
cv::Vec3f Sphere::getColour(){
    return _colour;
}

//get normal
vec3 Sphere::getNormal(vec3 intersection){
    return intersection - _location;
}

double Sphere::getRefl(){
    return _refl;
}

///takes in the ray from the pixel and checks if it is negative
///if not, then checks what the determinant is for the intersection
/// if 0, tangent intersection has occured.
/// if > 0, then there is a double intersection with the sphere.
double Sphere::intersection(vec3 ray){
    //the sphere is behind the camera
    if(_eToc(0) < 0){
        return -1;
    }
    double determinant = pow(((double)ray.dot(_eToc)),2) - (ray.dot(ray))*(_eToc.dot(_eToc) - pow((double)_radius,2));
    //if the determinant missed, then do nothing
    if(determinant < 0){
        return -2; //
    }else if(determinant == 0){ //tangent connection
        return ((-ray.dot(_eToc))/(ray.dot(ray)));
    }
    else{ //pierced the sphere
        double t1 = (ray.dot(_eToc) + sqrt(determinant))/ray.dot(ray);
        double t2 = abs((ray.dot(_eToc) - sqrt(determinant))/ray.dot(ray));
        return abs(min(t1,t2));
        //
    }
}
