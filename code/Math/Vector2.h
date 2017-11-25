#pragma once

/// Holds code related to math.
namespace MATH
{
    /// A 2D mathematical vector with both magnitude and direction.
    /// It currently only has the minimal functionality needed,
    /// so it cannot directly perform all common vector operations.
    ///
    /// The ComponentType template parameter is intended to be replaced with
    /// any numerical type that is typically used for vectors (int, float, etc.).
    template <typename ComponentType>
    class Vector2
    {
    public:
        // CONSTRUCTION.
        explicit Vector2(const ComponentType x = 0, const ComponentType y = 0);

        // OPERATORS.
        bool operator== (const Vector2& rhs) const;
        bool operator!= (const Vector2& rhs) const;
        Vector2 operator- (const Vector2& rhs) const;

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The x component of the vector.
        ComponentType X;
        /// The y component of the vector.
        ComponentType Y;
    };

    // DEFINE COMMON VECTOR2 TYPES.
    /// A vector composed of 2 unsigned integer components.
    typedef Vector2<unsigned int> Vector2ui;
    /// A vector composed of 2 float components.
    typedef Vector2<float> Vector2f;

    /// Constructor that accepts initial values.
    /// @param[in]  x - The x component value.
    /// @param[in]  y - The y component value.
    template <typename ComponentType>
    Vector2<ComponentType>::Vector2(const ComponentType x, const ComponentType y) : 
        X(x), 
        Y(y)
    {};

    /// Equality operator.  Direct equality comparison is used for components,
    /// so the precision of components types should be considered when using
    /// this operator.
    /// @param[in]  rhs - The vector on the right-hand side of the operator.
    /// @return True if the vectors are equal; false otherwise.
    template <typename ComponentType>
    bool Vector2<ComponentType>::operator== (const Vector2<ComponentType>& rhs) const
    {
        bool x_component_matches = (this->X == rhs.X);
        bool y_component_matches = (this->Y == rhs.Y);

        bool both_components_match = (x_component_matches && y_component_matches);
        return both_components_match;
    }

    /// Inequality operator.  Direct equality comparison is used for components,
    /// so the precision of components types should be considered when using
    /// this operator.
    /// @param[in]  rhs - The vector on the right-hand side of the operator.
    /// @return True if the vectors are unequal; false otherwise.
    template <typename ComponentType>
    bool Vector2<ComponentType>::operator!= (const Vector2<ComponentType>& rhs) const
    {
        bool vectors_equal = ((*this) == rhs);
        return !vectors_equal;
    }

    /// Subtraction operator.
    /// @param[in]  rhs - The vector on the right-hand side of the operator to
    ///     subtract from this vector.
    /// @return A new vector created by subtracting the provided vector from this vector.
    template <typename ComponentType>
    Vector2<ComponentType> Vector2<ComponentType>::operator- (const Vector2<ComponentType>& rhs) const
    {
        MATH::Vector2f resulting_vector;
        resulting_vector.X = this->X - rhs.X;
        resulting_vector.Y = this->Y - rhs.Y;
        return resulting_vector;
    }
}