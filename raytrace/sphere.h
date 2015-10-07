#ifndef SPHERE_H
#define SPHERE_H
#include "icg_common.h"
#include <Eigen/Geometry>
#include "shape.h"
class Sphere: public Shape
{
private:
    vec3 _location = vec3(0,0,0);
    double _radius = 1;
    vec3 _eToc = vec3(0,0,0);
    cv::Vec3f _colour;
    vec3 _ray = vec3(0,0,0);
    double _refl = 0;
public:
    //constructor
    Sphere(vec3 location, double r, vec3 camera, cv::Vec3f color, double refl);
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

    virtual cv::Vec3f getColour() override;

    virtual double intersection(vec3 ray, vec3 origin) override;

    virtual vec3 getNormal(vec3 intersection) override;

    virtual double getRefl() override;

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
    void setColour(cv::Vec3f colour){
        _colour = colour;
        return;
    }


};

#endif // SPHERE_H
