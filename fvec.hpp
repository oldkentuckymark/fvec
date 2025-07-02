#pragma once

#include <cstdint>

namespace fvec
{


class fixed32   //16.16
{
static constexpr int32_t FIX_SHIFT = 16;
static constexpr int32_t FIX_SCALE = 65536;
static constexpr float FIX_SCALEF = 65536.0f;

public:
    int32_t data;

    fixed32() = default;
    fixed32(fixed32 const &that) = default;
    fixed32& operator = (fixed32 &that) = default;

    explicit fixed32(int16_t that)
    {
        data = that << FIX_SHIFT;
    }

    explicit fixed32(float that)
    {
        data = (that*FIX_SCALE);
    }

    fixed32& operator = (int16_t that)
    {
        data = that << FIX_SHIFT;
        return (*this);
    }

    fixed32& operator = (float that)
    {
        data = (that*FIX_SCALE);
        return (*this);
    }

    operator int32_t ()
    {
        return data / FIX_SCALE;
    }

    operator int16_t ()
    {
        return data / FIX_SCALE;
    }

    fixed32 operator + (fixed32 that)
    {
        fixed32 r;
        r.data = data + that.data;
        return r;
    }

    fixed32 operator - (fixed32 that)
    {
        fixed32 r;
        r.data = data - that.data;
        return r;
    }

    fixed32 operator * (fixed32 that)
    {
        fixed32 r;
        r.data = (int64_t(data) * that.data) >> FIX_SHIFT;
        return r;
    }

    fixed32 operator / (fixed32 that)
    {
        fixed32 r;
        r.data = (int64_t(data) * FIX_SCALE) / (that.data);
        return r;
    }


};

template<class TYPE,  void (*PIXEL_FUNCTION)(int16_t,int16_t, uint8_t, uint8_t, uint8_t)>
class Renderer
{
public:
    TYPE a,b,c;

    Renderer()
    {
        PIXEL_FUNCTION(1,2,0,0,0);
    }


};

}
