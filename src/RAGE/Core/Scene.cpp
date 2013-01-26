#include <RAGE/Core/Scene.hpp>
#include <RAGE/Core/SceneGraph.hpp>
#include <RAGE/Core/Camera.hpp>

namespace ra
{

struct ObjectZComparator
{
	bool operator()(const ra::SceneGraph* o1, const ra::SceneGraph* o2) const
    {
		return o1->GetZOrder() < o2->GetZOrder();
    }
};

Scene::Scene(SceneID theID)
	: m_ID(theID)
	, m_init(false)
	, m_paused(false)
	, m_cleanup(false)
	, m_colorBack(0, 0, 0)
	, m_camera(ra::Camera::Instance())
{
	m_app = ra::App::Instance();
	m_app->log << "Scene::ctor() con ID: " << theID << " creada" << std::endl;
}

Scene::~Scene()
{
	m_app->log << "Scene::dtor() con ID: " << GetID() << " eliminada" << std::endl;
}

const SceneID Scene::GetID() const
{
	return m_ID;
}

const bool Scene::IsInitComplete() const
{
	return m_init;
}

const bool Scene::IsPaused() const
{
	return m_paused;
}

void Scene::SetBackgroundColor(const sf::Color &theColor)
{
	m_colorBack = theColor;
}

void Scene::Draw()
{
	// Establecemos el color de fondo
	m_app->window.clear(m_colorBack);

	// Ordenamos la lista de objetos en base a su Z
	m_sceneGraph.sort(ObjectZComparator());

	// Recorremos la lista de Actores de la escena para dibujarla
	std::list<ra::SceneGraph*>::const_iterator element;
	for(element = m_sceneGraph.begin(); element != m_sceneGraph.end(); element++)
	{
		ra::SceneGraph* object = *element;

		if (object->IsVisible() && m_camera->GetRect().intersects(object->getGlobalBounds()))
		{
			m_app->window.draw(*object);
		}
	}
}

void Scene::AddObject(ra::SceneGraph* theGraph)
{
	std::list<ra::SceneGraph*>::const_iterator it;
	it = std::find(m_sceneGraph.begin(), m_sceneGraph.end(), theGraph);
	if (it == m_sceneGraph.end())
		m_sceneGraph.push_back(theGraph);
}

void Scene::QuitObject(ra::SceneGraph* theGraph)
{
	m_sceneGraph.remove(theGraph);
}

void Scene::DeleteObject(ra::SceneGraph* theGraph)
{
	m_sceneGraph.remove(theGraph);
	delete theGraph;
}

void Scene::AddObjects(const std::vector<ra::SceneGraph*>& theList)
{
	std::vector<ra::SceneGraph*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		AddObject(*it);
	}
}

void Scene::QuitObjects(const std::vector<ra::SceneGraph*>& theList)
{
	std::vector<ra::SceneGraph*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		QuitObject(*it);
	}
}

void Scene::DeleteObjects(const std::vector<ra::SceneGraph*>& theList)
{
	std::vector<ra::SceneGraph*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		DeleteObject(*it);
	}
}


}; // namespace ra