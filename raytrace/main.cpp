#include "icg_common.h"
#include <Eigen/Geometry>
#include "sphere.h"
#include "shape.h"
#include "plane.h"
#include <cmath>
#include <vector>
#ifndef WITH_OPENCV
    #error OpenCV required for this exercise
#endif
using namespace std;

typedef cv::Vec3b Colour;
Colour red() { return Colour(0,0,255); }
Colour white() { return Colour(255,255,255); }
Colour black() { return Colour(0,0,0); }
Colour blue() { return Colour(255,0,0); }
Colour green() { return Colour(0,255,0); }
Colour yellow() { return Colour(0,255,255); }
Colour orange() { return Colour(0,140,255); }
struct MyImage{
    /// Data (not private for convenience)
    int cols = 500;
    int rows = 500;
    ///  Channel with [0..255] range image (aka uchar)
    cv::Mat image = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(255,255,255));

    Colour& operator()(int row, int col)
    {
        assert(row >= 0 && row < rows);
        assert(col >= 0 && col < cols);
        return image.at<cv::Vec3b>(cv::Point(col, row));
    }

    /// Displays the image and pauses program execution (until key pressed)
    void show(){
        /// Display the image
        cv::imshow("image", image);
        cv::waitKey(0);
    }

    /// Use files with "*.png" extension
    void save(const std::string& filename){
        cv::imwrite(filename, image);
    }
};


