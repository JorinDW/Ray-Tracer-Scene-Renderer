#pragma once
#include "icg_common.h"
typedef Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RGBImage;
class Quad{
private:
    GLuint _vao; /// vertex array object
    GLuint _vbo; /// vertex buffer object
    GLuint _ibo; /// index buffer object
    GLuint _pid; /// GLSL shader program ID
    GLuint _tex; /// Texture ID
    GLuint _tex_night; /// Texture ID
    GLuint _snow;
    GLuint _grass;
    GLuint _sand;
    GLuint _rock;
    GLuint _water;
    const int _numOfVerts = 400; /// the number of triangles to render on a side (square terrain mesh)
    std::vector<unsigned int> indices; /// indices vector
    std::vector<vec3> vpoint; /// vertex point vector
public:
    bool wireframe = true; /// bolean used to determine wireframe or filled rendering
    ///return the program ID to the main loop
    GLuint getProgramID(){
        return _pid;
    }

    ///--- Initialization of Quad
    void init(RGBImage perlin){

        ///--- Vertex Array Object creation
        /// We first generate a vertex array in the GPU
        /// Then bind that buffer to _vao
        /// Then check errors
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        check_error_gl();

        ///--- Vertex coordinates specification/generation
        /// We start with the simples strip of triangles, a four point quad
        /// We then produce the rest of the points based on the _numOfVerts value through a for loop.
        /// The max positions of the top, bottom, left and right sides
        float maxXY = 0.9;
        /// The actual distance to be split up into segments
        float distanceXY = maxXY * 2;
        /// The size of the steps that we take between points
        float offsetXY = distanceXY/_numOfVerts;
        /// Go through all _numOfVerts x _numOfVerts vertexs and push_back them into the vpoints vector
        /// Based on coords determined using the offsetXY and maxXY
        for(int i = 0; i < _numOfVerts; i++){
            for(int j = 0; j < _numOfVerts; j++){
                /// The x,y,z values of the vertex
                float x = -maxXY + offsetXY * j;
                float y = maxXY - offsetXY * i;
                float z = 0.0;
                vpoint.push_back(vec3(x,y,z));
                //printf("vpoint x: %f, y: %f, z: 0\n", x, y);
            }
        }

        ///--- Vertex Buffer Object creation
        /// We first generate the vertex buffer
        /// Then bind that buffer using _vbo
        /// Then inject the data in a given format in glBufferData from the vpoint array
        /// Then check errors
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _numOfVerts * _numOfVerts * sizeof(vec3), &vpoint[0], GL_STATIC_DRAW);
        check_error_gl();

        ///--- Index Buffer Object population
        /// iterate through the indice locations
        /// Run through all indices that we are going to use in the correct rendering order
        for(int i = 0; i < _numOfVerts * ( _numOfVerts - 1); i ++){
            /// If i is a remainder = 0 divisor of _numOfVerts then push back our restart index
            if(i%_numOfVerts == 0){
                indices.push_back(pow(_numOfVerts,2));
            }
            /// Push in the pair of indices, i, and i + _numOfVerts
            indices.push_back(i);
            indices.push_back(i + _numOfVerts);
        }

