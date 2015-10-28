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
    vector<Shape*> wings;
public:
    void init(){
        /// Initialize the body parts with the generic bat coords.
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
        wings.push_back(&leftWing);
        wings.push_back(&rightWing);
    }
       
    void cleanup(){
        ///Call the Quad and Triangle cleanup functions
        for(auto &k : bodyParts){
            k->cleanup();
        }
    }
    
    void draw(mat4& M){
        float time = glfwGetTime();

        ///Perform bat transformations using bat_M to track changes
        //float freq = M_PI*time*10;
        //bat_M *= Eigen::Affine3f(Eigen::Translation3f(0.0, 0.0, 0.0)).matrix();
    //    Transform sun_M = Transform::Identity();
    //    sun_M *= Eigen::Translation3f(0.2, 0.0, 0.0);
    //    sun_M *= Eigen::AngleAxisf(-freq/SUN_ROT_PERIOD, Eigen::Vector3f::UnitZ());
    //    //scale_t: make the sun become bigger and smaller over the time!
        float scale_t = abs(std::sin(time));
        M *= Eigen::Affine3f(Eigen::AlignedScaling3f(0.2 +scale_t, 0.2 +scale_t, 1.0)).matrix();


        ///Call the Quad Draw functions
        for(auto &k : bodyParts){
            k->draw(M);
        }

        ///Call the Triangle Draw functions
        for(auto &j : wings){
            j->draw(M);
        }
    }
};
