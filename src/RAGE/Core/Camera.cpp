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

} // namespace ra