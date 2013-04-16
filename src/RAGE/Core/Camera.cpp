#include <RAGE/Core/Camera.hpp>
#include <RAGE/Core/App.hpp>

namespace ra
{

Camera::Camera()
	: m_app(App::instance())
{
}

Camera::~Camera()
{
}

void Camera::update()
{
}

void Camera::setDefaultCamera()
{
	this->reset(sf::FloatRect(
				0, 
				0, 
				static_cast<float>(m_app->getWindow().getSize().x), 
				static_cast<float>(m_app->getWindow().getSize().y)));
}

sf::FloatRect Camera::getRect() const
{
	sf::FloatRect r;
	r.left = this->getCenter().x - this->getSize().x / 2.0f;
	r.top = this->getCenter().y - this->getSize().y / 2.0f;
	r.width = this->getSize().x;
	r.height = this->getSize().y;
	return r;
}

} // namespace ra