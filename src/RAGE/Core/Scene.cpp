#include <RAGE/Core/Scene.hpp>
#include <RAGE/Core/App.hpp>
#include <RAGE/Core/SceneObject.hpp>
#include <iostream> // Quitar

namespace ra
{

struct ObjectZComparator
{
	bool operator()(const ra::SceneObject* o1, const ra::SceneObject* o2) const
    {
		return o1->GetZOrder() < o2->GetZOrder();
    }
};

Scene::Scene(SceneID ID)
{
	m_app = App::instance();
	m_ID = ID;
}

Scene::~Scene()
{
}

const SceneID& Scene::getID() const
{
	return m_ID;
}

void Scene::setBackgroundColor(const sf::Color &color)
{
	m_colorBack = color;
}

App* Scene::getApp()
{
	return m_app;
}

void Scene::draw()
{
	// Establecemos el color de fondo
	m_app->getWindow().clear(m_colorBack);

	// Ordenamos la lista de objetos en base a su Z
	m_sceneObjects.sort(ObjectZComparator());

	// Recorremos la lista de Actores de la escena para dibujarla
	for(m_objectsIter = m_sceneObjects.begin(); m_objectsIter != m_sceneObjects.end(); m_objectsIter++)
	{
		if ((*m_objectsIter)->IsVisible() && m_app->getCamera().getRect().intersects((*m_objectsIter)->getGlobalBounds()))
		{
			m_app->getWindow().draw(**m_objectsIter);
		}
	}
}

void Scene::addObject(SceneObject& object)
{
	m_objectsIter = std::find(m_sceneObjects.begin(), m_sceneObjects.end(), &object);
	if (m_objectsIter == m_sceneObjects.end())
		m_sceneObjects.push_back(&object);
}

void Scene::quitObject(SceneObject& object)
{
	m_sceneObjects.remove(&object);
}

void Scene::deleteObject(SceneObject& object)
{
	m_sceneObjects.remove(&object);
	delete &object;
}

}