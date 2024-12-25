#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>

struct vec3 {
    float x, y, z;
};

struct color {
    Uint8 r, g, b, a;
};

struct triangle {
    int p1, p2, p3; // Indices of points
    color col;      // Color of the triangle
};


