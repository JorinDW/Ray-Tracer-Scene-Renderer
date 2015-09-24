#include "icg_common.h"
#include <Eigen/Geometry>
#include "sphere.h"
#include "cmath"
#ifndef WITH_OPENCV
    #error OpenCV required for this exercise
#endif
using namespace std;

typedef cv::Vec3b Colour;
Colour red() { return Colour(255, 0, 0); }
Colour white() { return Colour(255, 255, 255); }
Colour black() { return Colour(0, 0, 0); }

struct MyImage{
    /// Data (not private for convenience)
    int cols = 200;
    int rows = 200;
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
    
    ///create spheres
    Sphere s1 = Sphere(1,0,0,1.75);
    cout << "Sphere details: "<< s1.getLocation().transpose() << endl;
    cout << s1.getRadius() << endl;

    ///define camera location
    vec3 camera = vec3(-1,0,0);

    ///define the origin
    vec3 o = vec3(0,0,0);

    //calculate e - c a single time since it is used many times
    vec3 eToc = camera - s1.getLocation();

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
            int l = -2;
            //right side of image plane
            int r = 2;
            //bottom of the image plane
            int b = -2;
            //top of the image plane
            int t = 2;
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
            if(row < 1){
                cout<< "u : " << u << ",v : " << v << endl;
            }

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
            int d = 1;
            //creating the ray direction vector
            vec3 rayDirection = vec3 (-d,u,v);
            //normalize the vector
            rayDirection.normalized();
            //create the ray from the camera position and the location of the point
            ray3 pixelRay = ray3(camera,rayDirection);
            ///note: The origin of this rayDirection vector is the view point denoted by the camera variable. We have this set to (0,0,-1)
            //cout << "\nNormalize rayDirection: " << rayDirection.transpose() << endl;
            //cout << "Pixel ray: " << pixelRay << endl;


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
            // we calculate the determinant
            double determinant = pow(((double)rayDirection.dot(eToc)),2) - (rayDirection.dot(rayDirection))*(eToc.dot(eToc) - pow((double)s1.getRadius(),2));
            cout << "Determinant: " << determinant << endl;
            if(determinant < 0){
                image(row, col) = white();
            }else{
                image(row, col) = black();
            }



            ///determine if the view ray intersects with the sphere (for each shape, choose closest)
                ///if it doesn't make it black
                ///if it does
                    ///create ambient light color
                    ///create diffuse light
                    ///create specular lights
            //vec3 d = vec3(1,1,0).normalized();
            //ray3 r(o,d);
       }
    }
    cout<< "Done!" << endl;
    image.show();
    //image.save("output.png"); ///< Does not work on Windows!

    return EXIT_SUCCESS;
}
