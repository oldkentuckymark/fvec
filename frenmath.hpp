#pragma once

#include <cmath>
#include <cstdint>
#include <numbers>

namespace fren::math
{

class fixed32   //16.16
{
    static constexpr int32_t FIX_SHIFT = 16;
    static constexpr int32_t FIX_SCALE = 65536;
    static constexpr float FIX_SCALEF = 65536.0f;

public:
    int32_t data;

    constexpr fixed32() = default;
    constexpr fixed32(fixed32 const &that) = default;
    constexpr auto operator = (fixed32 const &that) -> fixed32& = default;

    constexpr explicit fixed32(int16_t that) : data(that << FIX_SHIFT)
    {

    }

    constexpr explicit fixed32(uint16_t that) : data(that << FIX_SHIFT)
    {

    }

    constexpr explicit fixed32(float const that) : data(that*FIX_SCALE)
    {

    }

    constexpr auto operator = (int16_t const that) -> fixed32&
    {
        data = that << FIX_SHIFT;
        return (*this);
    }

    constexpr auto operator = (float const that) -> fixed32&
    {
        data = (that*FIX_SCALE);
        return (*this);
    }

    constexpr explicit operator int32_t () const
    {
        return data / FIX_SCALE;
    }

    constexpr explicit operator int16_t () const
    {
        return data / FIX_SCALE;
    }

    constexpr explicit operator float () const
    {
        return data / FIX_SCALEF;
    }

    constexpr auto operator + (fixed32 const that) const -> fixed32
    {
        fixed32 r;
        r.data = data + that.data;
        return r;
    }

    constexpr auto operator - (fixed32 const that) const -> fixed32
    {
        fixed32 r;
        r.data = data - that.data;
        return r;
    }

    constexpr auto operator * (fixed32 const that) const -> fixed32
    {
        fixed32 r;
        r.data = (int64_t(data) * that.data) >> FIX_SHIFT;
        return r;
    }

    constexpr auto operator / (fixed32 const that) const -> fixed32
    {
        fixed32 r;
        r.data = (int64_t(data) * FIX_SCALE) / (that.data);
        return r;
    }

    constexpr auto operator-() const -> fixed32
    {
        fixed32 r;
        r.data = this->data * -1;
        return r;
    }

    constexpr auto operator<=>(fixed32 const & that) const -> std::strong_ordering
    {
        return this->data <=> that.data;
    }


};

constexpr auto sqrt(fixed32 const n) -> fixed32
{
    return static_cast<fixed32>(std::sqrtf(static_cast<float>(n)));
}

constexpr auto sin(fixed32 const n) -> fixed32
{
    return static_cast<fixed32>(std::sinf(static_cast<float>(n)));
}

constexpr auto cos(fixed32 const n) -> fixed32
{
    return static_cast<fixed32>(std::cosf(static_cast<float>(n)));
}

template<class T, std::size_t S, auto FUNC>
constexpr auto makeTable() -> std::array<T, S>
{
    std::array<T,S> r{};
    for(std::size_t i = 0; i < S; ++i)
    {
        r[i] = FUNC(i);
    }
    return r;
}


class vec2
{
public:
    fixed32 x,y;

    constexpr auto operator + (vec2 const & that) const -> vec2
    {
        return {x+that.x, y+that.y};
    }

    constexpr auto operator - (vec2 const & that) const -> vec2
    {
        return {x-that.x, y-that.y};
    }

    constexpr auto operator * (fixed32 const & that) const -> vec2
    {
        return {x*that,y*that};
    }

    constexpr auto operator / (fixed32 const & that) const -> vec2
    {
        return {x/that,y/that};
    }

    [[nodiscard]] constexpr auto length() const -> fixed32
    {
        const auto x2 = x*x;
        const auto y2 = y*y;
        const auto sum = x2+y2;
        return sqrt(sum);
    }

    auto operator[](uint8_t const p) -> fixed32&
    {
        return *((&(this->x)) + p);

    }
};

class vec3 : public vec2
{
public:
    fixed32 z;

    constexpr auto operator + (vec3 const & that) -> vec3
    {
        return {this->x+that.x, this->y+that.y, z+that.x};
    }

    constexpr auto operator - (vec3 const & that) -> vec3
    {
        return {this->x-that.x, this->y-that.y, z-that.x};
    }

    constexpr auto operator * (fixed32 const & that) -> vec3
    {
        return {this->x*that,this->y*that,this->z*that};
    }

    constexpr auto operator / (fixed32 const & that) -> vec3
    {
        return {this->x/that,this->y/that,this->z/that};
    }

    constexpr auto operator * (vec3 const & that) -> fixed32
    {
        return { (this->x*that.x) + (this->y*that.y) + (this->z*that.z) };
    }

    [[nodiscard]] constexpr auto length() const -> fixed32
    {
        const auto x2 = x*x;
        const auto y2 = y*y;
        const auto z2 = z*z;
        const auto sum = x2+y2+z2;
        return sqrt(sum);
    }
};

class vec4 : public vec3
{
public:
    fixed32 w;

    constexpr auto operator + (vec4 const & that) const -> vec4
    {
        return {this->x+that.x, this->y+that.y, z+that.x, w+that.w};
    }

    constexpr auto operator - (vec4 const & that) const -> vec4
    {
        return {this->x-that.x, this->y-that.y, z-that.x, w-that.w};
    }

    constexpr auto operator * (fixed32 const & that) const -> vec4
    {
        return {this->x*that,this->y*that,this->z*that,w*that};
    }

    constexpr auto operator / (fixed32 const & that) const -> vec4
    {
        return {this->x/that,this->y/that,this->z/that,w/that};
    }

    constexpr auto operator * (vec4 const & that) const -> fixed32
    {
        return { (this->x*that.x) + (this->y*that.y) + (this->z*that.z) + (this->w*that.w) };
    }

    [[nodiscard]] constexpr auto length() const -> fixed32
    {
        const auto x2 = x*x;
        const auto y2 = y*y;
        const auto z2 = z*z;
        const auto w2 = w*w;
        const auto sum = x2+y2+z2+w2;
        return sqrt(sum);
    }

};

class mat4
{
public:
    fixed32 m[4][4];

    constexpr auto operator + (mat4 const & that) -> mat4
    {
        mat4 n;

        for(uint8_t c = 0; c < 4; ++c)
        {
            for(uint8_t r = 0; r < 4; ++r)
            {
                n.m[c][r] = this->m[c][r] + that.m[c][r];
            }
        }

        return n;
    }
};

constexpr math::fixed32 operator""_fx(long double f)
{
    math::fixed32 r(static_cast<float>(f));
    return r;
}


auto mix(auto x, auto y, auto a) -> auto
{
    return x * (1.0_fx - a) + y * a;
}

constexpr fixed32 PI = 3.14159265_fx;

}


