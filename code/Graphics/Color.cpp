#include "Graphics/Color.h"

namespace GRAPHICS
{
    /// Constructor accepting all color components.
    /// @param[in]  red - The red component of the color.
    /// @param[in]  green - The green component of the color.
    /// @param[in]  blue - The blue component of the color.
    /// @param[in]  alpha - The alpha component of the color.
    Color::Color(
        const float red,
        const float green,
        const float blue,
        const float alpha) :
    Red(red),
    Green(green),
    Blue(blue),
    Alpha(alpha)
    {}
}
