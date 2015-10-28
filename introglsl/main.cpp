#include "icg_common.h"

#include "Bat/Bat.h"
#include "Quad/Quad.h"

Bat bat;
Quad background;

void init(){
    /// sets background color
    glClearColor(/*gray*/ .937,.937,.937, /*solid*/1.0 );
    /// create a quad for the background image to be on
    /// pass in the size of the desired quad (full screen)
    background.init();
    /// create the bats that will be flying around the scene
    bat.init();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    bat.draw();
    background.draw();
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
