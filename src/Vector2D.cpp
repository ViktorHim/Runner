#include "Vector2D.h"

Vector2D::Vector2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

int Vector2D::calculateDistance(Vector2D first, Vector2D second)
{
    int dx = first.x - second.x;
    int dy = first.y - second.y;
    return sqrt(dx*dx + dy*dy);
}