int main(int, char**){
    /// Rays and vectors represented with Eigen
    typedef Eigen::Vector3f vec3;
    typedef Eigen::ParametrizedLine<float, 3> ray3;
    
    MyImage image;
    
    ///define camera location (change this and you must change d)
    vec3 camera = vec3(10,0,0);

    ///define the origin
    vec3 o = vec3(0,0,0);

    ///define the light source
    vec3 lightSource = vec3(-25, 0, 2);

    ///create spheres
    vector<Shape*> objects;
    Sphere s1 = Sphere(vec3(-25,12,0),4,camera,red(),0.4);
    objects.push_back(&s1);
    Sphere s2 = Sphere(vec3(-20,-10,0),4,camera,orange(),0.4);
    objects.push_back(&s2);
    Sphere s3 = Sphere(vec3(-15, 5, 0),1,camera,yellow(),0.4);
    objects.push_back(&s3);
    Plane p1  = Plane(vec3(-1,1,-4),vec3(0,0,-1),camera, blue(),0.3);
    objects.push_back(&p1);
    Plane p2 = Plane(vec3(-1,1,4), vec3(0,0,1),camera, green(),0.3);
    objects.push_back((&p2));
//    Plane p3  = Plane(vec3(0,6,0),vec3(0,1,0),camera, black());
//    objects.push_back(&p3);
//    Plane p4 = Plane(vec3(-999,0,0), vec3(1,0,0), camera, beige());
//    objects.push_back((&p4));
    //halfway vector
    //vec3 halfway = ((rayDirection + lightVector)/((rayDirection + lightVector).normalized()));
    //create the light intensity cl
    double lightIntensity = 1.0;
    //create control value of light cp
    double lightControl = 1.0;
    //create the specular exponent p
    double specularExp = 1.0;
    //create ambient intensity
    double ambientInt = 0.35;
    //create light colour
    Colour lightColour = Colour(255,255,255);

    ///pixel iteration
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            ///****Create the Pixel Rays in 3D space****
            ///Model of Pixels from Graphical World:
            ///The image plane in the 3D space is like a photograph in the real world, it has no segmentation, only a perfect representation of
            /// the world it comes from. When we want to view the rendered world, we have to take this image plane and segment it into
            /// pixels that our screen can understand. So, this means that the size of the image, and the number of pixels are related but not
            /// equal.
            /// We use the following formula to divide up the image into pixels in both vertical and horizontal directions
            ///
            ///     u = l + (r-l)(i+0.5)/nx
            ///     v = b + (t-b)(j+0.5)/ny
            /// , where:
            /// - (u,v) are the coordinates of the pixel's position on the image plane w.r.t the origin,
            /// - (l,r) and (b,t) are the distances from the origin to the left, right, bottom, and top of the image plane (this can be replaced
            ///     with just a length and width),
            /// - (i,j) are the iterators for which pixel you are on
            /// - (0.5) ensures that you place the pixel into the center of the space on the image plane it belongs to
            /// - and (nx,ny) are the number of pixels horizontally and vertically respectively.
            ///
            /// I will be using:
            /// - (l,r) and (b,t) as (-a,a) and (-a,a) so that when my viewing point is located at (0,0,-1) I will have 90 degrees
            /// of view horizontally and vertically (the zoom of the image will be decided by what a is and the distance of the camera to the
            /// image plane),
            /// - and (nx,ny) as equal to get a square view point, and so that there aren't any scaling issues between length and width
            /// of the image plane and the number of pixels in the view. These are defined as image.col, image.row.
            //left side of image plane
            int l = -5;
            //right side of image plane
            int r = 5;
            //bottom of the image plane
            int b = -5;
            //top of the image plane
            int t = 5;
            //pixel horizontal iterator (because adding 0.5 to col directly causes an infinit loop)
            double i = col;
            //pixel vertical iterator (because adding 0.5 to row directly causes an infinit loop)
            double j = row;
            //horizontal coordinates of pixel on image plane
            double u = l + ((r - l)*(i + 0.5))/image.cols;
            //vertical coordinates of pixel on image plane
            double v = b + ((r - l)*(j + 0.5))/image.rows;
            ///We now have the corrdinates of the pixel's position on the image plane w.r.t the origin (since we placed the origin at the center
            /// of the image plane.)


            ///****Create the View Ray Direction from (u,v)****
            /// Now we are determining the direction of the view ray from the coordinates that we determined previously
            /// The ray direction can be determined using the following equation
            ///
            ///     -dW + uU + vV
            ///
            /// , where:
            /// - captials are vectors (and in this case they are the 3 directional vectors),
            /// - d is the distance between the camera and the image plane (negative so that we are pointing out of the image back towards the scene)
            /// - and (u,v) are the horizontal and vertical coordinate that we just determined
            //distance to the image plane (from the -1 of the camera being -1 behind the image plane)
            int d = -10;
            //creating the ray direction vector
            vec3 rayDirection = vec3 (d,u,v);
            //normalize the vector
            rayDirection.normalized();
            ///note: The origin of this rayDirection vector is the view point denoted by the camera variable. We have this set to (-1,0,0)
            //create the ray from the pixel position and the location of the point
            ray3 pixelRay = ray3(camera,rayDirection);

            ///****Intersections of the rayDirection and each Shape in the Scene****
            ///We now need to determine what kinds of intersection our ray has. We can do this using the following formula:
            ///
            ///     t = (-d.(e-c)+/-((d.(e-c))^2 - (d.d)((e-c).(e-c)-R^2))^0.5)/2
            /// where,
            /// - d is the rayDirection vector,
            /// - e is the camera position vector,
            /// - c is the sphere position vector,
            /// - and R is the radius of the sphere.
            ///
            /// But, there is a condition that we can check before we do this whole computation. The determinat of this
            /// quadratic equation can tell you the nature of the intersection. There are 3 possibilities:
            /// - one: we miss the sphere and the determinat is negative
            /// - two: we graze the sphere and the determinant is zero
            /// - three: we pierce the sphere and the determinant is positive
            /// Because we would like for their to be more than one sphere in the object, and we need to check for the closest intersection
            /// that occurs for a given ray, we will have to iterate over the objects individually and see if an intersection occurs.
            /// note: The version above between the starred comments worked for a single object and didn't consider what what close and far away.
            //closest t
            double closest = 9999;
            Shape* hitShape;
            for(auto &i : objects){
                double test  = i->intersection(rayDirection);
                if(test < 0){
                    //do nothing
                }else if(test < closest){
                    //image(row,col) = i->getColour();
                    closest = test;
                    hitShape = i;
                }
            }


            ///****Ambient,Diffuse and Specular Lighting****
            /// Here we now need to create a system for determining the color of pixels based on the obejcts they contain.
            /// Doing this we will combine three different types of lighting, ambient, diffuse and specular.
            /// We will split this process into ambient + diffuse, and seperately + specular.
            /// The following equation show us how to calculate ambient and diffuse together
            ///
            ///     c = cr*(ca + cl*max(0,N.L)) + cl*cp*(H.N)^p
            /// where,
            /// c is the color that we show for the paritcualr pixel,
            /// cr is the diffuse reflectance of the surface which determines how reflective the surface is,
            /// cl is the intensity of the light,
            /// N is the normal of the surface,
            /// L is the vector of the light,
            /// cp is a control value for light,
            /// H is the unit vector halfway between the light and view vectors,
            /// and p is an exponent that determines the size of the specular highlights
            if(hitShape){
                //cout<<"Here"<<endl;
                //generates the point that the ray intersected the sphere or plane.
                //used to determine the normal.
                vec3 intersectionPoint = pixelRay.pointAt(closest);
                //use hitShape.getLocation to get the second point to create the normal.
                vec3 normal = (hitShape->getNormal(intersectionPoint));
                //now generate the light vector
                vec3 lightVector = (intersectionPoint - lightSource).normalized();
                //calculate the light at the point
                //Colour pixelColour = hitShape->getRefl()*(ambientInt*hitShape->getColour() + lightColour*lightIntensity*std::max((float)0.0,normal.dot(lightVector)));
                //the diffuse light
                Colour diffuseLight = Colour(150,150,150);
                //do precalculations
                double specular = (normal*(normal.dot(lightVector)) - lightVector).dot(rayDirection);
                Colour pixelColour = hitShape->getColour()*hitShape->getRefl() + 1.0*(lightVector.dot(normal))*(diffuseLight) + 1.0*pow((double)specular,20)*diffuseLight;
                //set the pixel colour
                image(row,col) = pixelColour;
            } else {
                image(row,col) = yellow();
            }

            //vec3 d = vec3(1,1,0).normalized();
            //ray3 r(o,d);
       }
    }
    cout<< "Done!" << endl;
    image.show();
    //image.save("output.png"); ///< Does not work on Windows!

    return EXIT_SUCCESS;
}

