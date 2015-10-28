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
        ///
        std::vector<vec3> bodyPoints;
        bodyPoints.push_back(vec3(/*V1*/ -1.0f, 1.0f, 0.0f));
        bodyPoints.push_back(vec3(/*V2*/ 1.0f, 1.0f, 0.0f));
        bodyPoints.push_back(vec3(/*V3*/ -0.7f, -2.0f, 0.0f));
        bodyPoints.push_back(vec3(/*V4*/ 0.7f, -2.0f, 0.0f));

        std::vector<vec3> headPoints;
        headPoints.push_back(vec3(/*V1*/ -0.5f, 1.5f, 0.0f));
        headPoints.push_back(vec3(/*V2*/  0.5f, 1.5f, 0.0f));
        headPoints.push_back(vec3(/*V3*/ -0.5f, 1.0f, 0.0f));
        headPoints.push_back(vec3(/*V4*/  0.5f, 1.0f, 0.0f));

        std::vector<vec3> leftWingPoints;
        leftWingPoints.push_back(vec3(/*V1*/ -4.0f, 1.0f, 0.0f));
        leftWingPoints.push_back(vec3(/*V2*/ -1.0f, 1.0f, 0.0f));
        leftWingPoints.push_back(vec3(/*V3*/ -2.0f, -1.0f, 0.0f));

        std::vector<vec3> rightWingPoints;
        rightWingPoints.push_back(vec3(/*V1*/ 1.0f, 1.0f, 0.0f));
        rightWingPoints.push_back(vec3(/*V2*/ 4.0f, 1.0f, 0.0f));
        rightWingPoints.push_back(vec3(/*V3*/ 2.0f, -1.0f, 0.0f));

        batHead.init(headPoints);
        batBody.init(bodyPoints);
        leftWing.init(leftWingPoints);
        rightWing.init(rightWingPoints);

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
