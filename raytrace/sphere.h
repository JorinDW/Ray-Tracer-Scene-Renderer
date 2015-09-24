#ifndef SPHERE_H
#define SPHERE_H
#include "icg_common.h"


class Sphere
{
private:
    vec3 _location = vec3(0,0,0);
    double _radius = 1;
public:
    //constructor
    Sphere(int u ,int v, int w, double r);

    //destructor
    ~Sphere();

    //copy constructor
    Sphere(const Sphere& sphere);

    //assignment operator
    Sphere& operator = (const Sphere& sphere);

    //set location
    void setLocation(vec3 newLocation){
        _location = newLocation;
        return;
    }

    //get location
    vec3 getLocation(){
        return _location;
    }

    //set radius
    void setRadius(int newSize){
        _radius = newSize;
        return;
    }

    //get radius
    double getRadius(){
        return _radius;
    }
};

#endif // SPHERE_H
