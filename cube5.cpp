#include "screen.h"
int main()
{
    Screen screen;
    Camera camera;

    // Define the cube's vertices
    std::vector<vec3> points = {
        {100, 100, 100}, {200, 100, 100}, {200, 200, 100}, {100, 200, 100}, // Front face
        {100, 100, 200}, {200, 100, 200}, {200, 200, 200}, {100, 200, 200}  // Back face
    };

    // Define the cube's faces as triangles
    std::vector<triangle> triangles = {
        // Front face
        {0, 1, 2, {255, 0, 0, 255}}, {0, 2, 3, {255, 0, 0, 255}},
        // Back face
        {4, 5, 6, {0, 255, 0, 255}}, {4, 6, 7, {0, 255, 0, 255}},
        // Left face
        {0, 4, 7, {0, 0, 255, 255}}, {0, 7, 3, {0, 0, 255, 255}},
        // Right face
        {1, 5, 6, {255, 255, 0, 255}}, {1, 6, 2, {255, 255, 0, 255}},
        // Top face
        {0, 1, 5, {255, 0, 255, 255}}, {0, 5, 4, {255, 0, 255, 255}},
        // Bottom face
        {3, 2, 6, {0, 255, 255, 255}}, {3, 6, 7, {0, 255, 255, 255}}
    };

    // Calculate the centroid of the cube
    vec3 centroid = {0, 0, 0};
    for (const auto& p : points)
    {
        centroid.x += p.x;
        centroid.y += p.y;
        centroid.z += p.z;
    }
    centroid.x /= points.size();
    centroid.y /= points.size();
    centroid.z /= points.size();

    // Main loop
    while (true)
    {
        // Handle input for camera controls
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W]) camera.position.z += 5; // Move forward
        if (keystate[SDL_SCANCODE_S]) camera.position.z -= 5; // Move backward
        if (keystate[SDL_SCANCODE_A]) camera.position.x -= 5; // Move left
        if (keystate[SDL_SCANCODE_D]) camera.position.x += 5; // Move right
        if (keystate[SDL_SCANCODE_Q]) camera.position.y -= 5; // Move down
        if (keystate[SDL_SCANCODE_E]) camera.position.y += 5; // Move up
        if (keystate[SDL_SCANCODE_LEFT]) camera.rotateYaw(0.05f); // Rotate left
        if (keystate[SDL_SCANCODE_RIGHT]) camera.rotateYaw(-0.05f); // Rotate right

        // Rotate the cube around its centroid
        for (auto& p : points)
        {
            p.x -= centroid.x;
            p.y -= centroid.y;
            p.z -= centroid.z;
//            screen.rotate(p, 0.01, 0.01, 0.01);
            p.x += centroid.x;
            p.y += centroid.y;
            p.z += centroid.z;
        }

        // Project points to screen space using the camera
        std::vector<vec3> projectedPoints;
        for (const auto& p : points)
        {
            projectedPoints.push_back(camera.project(p, 640, 480));
        }

        // Clear the screen, draw the cube, and show the result
        screen.clear();
        screen.backfaceCullAndDraw(projectedPoints, triangles, camera);
        screen.show();

        // Handle input and delay
        screen.input();
        SDL_Delay(30);
    }

    return 0;
}
