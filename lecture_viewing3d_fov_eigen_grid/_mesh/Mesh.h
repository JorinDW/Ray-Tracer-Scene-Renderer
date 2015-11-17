#pragma once
#include "icg_common.h"

class Mesh{
public:
    bool wireframe = true;
    
protected:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID
    GLuint _tex;
    //opengp::Surface_mesh mesh;
    GLuint _vpoint;    ///< memory buffer
    GLuint _vnormal;   ///< memory buffer

public:        
    GLuint getProgramID(){ 
        return _pid; 
    }
    
    void init(){ //in this method we create the vertex array that will be referenced by the indice array
        //the height and width of the mesh as counted in number of triangles
        int _rowsAndCols = 10;
        //the value that will be used to restart the triangle strips
        int _restartValue = _rowsAndCols * _rowsAndCols + _rowsAndCols;
        //vector of vec3s that will represent vertices in the mesh of triangles.
        vector<vec3> _vertices;

        //algorithm that generates the vec3 vertices based on the _rowsAndCols variable
        int i;
        for(i = 0; i < _rowsAndCols; i++){
            printf("hello");
        }

        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);//create a vertex array
        glBindVertexArray(_vao);//bind to the vertex array we created so it is available
        check_error_gl();//check for errors

        ///--- Index Buffer
        std::vector<unsigned int> indices;

//        ///--- Compile the shaders
//        _pid = opengp::load_shaders("_mesh/Mesh_vshader.glsl", "_mesh/Mesh_fshader.glsl");
//        if(!_pid) exit(EXIT_FAILURE);
//        glUseProgram(_pid);
    }
           
    void cleanup(){
        /// TODO
    }

    void draw(){
        bindShader();
            ///--- Setup the texture units
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _tex);
            glUniform1f(glGetUniformLocation(_pid, "time"), glfwGetTime());
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
            glDrawElements(GL_TRIANGLES, /*#vertices*/ 3*mesh.n_faces(), GL_UNSIGNED_INT, ZERO_BUFFER_OFFSET);
        unbindShader();
    }
    
private:
    void bindShader() {
//        glUseProgram(_pid);
//        glBindVertexArray(_vao);
//        check_error_gl();

        ///--- Vertex Attribute ID for Positions
        GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");


        ///--- Vertex Attribute ID for Normals
        GLint vnormal_id = glGetAttribLocation(_pid, "vnormal");

    }

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
