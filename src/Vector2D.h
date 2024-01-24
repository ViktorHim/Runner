#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
class Vector2D
{
    public:
        int x;
        int y;
        Vector2D(int x, int y);
        Vector2D();
        static int calculateDistance(Vector2D first, Vector2D second);
};
#endif