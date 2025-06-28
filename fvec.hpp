#pragma once

#include <cstdint>



//typedef s32 fixed32;
//typedef s16 fixed16;



//static inline fixed32 fx_from_int(int d) {
//    return d << FIX_SHIFT;
//}

// static inline fixed32 fx_from_float(float f) {
//     return (fixed32)(f*FIX_SCALE);
// }

// static inline int fx_to_int(fixed32 fx) {
//     return fx / FIX_SCALE;
// }

// static inline float fx_to_float(fixed32 fx) {
//     return fx / FIX_SCALEF;
// }

// static inline fixed32 fx_multiply(fixed32 fa, fixed32 fb) {
//     return (fa*fb)>>FIX_SHIFT;
// }

// static inline fixed32 fx_division(fixed32 fa, fixed32 fb) {
//     return ((fa)*FIX_SCALE)/(fb);
// }



namespace fvec
{


class fixed32   //24.8
{
static constexpr int16_t FIX_SHIFT = 8;
static constexpr int16_t FIX_SCALE = 256;
static constexpr float FIX_SCALEF = 256.0f;

public:
    int32_t data;

    fixed32() = default;
    fixed32(fixed32 const &that) = default;
    fixed32& operator = (fixed32 &that) = default;

    fixed32(int16_t that)
    {

    }


    operator int32_t ()
    {
        return
    }


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
