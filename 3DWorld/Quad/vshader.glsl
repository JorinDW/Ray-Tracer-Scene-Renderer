#version 330 core
uniform float time;
in vec3 vpoint; ///< [-1,+1]
out float vheight; ///< for debug coloring
out float scale=.1;
uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJ;
uniform sampler2D tex;
float tex_at(vec2 uv){ return texture(tex,uv).b; }

void main() {
    if(scale * tex_at(0.5*vec2(vpoint.x, vpoint.y)+0.5) < 0){
        vheight = 0;
    }
    else{
        vheight = scale * tex_at(0.5*vec2(vpoint.x, vpoint.y)+0.5);
    }
    //vheight = 0;
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint.x, vpoint.y, vheight, 1.0);
}
