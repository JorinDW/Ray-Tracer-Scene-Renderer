#version 330 core
out vec3 color;
in vec3 fpoint;
in float vheight; ///< for debug coloring
in float scale; ///< to normalize color range
in vec2 uv;
uniform sampler2D tex;
vec3 Y = vec3(0,0,0);
vec3 G = vec3(1,0.5,0);
const vec3 COLORS[2] = vec3[](
    vec3(1.0,0.0,0.0),
    vec3(0.0,1.0,0.0));

void main() {
    //color = texture(tex,uv).rgb;
    color = mix(Y,G, 2*vheight/scale);
    //color = vec3(0,0,0);
}


