#include "icg_common.h"
#include "Bat/Bat.h"
#include "Quad/Quad.h"

//typedef Eigen::Transform<float,3,Eigen::Affine> Transform;
Bat bat;
Quad background;

void init(){
    /// sets background color
    glClearColor(/*gray*/ .937,.937,.937, /*solid*/1.0 );
    /// create a quad for the background image to be on
    /// pass in the size of the desired quad (full screen)
//    const GLfloat backPoint[] = { /*V1*/ -1.0f, -1.0f, 0.0f,
//                               /*V2*/ +1.0f, -1.0f, 0.0f,
//                               /*V3*/ -1.0f, +1.0f, 0.0f,
//                               /*V4*/ +1.0f, +1.0f, 0.0f };
//    background.init(backPoint);
    /// create the bats that will be flying around the scene
    bat.init();
}

void display(){
    mat4 bat_M = mat4::Identity();
    glClear(GL_COLOR_BUFFER_BIT);
    float time = glfwGetTime();

    ///Perform bat transformations using bat_M to track changes
    float freq = M_PI*time*1;

    //bat_M *= Eigen::Affine3f(Eigen::Translation3f(0.0, 0.0, 0.0)).matrix();
//    Transform sun_M = Transform::Identity();
//    sun_M *= Eigen::Translation3f(0.2, 0.0, 0.0);
//    sun_M *= Eigen::AngleAxisf(-freq/SUN_ROT_PERIOD, Eigen::Vector3f::UnitZ());
//    //scale_t: make the sun become bigger and smaller over the time!
    float scale_t = 0.01*std::sin(freq);
    bat_M *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.2 +scale_t, 0.2 +scale_t, 1.0)).matrix();


    bat.draw(bat_M);
    //background.draw();
}

int main(int, char**){
    glfwInitWindowSize(700, 700);
    glfwCreateWindow("Scary Scene");
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();
    bat.cleanup();
    background.cleanup();
    return EXIT_SUCCESS;
}
