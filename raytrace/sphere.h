#ifndef SPHERE_H
#define SPHERE_H
#include "icg_common.h"


class Sphere
{
private:
    vec3 _location = vec3(0,0,0);
    double _radius = 1;
    vec3 _eToc = vec3(0,0,0);
public:
    //constructor
    Sphere(int u ,int v, int w, double r, vec3 camera);
    //Sphere(int u ,int v, int w, double r);
    //destructor
    ~Sphere();

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

    //set eToc
    void setEToC(vec3 newEToC){
        _eToc = newEToC;
        return;
    }

    //get eToc
    vec3 getEToC(){
        return _eToc;
    }

//    string toString(){
//        string s = _location + " , " + _radius + " , " + _eToc + " , ";
//        return s;
//    }
};

#endif // SPHERE_H
