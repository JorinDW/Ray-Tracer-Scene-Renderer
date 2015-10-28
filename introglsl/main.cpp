#include "icg_common.h"
#include "Bat/Bat.h"
#include "Quad/Quad.h"

//typedef Eigen::Transform<float,3,Eigen::Affine> Transform;
Bat bat;
Bat bat2;
Bat bat3;
Bat bat4;
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
    bat2.init();
    bat3.init();
    bat4.init();
}

void display(){
    mat4 bat_M = mat4::Identity();
    mat4 bat_M2 = mat4::Identity();
    mat4 bat_M3 = mat4::Identity();
    mat4 bat_M4 = mat4::Identity();
    glClear(GL_COLOR_BUFFER_BIT);

    /// Perform whole bat transformations here
    float time = glfwGetTime();

    ///Perform whole bat transformations using bat_M to track changes
    //float freq = M_PI*time*10;
    //bat_M *= Eigen::Affine3f(Eigen::Translation3f(0.0, 0.0, 0.0)).matrix();
    //Transform sun_M = Transform::Identity();
    //sun_M *= Eigen::Translation3f(0.2, 0.0, 0.0);
    //sun_M *= Eigen::AngleAxisf(-freq/SUN_ROT_PERIOD, Eigen::Vector3f::UnitZ());
    //scale_t: make the sun become bigger and smaller over the time!
    float scale_t = 0.2*abs(std::sin(time));
    bat_M *= Eigen::Affine3f(Eigen::Translation3f(std::sin(time), 0.0 + scale_t, 0.0)).matrix();
    bat_M *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.02 +scale_t, 0.02 +scale_t, 1.0)).matrix();


    bat_M2 *= Eigen::Affine3f(Eigen::Translation3f(std::sin(time),std::sin(time), 0.0)).matrix();
    bat_M2 *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.01 +0.1*scale_t, 0.01 +scale_t, 1.0)).matrix();

    bat_M3 *= Eigen::Affine3f(Eigen::Translation3f(std::sin(time),0.5*std::sin(std::cos(time)), 0.0)).matrix();
    bat_M3 *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.001 +scale_t*7, 0.01 +0.02*scale_t, 1.0)).matrix();

    bat_M4 *= Eigen::Affine3f(Eigen::Translation3f(abs(std::cos(time*0.1)),std::sin(time), 0.0)).matrix();
    bat_M4 *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.01 +scale_t, 0.01 +scale_t*5, 1.0)).matrix();

    bat.draw(bat_M);
    bat2.draw(bat_M2);
    bat3.draw(bat_M3);
    bat4.draw(bat_M4);
    //background.draw();
}

int main(int, char**){
    glfwInitWindowSize(1000, 1000);
    glfwCreateWindow("Scary Scene");
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();
    bat.cleanup();
    background.cleanup();
    return EXIT_SUCCESS;
}
