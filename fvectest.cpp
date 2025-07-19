#include "fvec.hpp"
#include <SDL2/SDL.h>


class SDLDRAWER
{
    SDL_Window* win;
    SDL_Renderer* ren;
public:
    SDLDRAWER()
    {
        SDL_CreateWindowAndRenderer(1200*2,800*2,0,&win,&ren);
        SDL_RenderSetLogicalSize(ren, 240, 160);
    }

    auto operator () (uint16_t x, uint16_t y, uint16_t c) -> void
    {

    }
};





auto main(int argc, char *argv[]) -> int
{

    SDL_Init(SDL_INIT_VIDEO);



    auto plot = [&](uint16_t x, uint16_t y, uint16_t c) -> void
    {
        auto col = fvec::Convert555to888(c);
        SDL_SetRenderDrawColor(ren, col[0], col[1], col[2], 255);
        SDL_RenderDrawPoint(ren,x,y);
    };

    fvec::Renderer<fvec::fixed32, plot> r(plot);

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

        const auto sintable = fvec::makeTable< int,30,std::sinf >;

        SDL_SetRenderDrawColor(ren,0,0,0,255);
        SDL_RenderClear(ren);

        r.plot(0,0,fvec::Convert888to555(255,0,0));
        r.plot(1,0,fvec::Convert888to555(255,255,255));
        r.plot(2,0,UINT16_MAX);




        SDL_RenderPresent(ren);

    }




    return 0;
}
