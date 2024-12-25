#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "cube.h"

class Screen {
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Screen() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    ~Screen() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void show() {
        SDL_RenderPresent(renderer);
    }

    void setDrawColor(const color& c) {
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    }

    void setPixel(int x, int y, const color& c) {
        SDL_RenderDrawPointF(renderer, static_cast<float>(x), static_cast<float>(y));
    }
void backfaceCullAndDraw(const std::vector<vec3>& points, const std::vector<triangle>& triangles, const struct Camera& camera) {
    std::vector<SDL_Vertex> vertices;
    std::vector<Uint32> indices;

    for (const auto& tri : triangles) {
        const vec3& p1 = points[tri.p1];
        const vec3& p2 = points[tri.p2];
        const vec3& p3 = points[tri.p3];

        // Compute the normal of the triangle
        vec3 u = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
        vec3 v = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
        vec3 normal = {
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x
        };

        // Check if the triangle is facing the camera
        vec3 view = {p1.x - camera.position.x, p1.y - camera.position.y, p1.z - camera.position.z};
        float dot = normal.x * view.x + normal.y * view.y + normal.z * view.z;
        if (dot < 0) {
            SDL_Vertex v1 = {static_cast<float>(p1.x), static_cast<float>(p1.y), static_cast<float>(p1.z), tri.col.r, tri.col.g, tri.col.b, tri.col.a};
            SDL_Vertex v2 = {static_cast<float>(p2.x), static_cast<float>(p2.y), static_cast<float>(p2.z), tri.col.r, tri.col.g, tri.col.b, tri.col.a};
            SDL_Vertex v3 = {static_cast<float>(p3.x), static_cast<float>(p3.y), static_cast<float>(p3.z), tri.col.r, tri.col.g, tri.col.b, tri.col.a};

            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);

            indices.push_back(static_cast<Uint32>(indices.size()));
            indices.push_back(static_cast<Uint32>(indices.size()));
            indices.push_back(static_cast<Uint32>(indices.size()));
        }
    }

    if (!vertices.empty() && !indices.empty()) {
        SDL_RenderGeometry(renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()), reinterpret_cast<const int*>(indices.data()), static_cast<int>(indices.size()));
    }
}


    void rotate(vec3& point, float angleX, float angleY, float angleZ) {
        // Rotate around X-axis
        float cosX = std::cos(angleX);
        float sinX = std::sin(angleX);
        float y = point.y * cosX - point.z * sinX;
        float z = point.y * sinX + point.z * cosX;
        point.y = y;
        point.z = z;

        // Rotate around Y-axis
        float cosY = std::cos(angleY);
        float sinY = std::sin(angleY);
        float x = point.x * cosY + point.z * sinY;
        z = -point.x * sinY + point.z * cosY;
        point.x = x;
        point.z = z;

        // Rotate around Z-axis
        float cosZ = std::cos(angleZ);
        float sinZ = std::sin(angleZ);
        x = point.x * cosZ - point.y * sinZ;
        y = point.x * sinZ + point.y * cosZ;
        point.x = x;
        point.y = y;
    }

    void input() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
        }
    }
};

#endif
