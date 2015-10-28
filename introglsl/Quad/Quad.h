#pragma once
#include "icg_common.h"
#include "../Shape/Shape.h"
class Quad: public Shape{
private:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID 
    GLuint _vbo_vpoint; ///< memory buffer
public:
    virtual void init(std::vector<vec3> vpoint) override{
        ///--- Compile the shaders
        _pid = opengp::load_shaders("Quad/vshader.glsl", "Quad/fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);       
        glUseProgram(_pid);
        
        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
     
        ///--- Vertex coordinates
        {
            ///--- Buffer
            glGenBuffers(1, &_vbo_vpoint);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo_vpoint);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3)*vpoint.size(), &vpoint[0], GL_STATIC_DRAW);
        
            ///--- Attribute
            GLuint vpoint_id = glGetAttribLocation(_pid, "vpoint");
            glEnableVertexAttribArray(vpoint_id);
            glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
        }

        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }
       
    virtual void cleanup() override{
        glBindVertexArray(0);
        glUseProgram(0);
        glDeleteBuffers(1, &_vbo_vpoint);
        glDeleteProgram(_pid);
        glDeleteVertexArrays(1, &_vao);
    }
    
    virtual void draw() override{
        glUseProgram(_pid);
        glBindVertexArray(_vao);
            ///--- Uniform for animation
            float t = glfwGetTime();
            glUniform1f(glGetUniformLocation(_pid, "time"), t);
            ///--- Draw
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);        
        glUseProgram(0);
    }
};
