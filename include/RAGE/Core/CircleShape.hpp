#ifndef RAGE_CORE_CIRCLESHAPE_HPP
#define RAGE_CORE_CIRCLESHAPE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Shape.hpp>


namespace ra
{
////////////////////////////////////////////////////////////
/// \brief Specialized shape representing a circle
///
////////////////////////////////////////////////////////////
class RAGE_CORE_API CircleShape : public ra::Shape
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param radius     Radius of the circle
    /// \param pointCount Number of points composing the circle
    ///
    ////////////////////////////////////////////////////////////
    explicit CircleShape(float radius = 0, unsigned int pointCount = 30);

    ////////////////////////////////////////////////////////////
    /// \brief Set the radius of the circle
    ///
    /// \param radius New radius of the circle
    ///
    /// \see getRadius
    ///
    ////////////////////////////////////////////////////////////
    void setRadius(float radius);

    ////////////////////////////////////////////////////////////
    /// \brief Get the radius of the circle
    ///
    /// \return Radius of the circle
    ///
    /// \see setRadius
    ///
    ////////////////////////////////////////////////////////////
    float getRadius() const;

    ////////////////////////////////////////////////////////////
    /// \brief Set the number of points of the circle
    ///
    /// \param count New number of points of the circle
    ///
    /// \see getPointCount
    ///
    ////////////////////////////////////////////////////////////
    void setPointCount(unsigned int count);

    ////////////////////////////////////////////////////////////
    /// \brief Get the number of points of the shape
    ///
    /// \return Number of points of the shape
    ///
    /// \see setPointCount
    ///
    ////////////////////////////////////////////////////////////
    virtual unsigned int getPointCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get a point of the shape
    ///
    /// The result is undefined if \a index is out of the valid range.
    ///
    /// \param index Index of the point to get, in range [0 .. getPointCount() - 1]
    ///
    /// \return Index-th point of the shape
    ///
    ////////////////////////////////////////////////////////////
    virtual sf::Vector2f getPoint(unsigned int index) const;

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    float        m_radius;     ///< Radius of the circle
    unsigned int m_pointCount; ///< Number of points composing the circle
};

} // namespace ra


#endif // RAGE_CORE_CIRCLESHAPE_HPP