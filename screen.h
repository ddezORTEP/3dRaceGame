#include <SDL2/SDL.h>
#include <vector>
#include <numeric>
#include<iostream>

struct vec3
{
    float x,y,z;
};
struct connection{
    int a,b;
};
struct tri{
    vec3 p[3];
};


class Screen
{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    public:
    Screen(){
    
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(640*2,480*2,0, &window, &renderer);
        SDL_RenderSetScale(renderer,2,2);
    }

    void pixel(float x, float y){
            points.emplace_back(x,y);
    }

    void show(){
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        for(auto& point : points)
        {
            SDL_RenderDrawPointF(renderer,point.x, point.y);
        }
        SDL_RenderPresent(renderer);
    }
   void clear() {
    points.clear();
   } 
    void input()
    {
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)            {
            SDL_Quit();
            exit(0);

            }
        }
    
    }
void line(Screen& screen, float x1, float y1, float x2, float y2){
float dx = x2 - x1;
float dy = y2 - y1;

float length= std::sqrt(dx*dx + dy * dy);
float angle = std::atan2(dy, dx); 
for(float i = 0; i < length; i++){
  screen.pixel(
          x1 + std::cos(angle) * i,
          y1 + std::sin(angle) * i
          );
 }
}

void rotate(vec3& point, float x=1, float y =1, float z=1){
    float rad = 0;
    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;

}



};
