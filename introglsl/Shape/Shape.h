#ifndef SHAPE_H
#define SHAPE_H


class Shape
{
public:
    Shape();
    virtual void draw() = 0;
    virtual void cleanup() = 0;
    virtual void init() = 0;
};

#endif // SHAPE_H