        ///--- Index Buffer Object creation
        /// We first create a variable to use to connect the buffer generation with the buffer binding
        /// Then we generate the buffer
        /// Then we bind the buffer
        /// Then send the buffer the data inside the indices array with the settings that we want
        /// Then we check the errors
        GLuint _vbo_indices;
        glGenBuffers(1, &_vbo_indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        check_error_gl();

        ///--- Compile the shaders
        _pid = opengp::load_shaders("Quad/vshader.glsl", "Quad/fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);
        glUseProgram(_pid);
        RGBImage fBm = makeFBM(perlin);
        ///--- Load texture
        loadTextureRGB32F(fBm.data(), fBm.rows(), fBm.cols());
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
        ///--- Setup the texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _tex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _snow);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _grass);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _sand);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, _rock);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, _water);


        glUniform1f(glGetUniformLocation(_pid, "time"), glfwGetTime());
        /// Enable triangle strip looping using an index outside of the range of the indices
        glEnable(GL_PRIMITIVE_RESTART);
        /// Use _numOfVerts squared to give us the restart index.
        glPrimitiveRestartIndex(pow(_numOfVerts,2));
        /// being polygon mode which enables the wireframe/filled mode switching
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
        /// draw the elements onto the image
        glDrawElements(GL_TRIANGLE_STRIP,indices.size(), GL_UNSIGNED_INT, ZERO_BUFFER_OFFSET);
        /// unbind the shader
        unbindShader();
    }
private:
    ///--- FBM calculator
    RGBImage makeFBM(RGBImage perlin){
        double H = 0.25;
        double lacunarity = 2;
        int MAX_OCTAVES = 2;
        vec3 value;
        double frequency;
        double amplitude = 0.85;
        double expArray[MAX_OCTAVES];
        int first = 1;
        RGBImage fbm(perlin.rows(),perlin.cols());
        for(int i = 0; i < perlin.cols(); i++){
            for(int j = 0; j < perlin.rows(); j++){
                int x = i;
                int y = j;
                value = vec3(0.0,0.0,0.0);
                if(first){
                    frequency = 2;
                    for(int k = 0; k < MAX_OCTAVES; k++){
                        expArray[k] = pow(frequency, -H);
                        frequency *= lacunarity;
                    }
                    first = 0;
                }
                for(int l = 0; l < MAX_OCTAVES; l++){
                    value += perlin(x%perlin.rows(),y%perlin.cols()) * expArray[l];
                    x *= lacunarity;
                    y *= lacunarity;
                }
                fbm(i,j) = value * amplitude;
            }
        }
        return fbm;
    }

    double exp_array_gen(int k,double freq, double H, double lac){
        double octave = pow(freq,-H);

        return octave;
    }

    ///--- Bind shader(s)
    void bindShader() {
        /// enable the opengl shaders
        glUseProgram(_pid);
        /// bind the vertex array object
        glBindVertexArray(_vao);
        /// check for error
        check_error_gl();

        ///--- Vertex Attribute ID for Positions
        GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");
        /// check that vpoint_id is greater or equal to 0
        if (vpoint_id >= 0) {
            /// send the vpoint array to the GPU
            glEnableVertexAttribArray(vpoint_id);
            /// check that the vpoint made it
            check_error_gl();
            /// bind the vertex buffer object
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            /// give GPU access to the beginning of the vpoint array
            glVertexAttribPointer(vpoint_id, 3 /*vec3*/, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
            /// check for errors
            check_error_gl();
        }
    }

    ///--- Unbind shader(s)
    void unbindShader() {
        GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");
        if (vpoint_id >= 0)
            glDisableVertexAttribArray(vpoint_id);
        glUseProgram(0);
        glBindVertexArray(0);
    }

    ///---Bind the perlin texture so that it can be used in the vshader
    void loadTextureRGB32F(void * pTex, int width, int height)
        {
            glBindTexture(GL_TEXTURE_2D, _tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);`
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width,
                            height, 0, GL_RGB, GL_FLOAT,
                            pTex);

            glGenTextures(1, &_snow);
            glBindTexture(GL_TEXTURE_2D, _snow);
            glfwLoadTexture2D("Quad/snow.tga", 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glUniform1i(glGetUniformLocation(_pid, "snow"), 1 /*GL_TEXTURE0*/);

            glGenTextures(1, &_grass);
            glBindTexture(GL_TEXTURE_2D, _grass);
            glfwLoadTexture2D("Quad/grass.tga", 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glUniform1i(glGetUniformLocation(_pid, "grass"), 2 /*GL_TEXTURE0*/);

            glGenTextures(1, &_sand);
            glBindTexture(GL_TEXTURE_2D, _sand);
            glfwLoadTexture2D("Quad/sand.tga", 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glUniform1i(glGetUniformLocation(_pid, "sand"), 3 /*GL_TEXTURE0*/);

            glGenTextures(1, &_rock);
            glBindTexture(GL_TEXTURE_2D, _rock);
            glfwLoadTexture2D("Quad/rock.tga", 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glUniform1i(glGetUniformLocation(_pid, "rock"), 4 /*GL_TEXTURE0*/);

            glGenTextures(1, &_water);
            glBindTexture(GL_TEXTURE_2D, _water);
            glfwLoadTexture2D("Quad/water.tga", 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glUniform1i(glGetUniformLocation(_pid, "water"), 5 /*GL_TEXTURE0*/);

        }
};
