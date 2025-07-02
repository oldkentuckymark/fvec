#include "fvec.hpp"
#include <SDL2/SDL.h>


auto pix(short,short) -> void
{
    return;
}



auto main(int argc, char *argv[]) -> int
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_CreateWindowAndRenderer(1200,800,0,&win,&ren);
    SDL_RenderSetLogicalSize(ren, 240, 160);


    fvec::fixed32 a{int16_t(100)};
    fvec::fixed32 b{int16_t(100)};

    auto c = (a/b);


    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            else if(e.type == SDL_MOUSEMOTION)
            {
                //cam0ref.yaw_ -= (float)e.motion.xrel / 200.f;

            }
        }
        uint8_t const * const keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_ESCAPE])
        {
            running = false;
        }
        if (keys[SDL_SCANCODE_W])
        {

        }
        SDL_SetRenderDrawColor(ren,0,0,0,255);
        SDL_RenderClear(ren);


        SDL_SetRenderDrawColor(ren,255,0,0,255);
        SDL_RenderDrawLine(ren,0,0,a,b);





        SDL_RenderPresent(ren);


    }




    return 0;
}
