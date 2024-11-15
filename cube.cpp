#include "screen.h"

int main(){

    Screen Screen;


    // our cube
    std::vector<vec3> points {
        //points for first half of cube   
        {100,100,100},
            {200,100,100},
            {200,200,100},
            {100,200,100},

            //points for second half of cube
            {100,100,200},
            {200,100,200},
            {200,200,200},
            {100,200,200}

    };
    std::vector<connection> connections{
        //connect side lines
        {0,4},
            {1,5},
            {2,6},
            {3,7},
            
            //connect front faces
            {0,1},
            {1,2},
            {2,3},
            {3,0},

            //connect back faces
            {4,5},
            {5,6},
            {6,7},
            {7,4},
            // triangles
            {1,3},
            {3,6},
            {2,5},
            {5,7},
    };


    // calculate centroid
    //
    vec3 centroid{0,0,0};
    for(auto& p : points){
        centroid.x += p.x;
        centroid.y += p.y;
        centroid.z += p.z;
    }
    centroid.x /= points.size();
    centroid.y /= points.size();
    centroid.z /= points.size();


    //main loop
    while(true)
    {
        //rotation of cube
        for(auto& p : points){
            p.x -= centroid.x;
            p.y -= centroid.y;
            p.z -= centroid.z;
            Screen.rotate(p, 0.002, 0.001, 0.004);
            p.x += centroid.x;
            p.y += centroid.y;
            p.z += centroid.z;

        }

        for(auto& p : points){
            Screen.pixel(p.x, p.y);
        }
        for(auto& conn : connections){
            Screen.line(Screen, points[conn.a].x,
                    points[conn.a].y,
                    points[conn.b].x,
                    points[conn.b].y);
        }
        Screen.show();
        Screen.clear();
        Screen.input();
        SDL_Delay(30);
    }


    return 0;
}
