#include <RAGE/Core/Camera.hpp>

namespace ra
{

Camera* Camera::ms_instance = 0;

Camera* Camera::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new Camera();
	}
	return ms_instance;
}

void Camera::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}

Camera::Camera()
	: m_app(ra::App::Instance())
	, m_conectToGraph(false)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
}

void Camera::ConnectToGraph(ra::SceneGraph& theGraph)
{
	m_graph = &theGraph;
	m_conectToGraph = true;
}

void Camera::DisconnectToSprite()
{
	m_conectToGraph = false;
	m_graph = 0;
}

/*void Camera::LockToMap(GGE::Map& theMap)
{
	mMap = &theMap;
	mConectToMap = true;
}*/

void Camera::SetDefaultCamera()
{
	this->reset(sf::FloatRect(
				0, 
				0, 
				static_cast<float>(m_app->window.getSize().x), 
				static_cast<float>(m_app->window.getSize().y)));
	this->DisconnectToSprite();
}

sf::FloatRect Camera::GetRect() const
{
	sf::FloatRect rect;
	rect.left = this->getCenter().x - this->getSize().x / 2.0f;
	rect.top = this->getCenter().y - this->getSize().y / 2.0f;
	rect.width = this->getSize().x;
	rect.height = this->getSize().y;
	return rect;
}

} // Namespace GGE