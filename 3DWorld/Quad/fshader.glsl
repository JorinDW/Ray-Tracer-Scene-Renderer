#version 330 core
out vec3 color;
in vec3 fpoint;
in float vheight; ///< for debug coloring
in float scale; ///< to normalize color range
in vec2 uv;
uniform sampler2D tex;
vec3 Red = vec3(1,0,0);
vec3 Green = vec3(0,1,0);
vec3 Blue = vec3(0,0,1);
vec3 White = vec3(1,1,1);
vec3 Black = vec3(0,0,0);
vec3 Brown = vec3(1,0.5,0.5);
const vec3 COLORS[2] = vec3[](
    vec3(1.0,0.0,0.0),
    vec3(0.0,1.0,0.0));

void main() {
    //color = texture(tex,uv).rgb;
    //color = mix(Y,G, 2*vheight/scale);
    if(vheight < 0.02){
        color = mix(Blue,Green,5*(vheight/scale));
    }
    else{
        color = mix(Green,White,1.1*(vheight/scale));
    }

}


