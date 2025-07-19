#pragma once

#include <cstdint>
#include <array>
#include <cmath>

namespace fren
{


constexpr auto Convert888to555(uint8_t const r, uint8_t const g, uint8_t const b) -> uint16_t
{
    return (((r >> 3) & 31) |
            (((g >> 3) & 31) << 5) |
            (((b >> 3) & 31) << 10) );

}

constexpr auto Convert555to888(uint16_t color) -> std::array<uint8_t, 4>
{
    uint8_t const red = (color & 31) << 3;
    uint8_t const green = ((color >> 5) & 31) << 3;
    uint8_t const blue = ((color >> 10) & 31) << 3;
    uint8_t const alpha = 255;
    return {red,green,blue,alpha};
}

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

    constexpr operator int32_t () const
    {
        return data / FIX_SCALE;
    }

    constexpr operator int16_t () const
    {
        return data / FIX_SCALE;
    }

    constexpr operator float () const
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

    constexpr auto operator + (vec4 const & that) -> vec4
    {
        return {this->x+that.x, this->y+that.y, z+that.x, w+that.w};
    }

    constexpr auto operator - (vec4 const & that) -> vec4
    {
        return {this->x-that.x, this->y-that.y, z-that.x, w-that.w};
    }

    constexpr auto operator * (fixed32 const & that) -> vec4
    {
        return {this->x*that,this->y*that,this->z*that,w*that};
    }

    constexpr auto operator / (fixed32 const & that) -> vec4
    {
        return {this->x/that,this->y/that,this->z/that,w/that};
    }

    constexpr auto operator * (vec4 const & that) -> fixed32
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
};


class Context
{
public:


    //Context() = delete;
    Context(Context&) = delete;
    Context(Context&&) = delete;
    auto operator = (Context&) -> Context& = delete;
    auto operator = (Context&&) -> Context& = delete;

    Context()
    {
    }

    virtual ~Context()
    {

    }

    void setVertexFunction(vec3 (*func)(vec3))
    {
        vertex_function_ = func;
    }

    void setVertexPointer(uint8_t size, uint8_t stride, fixed32* pointer)
    {

    }

    void SetColorPointer(uint8_t stride, uint16_t* pointer)
    {

    }

    void setIndexPointer(uint8_t* pointer)
    {

    }



    virtual void clear()
    {

    }

    virtual void present()
    {

    }

    virtual void plot(uint16_t x, uint16_t y, uint16_t c)
    {

    }



private:
    vec3 (*vertex_function_)(vec3){};

    fixed32* vertex_pointer_{};

    uint16_t* color_pointer_{};

    uint8_t* index_pointer_{};


    /*
def Render(p, phi, height, horizon, scale_height, distance, screen_width, screen_height):
    # precalculate viewing angle parameters
    var sinphi = math.sin(phi);
    var cosphi = math.cos(phi);

    # initialize visibility array. Y position for each column on screen
    ybuffer = np.zeros(screen_width)
    for i in range(0, screen_width):
        ybuffer[i] = screen_height

    # Draw from front to the back (low z coordinate to high z coordinate)
    dz = 1.
    z = 1.
    while z < distance
        # Find line on map. This calculation corresponds to a field of view of 90°
        pleft = Point(
            (-cosphi*z - sinphi*z) + p.x,
            ( sinphi*z - cosphi*z) + p.y)
        pright = Point(
            ( cosphi*z - sinphi*z) + p.x,
            (-sinphi*z - cosphi*z) + p.y)

        # segment the line
        dx = (pright.x - pleft.x) / screen_width
        dy = (pright.y - pleft.y) / screen_width

        # Raster line and draw a vertical line for each segment
        for i in range(0, screen_width):
            height_on_screen = (height - heightmap[pleft.x, pleft.y]) / z * scale_height. + horizon
            DrawVerticalLine(i, height_on_screen, ybuffer[i], colormap[pleft.x, pleft.y])
            if height_on_screen < ybuffer[i]:
                ybuffer[i] = height_on_screen
            pleft.x += dx
            pleft.y += dy

        # Go to next line and increase step size when you are far away
        z += dz
        dz += 0.2

# Call the render function with the camera parameters:
# position, viewing angle, height, horizon line position,
# scaling factor for the height, the largest distance,
# screen width and the screen height parameter
Render( Point(0, 0), 0, 50, 120, 120, 300, 800, 600 )

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    int16_t dx = std::abs(x1 - x0);
    int16_t dy = std::abs(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;

    while (true)
    {
        plot(x0, y0);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        int16_t e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}




*/

};



}
