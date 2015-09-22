#include "sphere.h"

Sphere::Sphere(int u, int v, int w, int r)
{
    cout << "Sphere()"<< endl;
    _location = vec3(u,v,w);
    _radius = r;
}

Sphere::~Sphere(){
    cout << "~Sphere()" << endl;
}

Sphere::Sphere(const Sphere &Sphere){
    cout << "Sphere(Sphere& )" << endl;
    this->_location = Sphere._location;
    this->_radius = Sphere._radius;
}

Sphere &Sphere::operator=(const Sphere &Sphere){
    cout << "Sphere::operator=" << endl;
    this->_location = Sphere._location;
    this->_radius = Sphere._radius;
    return *this;
}


