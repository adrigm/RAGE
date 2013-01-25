#include <RAGE/Core/ConvexShape.hpp>


namespace ra
{
////////////////////////////////////////////////////////////
ConvexShape::ConvexShape(unsigned int pointCount)
{
    setPointCount(pointCount);
}


////////////////////////////////////////////////////////////
void ConvexShape::setPointCount(unsigned int count)
{
    m_points.resize(count);
    update();
}


////////////////////////////////////////////////////////////
unsigned int ConvexShape::getPointCount() const
{
    return static_cast<unsigned int>(m_points.size());
}


////////////////////////////////////////////////////////////
void ConvexShape::setPoint(unsigned int index, const sf::Vector2f& point)
{
    m_points[index] = point;
    update();
}


////////////////////////////////////////////////////////////
sf::Vector2f ConvexShape::getPoint(unsigned int index) const
{
    return m_points[index];
}

} // namespace ra
