#pragma once
#include "icg_common.h"

class Quad{
private:
    GLuint _vao; /// vertex array object
    GLuint _vbo; /// vertex buffer object
    GLuint _ibo; /// index buffer object
    GLuint _pid; /// GLSL shader program ID
    bool wireframe = true; /// bolean used to determine wireframe or filled rendering
    const int _numOfTris = 100; /// the number of triangles to render on a side (square terrain mesh)
public:
    ///--- Initialization of Quad
    void init(){
        ///--- Vertex coordinates specification/generation
        /// We start with the simples strip of triangles, a four point quad
        /// We then produce the rest of the points based on the _numOfTris value through a for loop.
        const GLfloat vpoint[] = { /*V1*/ -1.0f, -1.0f, 0.0f,
                                   /*V2*/ +1.0f, -1.0f, 0.0f,
                                   /*V3*/ -1.0f, +1.0f, 0.0f,
                                   /*V4*/ +1.0f, +1.0f, 0.0f };

        ///--- Vertex Array Object creation
        /// We first generate a vertex array in the GPU
        /// Then bind that buffer to _vao
        /// Then check errors
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        check_error_gl();

        ///--- Vertex Buffer Object creation
        /// We first generate the vertex buffer
        /// Then bind that buffer to _vbo
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vpoint), vpoint, GL_STATIC_DRAW);
        
        ///--- Index Buffer Object creation
        /// We first generate
        ///--- Frees all bindings and programs
        glBindVertexArray(0);

        ///--- Compile the shaders
        _pid = opengp::load_shaders("_mesh/Mesh_vshader.glsl", "_mesh/Mesh_fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);
        glUseProgram(_pid);
    }

    ///--- Cleanup the quad
    void cleanup(){
        /// Setting a binding to 0 frees it
        glBindVertexArray(0);
        /// Setting program binding to 0 frees it
        glUseProgram(0);
        /// Delete the vertex buffer
        glDeleteBuffers(1, &_vbo);
        /// Delete the vertex array
        glDeleteVertexArrays(1, &_vao);
    }
    
    ///--- Draw the quad
    void draw(){
        /// Binds the data that we setup in the init() to the shaders
        bindShader();
        /// activate access to the vertex array
        glBindVertexArray(_vao);
        /// being polygon mode which enables the dis
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /// draw the elements onto the image
        glDrawElements(GL_TRIANGLE_STRIP, _numOfTris*2*_numOfTris, GL_UNSIGNED_INT, ZERO_BUFFER_OFFSET);
        /// release the array
        glBindVertexArray(0);
        /// release the program
        glUseProgram(0);
        /// unbind the shader
        unbindShader();
    }
private:
    ///--- Bind shader(s)
    void bindShader() {
        glUseProgram(_pid);
        glBindVertexArray(_vao);
        check_error_gl();

        ///--- Vertex Attribute ID for Positions
        GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");
        if (vpoint_id >= 0) {
            glEnableVertexAttribArray(vpoint_id);
            check_error_gl();
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glVertexAttribPointer(vpoint_id, 3 /*vec3*/, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
            check_error_gl();
        }

    }
    ///--- Unbind shader(s)
    void unbindShader() {
        GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");
        if (vpoint_id >= 0)
            glDisableVertexAttribArray(vpoint_id);
        GLint vnormal_id = glGetAttribLocation(_pid, "vnormal");
        if (vnormal_id >= 0)
            glDisableVertexAttribArray(vnormal_id);
        glUseProgram(0);
        glBindVertexArray(0);
    }
};
