#pragma once
#include "icg_common.h"
#include "../Quad/Quad.h"
#include "../Triangle/Triangle.h"
#include "../Shape/Shape.h"

class Bat{
private:
    Quad batHead;
    Quad batBody;
    Triangle leftWing;
    Triangle rightWing;
    vector<Shape*> bodyParts;
public:
    void init(){
        /// Initialize the body parts with the generic bat coords.
        batHead.init();
        batBody.init();
        leftWing.init();
        rightWing.init();

        /// Generate a generic bat by pushing Quads and Triangles as Shapes into a vector
        bodyParts.push_back(&batHead);
        bodyParts.push_back(&batBody);
        bodyParts.push_back(&leftWing);
        bodyParts.push_back(&rightWing);
//        ///go through each shape and initialize it
//        for(auto &k: bodyParts){
//            k->init();
//        }
    }
       
    void cleanup(){
        ///Call the Quad and Triangle cleanup functions
        for(auto &k : bodyParts){
            k->cleanup();
        }
    }
    
    void draw(){
        ///Call the Quad and Triangle Draw functions
        for(auto &k : bodyParts){
            k->draw();
        }
    }
};
