#version 330 core
uniform float time;
in vec3 vpoint; ///< [-1,+1]
out float vheight; ///< for debug coloring
out float scale=.1;
out float scaleB = 0.5;
out vec3 fpoint;
uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJ;
uniform sampler2D tex;
float tex_at(vec2 uv){ return texture(tex,uv).b; }

void main() {
    if(scale * tex_at(scaleB*vec2(vpoint.x, vpoint.y)+scaleB) < 0){
        vheight = 0;
    }
    else{
        vheight = scale * tex_at(scaleB*vec2(vpoint.x, vpoint.y)+scaleB);
    }
    fpoint = vec3(vpoint.x, vpoint.y, vheight);
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint.x, vpoint.y, vheight, 1.0);
}
