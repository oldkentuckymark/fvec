#include "fren.hpp"
#include <SDL2/SDL.h>


constexpr fren::math::fixed32 operator""_fx(long double f)
{
    fren::math::fixed32 r(static_cast<float>(f));
    return r;
}


class SDLDRAWER : public fren::Context
{
    SDL_Window* win{};
    SDL_Renderer* ren{};
public:
    SDLDRAWER()
    {
        SDL_CreateWindowAndRenderer(1200*2,800*2,0,&win,&ren);
        SDL_RenderSetLogicalSize(ren, 240, 160);
    }

    auto virtual plot(uint16_t x, uint16_t y, uint16_t c) -> void override
    {
        auto col = fren::Convert555to888(c);
        SDL_SetRenderDrawColor(ren,col[0],col[1],col[2],col[3]);
        //SDL_SetRenderDrawColor(ren,255,0,0,255);
        SDL_RenderDrawPoint(ren,x,y);
    }

    auto virtual line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) -> void override
    {
        auto col = fren::Convert555to888(color);
        SDL_SetRenderDrawColor(ren,col[0],col[1],col[2],col[3]);
        SDL_RenderDrawLine(ren, x1,y1,x2,y2);

    }

    auto clear() -> void override
    {
        SDL_SetRenderDrawColor(ren,0,0,0,255);
        SDL_RenderClear(ren);
    }

    auto present() -> void override
    {
        SDL_RenderPresent(ren);
    }
};

class VertexShader : public fren::VertexFunction
{
public:
    VertexShader()
    {
        //mv = glm::mat4(1.0f);
        //pj = glm::ortho(0.0f,1.0f,1.0f,0.0f);
        //pj = glm::perspective(45.0f, 1.0f, 0.2f, 1000.0f);

    }

    fren::math::vec4 operator() (const fren::math::vec4& in) override
    {
        //return pj * mv * in;
        return in;
    }

    //glm::mat4 mv, pj;
};



fren::math::fixed32 par[6] =
{
    0.25_fx,0.25_fx, 0.25_fx,0.5_fx, 0.5_fx,0.5_fx
};

uint16_t car[6] =
{
    UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX
};




auto main(int argc, char *argv[]) -> int
{

    auto ggg = par[0];

    SDL_Init(SDL_INIT_VIDEO);

    VertexShader vs;

    SDLDRAWER r;
    r.setViewPort(240,160);
    r.setVertexFunction(&vs);

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

        const auto sintable = fren::math::makeTable< int,30,std::sinf >;


        r.clear();

        r.VertexPointer(2, par);
        r.ColorPointer(car);

        r.DrawArray(fren::DrawType::Points, 0, 3);

        r.present();



    }




    return 0;
}
