#pragma once

#include <array>
#include "Graphics/Color.h"
#include "Graphics/Object3D.h"

namespace GRAPHICS
{
    class Triangle
    {
    public:
        static Object3D CreateEquilateral(const Color& color);
        static Object3D CreateEquilateral(
            const Color& top_center_color,
            const Color& bottom_right_color,
            const Color& bottom_left_color);
    };
}
