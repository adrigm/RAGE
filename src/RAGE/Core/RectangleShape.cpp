////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <RAGE/Core/RectangleShape.hpp>
#include <cmath>


namespace ra
{
////////////////////////////////////////////////////////////
RectangleShape::RectangleShape(const sf::Vector2f& size)
{
    setSize(size);
}


////////////////////////////////////////////////////////////
void RectangleShape::setSize(const sf::Vector2f& size)
{
    m_size = size;
    update();
}


////////////////////////////////////////////////////////////
const sf::Vector2f& RectangleShape::getSize() const
{
    return m_size;
}


////////////////////////////////////////////////////////////
unsigned int RectangleShape::getPointCount() const
{
    return 4;
}


////////////////////////////////////////////////////////////
sf::Vector2f RectangleShape::getPoint(unsigned int index) const
{
    switch (index)
    {
        default:
        case 0: return sf::Vector2f(0, 0);
        case 1: return sf::Vector2f(m_size.x, 0);
        case 2: return sf::Vector2f(m_size.x, m_size.y);
        case 3: return sf::Vector2f(0, m_size.y);
    }
}

} // namespace ra
