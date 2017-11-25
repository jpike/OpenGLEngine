#pragma once

namespace GRAPHICS
{
    /// Represents an RGBA color.
    /// Components are floating point with a range [0,1].
    /// A default color represents an opaque black color.
    class Color
    {
    public:
        // CONSTRUCTION.
        explicit Color(
            const float red = 0.0f,
            const float green = 0.0f,
            const float blue = 0.0f,
            const float alpha = 1.0f);

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The red component of the color.
        float Red = 0.0f;
        /// The green component of the color.
        float Green = 0.0f;
        /// The blue component of the color.
        float Blue = 0.0f;
        /// The alpha component of the color.
        float Alpha = 1.0f;
    };
}
