#include "icg_common.h"
#include "Bat/Bat.h"
#include "Quad/Quad.h"

//typedef Eigen::Transform<float,3,Eigen::Affine> Transform;
Bat bat;

void init(){
    /// sets background color
    glClearColor(/*gray*/ .937,.937,.937, /*solid*/1.0 );

    /// create the bats that will be flying around the scene
    bat.init();
}

void display(){
    mat4 bat_M = mat4::Identity();

    glClear(GL_COLOR_BUFFER_BIT);

    /// Perform whole bat transformations here
    float time = glfwGetTime();

    ///Perform whole bat transformations using bat_M to track changes
    float scale_t = 0.2*abs(std::sin(time));
    bat_M *= Eigen::Affine3f(Eigen::Translation3f(std::sin(time), 0.0 + scale_t, 0.0)).matrix();
    bat_M *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.02 +scale_t, 0.02 +scale_t, 1.0)).matrix();

    bat.draw(bat_M);
}

int main(int, char**){
    glfwInitWindowSize(1000, 1000);
    glfwCreateWindow("Scary Scene");
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();
    bat.cleanup();
    return EXIT_SUCCESS;
}
