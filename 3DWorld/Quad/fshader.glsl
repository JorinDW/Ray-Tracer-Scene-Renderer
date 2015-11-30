#version 330 core
out vec3 color;
in vec3 fpoint;
in float vheight; ///< for debug coloring
in float scale; ///< to normalize color range
in vec2 uv;
in float scaleB;
uniform sampler2D tex;
vec3 Red = vec3(1,0,0);
vec3 Green = vec3(0,1,0);
vec3 Blue = vec3(0,0,1);
vec3 White = vec3(1,1,1);
vec3 Black = vec3(0,0,0);
vec3 Brown = vec3(1,0.5,0.5);
vec3 normal;
float dot;
vec3 ex;
vec3 ey;
vec3 light = vec3(0,1,1);
float tex_at(vec2 uv){ return texture(tex,uv).b; }
float stepx;
float stepy;
vec3 water;
vec3 land;
void main() {
    vec2 size = textureSize(tex,0);
    stepx = 2/size[0];
    stepy = 2/size[1];
    ex = fpoint - vec3(fpoint.x + stepx, fpoint.y, scale * tex_at(scaleB*vec2(fpoint.x + stepx, fpoint.y)+scaleB));
    ey = fpoint - vec3(fpoint.x, fpoint.y + stepy, scale * tex_at(scaleB*vec2(fpoint.x, fpoint.y + stepy)+scaleB));
    normal = normalize(cross(ex,ey));
    dot = dot(normal,normalize(light));
    water = mix(Blue,Green,5*(vheight/scale));
    land = mix(Green,White,1.1*(vheight/scale));
    if(vheight < 0.01){
        color = water;
    }else{
        color = dot*mix(White,land,1);//mix(Green,White,1.1*(vheight/scale));
    }
    /*
    if(vheight < 0.02){
        color = dot*White;//mix(Blue,Green,5*(vheight/scale));
    }
    else{
        color = dot*White;//mix(Green,White,1.1*(vheight/scale));
    }*/
}


