#pragma once

namespace fvec
{

template<class T>
class vec2
{
public:
    T x,y;

    auto operator + (vec2 const & that) -> vec2
    {
        return {x+that.x,y+that.y};
    }

    auto operator - (vec2 const & that) -> vec2
    {
        return {x-that.x,y-that.y};
    }

    auto operator * (T const scalar) -> vec2
    {
        return {x*scalar,y*scalar};
    }

    auto operator / (T const scalar) -> vec2
    {
        return {x/scalar,y/scalar};
    }
};

template<class T>
class vec3
{
    T x,y,z;
};


template<class TYPE,  void (*PIXEL_FUNCTION)(short,short)>
class Renderer
{
public:
    TYPE a,b,c;

    Renderer()
    {
        PIXEL_FUNCTION(1,2);
    }


};

}
