#include <RAGE/Core/SceneManager.hpp>
#include <RAGE/Core/App.hpp>

namespace ra
{

SceneManager* SceneManager::m_instance = 0;

SceneManager* SceneManager::instance()
{
	if (m_instance == 0)
		m_instance = new SceneManager();
	return m_instance;
}

void SceneManager::release()
{
	if(m_instance)
		delete m_instance;
	m_instance = 0;
}


SceneManager::SceneManager() :
	m_app(NULL),
	m_activeScene(NULL),
	m_inactivesScenes(),
	m_nextScene("")
{
	m_app = App::instance();
	m_app->getLog() << "SceneManager::ctor()" << std::endl;
}

SceneManager::~SceneManager()
{
	m_app->getLog() << "SceneManager::dtor()" << std::endl;
}

void SceneManager::addScene(Scene* theScene)
{
	std::map<SceneID, Scene*>::const_iterator it = m_inactivesScenes.find(theScene->getID());
	if (it != m_inactivesScenes.end())
	{
		// Si ya existe la escena salimos
			m_app->getLog() << "SceneManager::AddScene() ya existe una escena con ID=" 
				<< theScene->getID() << std::endl; 
			return;
	}

	// Si no existe la añadimos a la lista
	m_inactivesScenes[theScene->getID()] = theScene;

	// Inicializamos la escena
	theScene->init();

	m_app->getLog() << "SceneManager::AddScene() Añadida escena con ID=" 
		<< theScene->getID() << std::endl;
}

void SceneManager::setActiveScene(SceneID theSceneID)
{
	std::map<SceneID, Scene*>::const_iterator it = m_inactivesScenes.find(theSceneID);
	if (it != m_inactivesScenes.end())
	{
		m_nextScene = theSceneID;
		return;
	}

	if (theSceneID == m_activeScene->getID())
	{
		m_app->getLog() << "SceneManager::SetActiveScene() la escena con ID=" <<  m_activeScene->getID()
			<< "ya esta activa" << std::endl;
		return;
	}

	m_app->getLog() << "SceneManager::SetActiveScene() No existe ninguna escena con ID=" 
		<< theSceneID << std::endl;
}

void SceneManager::changeScene(SceneID theSceneID)
{

	m_nextScene = "";
	if (m_activeScene != NULL)
	{
		m_activeScene->desactive();
		m_inactivesScenes[m_activeScene->getID()] = m_activeScene;
	}
	m_activeScene = m_inactivesScenes[theSceneID];
	m_inactivesScenes.erase(theSceneID);

	m_activeScene->active();

	m_app->getLog() << "SceneManager::ChangeScene() Activa escena con ID=" << theSceneID << std::endl;
}

void SceneManager::removeScene(SceneID theSceneID)
{
	// Buscamos en la lista de escenas inactivas
	std::map<SceneID, Scene*>::iterator it = m_inactivesScenes.find(theSceneID);
	if (it != m_inactivesScenes.end())
	{
		m_app->getLog() << "SceneManager::RemoveScene() Eliminada escena con ID=" 
			<< it->first << std::endl;
		it->second->cleanup();
		delete it->second;
		m_inactivesScenes.erase(it);
		return;
	}

	if (theSceneID == m_activeScene->getID())
	{
		m_app->getLog() << "SceneManager::RemoveScene() la escena con ID=" << m_activeScene->getID() 
			<< "esta activa y no se puede eliminar" << std::endl;
		return;
	}

	m_app->getLog() << "SceneManager::RemoveScene() No existe ninguna escena con ID=" 
		<< theSceneID << std::endl;
}

void SceneManager::removeAllInactiveScene()
{
	// Recorremos la lista de escenas inactivas
	std::map<SceneID, Scene*>::iterator it = m_inactivesScenes.begin();
	while(it != m_inactivesScenes.end())
	{
		m_app->getLog() << "SceneManager::RemoveAllInactiveScene() Eliminada escena con ID=" 
			<< it->first << std::endl;
		it->second->cleanup();
		delete it->second;
		m_inactivesScenes.erase(it++);
	}
}

void SceneManager::removeAllScene()
{
	// Eliminamos todas las escenas inactivas
	removeAllInactiveScene();

	if (m_activeScene != NULL)
	{
		// Eliminamos la escena activa
		m_app->getLog() << "SceneManager::RemoveAllScene() Eliminada escena con ID=" 
			<< m_activeScene->getID() << std::endl;
		m_activeScene->cleanup();
		delete m_activeScene;
		m_activeScene = NULL;
	}
}

void SceneManager::eventScene(sf::Event theEvent)
{
	m_activeScene->event(theEvent);
}

void SceneManager::updateScene()
{
	m_activeScene->update();
}

void SceneManager::drawScene()
{
	m_activeScene->draw();
}

void SceneManager::resumeScene()
{
	m_activeScene->resume();
}

void SceneManager::pauseScene()
{
	m_activeScene->pause();
}

bool SceneManager::handleChangeScene()
{
	if (m_nextScene == "")
	{
		return false;
	}
	return true;
}

} // namespace ra