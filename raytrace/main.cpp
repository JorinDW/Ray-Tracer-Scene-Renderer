#include "icg_common.h"
#include <Eigen/Geometry>
#include "sphere.h"

#ifndef WITH_OPENCV
    #error OpenCV required for this exercise
#endif

typedef cv::Vec3b Colour;
Colour red() { return Colour(255, 0, 0); }
Colour white() { return Colour(255, 255, 255); }
Colour black() { return Colour(0, 0, 0); }

struct MyImage{
    /// Data (not private for convenience)
    int cols = 640;
    int rows = 480;
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
    Sphere s1 = Sphere(0,0,1,5);
    cout << "Sphere details: "<< s1.getLocation().transpose() << endl;
    cout << s1.getRadius() << endl;

    ///define camera location
    vec3 camera = vec3(0,0,-1);

    ///define the origin
    vec3 o = vec3(0,0,0);

    ///pixel iteration
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            ///create the pixel rays in 3d spaceß
            ///create the view rays based on the pixel ray
            ///determine if the view ray intersects with the sphere (for each shape, choose closest)
                ///if it doesn't make it black
                ///if it does
                    ///create ambient light color
                    ///create diffuse light
                    ///create specular lights
            vec3 d = vec3(1,1,0).normalized();
            ray3 r(o,d);
       }
    }
    //image.show();
    //image.save("output.png"); ///< Does not work on Windows!

    return EXIT_SUCCESS;
}
