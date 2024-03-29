#include "icg_common.h"

#include "OpenGLImage/EigenVisualizer.h"

using namespace EigenVisualizer;

//return a random floating point number between [0, 1]
float rand0_1()
{
    return ((float) std::rand())/((float) RAND_MAX);
}

float mix(float x, float y, float alpha)
{
    return y * alpha + x * (1.0f - alpha);
}


float f(float t)
{
    float t_3 = t * t * t;
    return 6 * t * t * t_3 - 15 * t * t_3 + 10 * t_3;
}

RGBImage makePerlin(int width, int height, int period, RGBImage base,float strength){
    RGBImage PerlinNoise(width, height);
    float frequency = 1.0f / period;
    for (int i = 0; i < width; ++ i)
       for (int j = 0; j < height; ++ j)
       {
           int left = (i / period) * period;
           int right = (left + period) % width;
           float dx = (i - left) * frequency;

           int top = (j / period) * period;
           int bottom = (top + period) % height;
           float dy = (j - top) * frequency;

           vec2 a(dx, -dy);
           vec2 b(dx - 1, -dy);
           vec2 c(dx - 1, 1 - dy);
           vec2 d(dx, 1 - dy);

           vec3 topleft = base(left, top);
           float s = topleft(0) * a(0) + topleft(1) * a(1);
           vec3 topright = base(right, top);
           float t = topright(0) * b(0) + topright(1) * b(1);
           vec3 bottomleft = base(left, bottom);
           float u = bottomleft(0) * d(0) + bottomleft(1) * d(1);
           vec3 bottomright = base(right, bottom);
           float v = bottomright(0) * c(0) + bottomright(1) * c(1);

           float fx = f(dx);
           float fy = f(dy);

           float st = mix(s, t, fx);
           float uv = mix(u, v, fx);
           float noise = mix(st, uv, fy);

           PerlinNoise(i, j) = vec3(noise*strength, noise*strength, noise*strength);
       }
    return PerlinNoise;
}

int main(int, char**){

    int width = 300;
    int height = 300;

    //Create the base noise
    vec3 randGradientVec;
    RGBImage base(width, height);
    //Note: std::time(0) doesn't work on Windows
    //On mac you can do std::srand(std::time(0)); to get a completely randomized Perlin patch
    std::srand(1);
    for (int i = 0; i < width; ++ i)
        for (int j = 0; j < height; ++ j)
        {
            //we use vec3 instead of vec2 but set the last component to zero
            randGradientVec(0) = cos(2 * M_PI * rand0_1());
            randGradientVec(1) = sin(2 * M_PI * rand0_1());
            randGradientVec(2) = 0;
            base(i, j) = randGradientVec;
        }
    float s1 = 0.5;
    float s2 = 1.7;
    float s3 = 1.0;
    RGBImage perlin1(width,height);
    perlin1 = makePerlin(width,height,64,base,s1); //makePerlin(int width, int height, int period, RGBImage base, float strength)
    RGBImage perlin2(width,height);
    perlin2 = makePerlin(width,height,32,base,s2);
    RGBImage perlin3(width,height);
    perlin3 = makePerlin(width,height,16,base,s3);

    RGBImage perlinCombo(width,height);

    perlinCombo = perlin1 + perlin2 - perlin3;
    //string title = "Perlin noise with strengths: " + s1.toString() + ", " + s2.toString() + ", " + s3.toString();
    char title[] = "Perlin Noise with strengths";
    showImage(perlinCombo, title);


    return EXIT_SUCCESS;

}

