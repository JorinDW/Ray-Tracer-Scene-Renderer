#include "sphere.h"

Sphere::Sphere(int u, int v, int w, double r, vec3 camera)
//Sphere::Sphere(int u, int v, int w, double r)
{
    cout << "Sphere()"<< endl;
    _location = vec3(u,v,w);
    _radius = r;
    _eToc = camera - _location;
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
