#version 330 core
uniform float time;
in vec3 vpoint; ///< [-1,+1]
out float vheight; ///< for debug coloring
out float scale=.5;
//in bool first;
//in float exp_array;
//out float value;
//out float frequency;
//out float remainder;
//out float octaves;
//out float i;
//need to pass in first
//need to pass in the exponent_array
//need to use perlin noise as the basis
uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJ;
uniform sampler2D tex;
float tex_at(vec2 uv){ return texture(tex,uv).b; }

void main() {

    //vheight =



    /// UNCOMMENT ONE OF THESE
    //vheight = 0;
    //int j = 5
    //vheight = j;
    //vheight = scale * sin(10*vpoint.x + time);
    vheight = scale * tex_at( .5*vec2(vpoint.x, vpoint.y)+.5 );
    //double f = 0.5;
    //vheight = f;
    //vheight = 0;
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint.x, vpoint.y, vheight, 1.0);
}
