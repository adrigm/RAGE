#ifndef RAGE_CORE_CONVEXSHAPE_HPP
#define RAGE_CORE_CONVEXSHAPE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Shape.hpp>
#include <vector>


namespace ra
{
////////////////////////////////////////////////////////////
/// \brief Specialized shape representing a convex polygon
///
////////////////////////////////////////////////////////////
class RAGE_CORE_API ConvexShape : public ra::Shape
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param pointCount Number of points of the polygon
    ///
    ////////////////////////////////////////////////////////////
    explicit ConvexShape(unsigned int pointCount = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Set the number of points of the polygon
    ///
    /// \a count must be greater than 2 to define a valid shape.
    ///
    /// \param count New number of points of the polygon
    ///
    /// \see getPointCount
    ///
    ////////////////////////////////////////////////////////////
    void setPointCount(unsigned int count);

    ////////////////////////////////////////////////////////////
    /// \brief Get the number of points of the polygon
    ///
    /// \return Number of points of the polygon
    ///
    /// \see setPointCount
    ///
    ////////////////////////////////////////////////////////////
    virtual unsigned int getPointCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Set the position of a point
    ///
    /// Don't forget that the polygon must remain convex, and
    /// the points need to stay ordered!
    /// setPointCount must be called first in order to set the total
    /// number of points. The result is undefined if \a index is out
    /// of the valid range.
    ///
    /// \param index Index of the point to change, in range [0 .. getPointCount() - 1]
    /// \param point New position of the point
    ///
    /// \see getPoint
    ///
    ////////////////////////////////////////////////////////////
    void setPoint(unsigned int index, const sf::Vector2f& point);

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of a point
    ///
    /// The result is undefined if \a index is out of the valid range.
    ///
    /// \param index Index of the point to get, in range [0 .. getPointCount() - 1]
    ///
    /// \return Position of the index-th point of the polygon
    ///
    /// \see setPoint
    ///
    ////////////////////////////////////////////////////////////
    virtual sf::Vector2f getPoint(unsigned int index) const;

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<sf::Vector2f> m_points; ///< Points composing the convex polygon
};

} // namespace ra


#endif // RAGE_CORE_CONVEXSHAPE_HPP