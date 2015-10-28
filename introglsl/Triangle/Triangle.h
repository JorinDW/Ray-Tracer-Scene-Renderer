#pragma once
#include "icg_common.h"
#include "../Shape/Shape.h"

class Triangle: public Shape{
private:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID 
    GLuint _vbo; ///< memory buffer
public:
    virtual void init(std::vector<vec3> vpoint) override{
        ///--- Compile the shaders
        _pid = opengp::load_shaders("Triangle/vshader.glsl", "Triangle/fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);       
        glUseProgram(_pid);
        
        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
     
        ///--- Vertex Buffer
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3)*vpoint.size(), &vpoint[0], GL_STATIC_DRAW);
    
        ///--- vpoint shader attribute
        GLuint position = glGetAttribLocation(_pid, "vpoint"); ///< Fetch Attribute ID for Vertex Positions
        glEnableVertexAttribArray(position); /// Enable it
        glVertexAttribPointer(position, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
                      
        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }
       
    virtual void cleanup() override{
        glBindVertexArray(0);
        glUseProgram(0);
        glDeleteBuffers(1, &_vbo);
        glDeleteProgram(_pid);
        glDeleteVertexArrays(1, &_vao);
    }
        
    virtual void draw() override{
        glUseProgram(_pid);
        glBindVertexArray(_vao);       
            ///--- Draw
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);        
        glUseProgram(0);
    }
};
