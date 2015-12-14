#version 330 core
uniform float time;
in vec3 vpoint; ///< [-1,+1]
out float vheight; ///< for debug coloring
out float scale=0.01;
out float scaleB = 0.5;
out vec3 fpoint;
uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJ;
uniform sampler2D tex;
//uniform sampler2D grass;
//uniform sampler2D sand;
//uniform sampler2D rock;
//uniform sampler2D water;
//uniform sampler2D snow;
float tex_at(vec2 uv){ return texture(tex,uv).b; }

void main() {
//    if(scale * tex_at(scaleB*vec2(vpoint.x, vpoint.y)+scaleB) < 0){
//        vheight = 0;
//    }
//    else{
        vheight = scale * tex_at(scaleB*vec2(vpoint.x, vpoint.y)+scaleB);
//    }
    fpoint = vec3(vpoint.x, vpoint.y, vheight);
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint.x, vpoint.y, vheight, 1.0);
}
