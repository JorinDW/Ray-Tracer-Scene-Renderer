#ifndef SPHERE_H
#define SPHERE_H
#include "icg_common.h"
#include <Eigen/Geometry>
#include "shape.h"
class Sphere: public Shape
{
    typedef cv::Vec3b Colour;
private:
    vec3 _location = vec3(0,0,0);
    double _radius = 1;
    vec3 _eToc = vec3(0,0,0);
    Colour _colour = Colour(0,0,0);
    vec3 _ray = vec3(0,0,0);
public:
    //constructor
    Sphere(vec3 location, double r, vec3 camera, Colour color);
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
    virtual vec3 getEToC() override;

    virtual double getRadius() override;

    virtual Colour getColour() override;

    virtual double intersection(vec3 ray) override;
    //get location
    vec3 getLocation(){
        return _location;
    }

    //set radius
    void setRadius(int newSize){
        _radius = newSize;
        return;
    }

    //set eToc
    void setEToC(vec3 newEToC){
        _eToc = newEToC;
        return;
    }


    //set colour
    void setColour(Colour colour){
        _colour = colour;
        return;
    }


};

#endif // SPHERE_H
