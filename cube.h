#include "struct.h"
struct Camera {
    vec3 position{0, 0, -500}; // Camera position in world space
    vec3 direction{0, 0, 1};   // Camera direction (forward vector)
    float fov = 90.0f;         // Field of view in degrees
    float nearPlane = 1.0f;    // Near clipping plane
    float farPlane = 1000.0f;  // Far clipping plane
    float yaw = 0.0f;          // Camera yaw (horizontal rotation)

    vec3 rotateVector(const vec3& v, float angle) const {
        float cosAngle = std::cos(angle);
        float sinAngle = std::sin(angle);
        return {
            v.x * cosAngle - v.z * sinAngle,
            v.y,
            v.x * sinAngle + v.z * cosAngle
        };
    }

    vec3 project(const vec3& point, int screenWidth, int screenHeight) const {
        // Convert 3D point to camera space
        vec3 relative = {
            point.x - position.x,
            point.y - position.y,
            point.z - position.z
        };

        // Rotate the relative vector by the inverse camera yaw
        vec3 camSpace = rotateVector(relative, -yaw);

        // Perspective projection
        float aspectRatio = static_cast<float>(screenWidth) / screenHeight;
        float scale = 1.0f / std::tan(fov * 0.5f * M_PI / 180.0f);
        float projX = (scale * camSpace.x) / (aspectRatio * camSpace.z);
        float projY = (scale * camSpace.y) / camSpace.z;

        // Map to screen coordinates
        return {
            (projX + 1) * 0.5f * screenWidth,
            (1 - projY) * 0.5f * screenHeight,
            camSpace.z
        };
    }

    void rotateYaw(float angle) {
        yaw += angle;
    }
};


