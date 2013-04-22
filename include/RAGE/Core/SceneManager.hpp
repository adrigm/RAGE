#ifndef RAGE_CORE_SCENEMANAGER_HPP
#define RAGE_CORE_SCENEMANAGER_HPP

#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Scene.hpp>

namespace ra
{

class RAGE_CORE_API SceneManager
{
	static SceneManager* m_instance;

public:
	static SceneManager* instance();

	static void release();

	/**
	 * Añade una escena a la pila de escenas inactivas
	 *
	 * Solo añade una escena a la pila, no la inicializa
	 *
	 * @param theScene Puntero a la escena que vamos a añadir
	 */
	void addScene(Scene* theScene);


	/**
	 * Establece la escena indicada como activa
	 *
	 * Establece la escena como activa si se encuentra en la pila y llama a su
	 * Init() si no ha sido llamado. Cambia la escena al final del ciclo
	 *
	 * @param theSceneID Cadena única que identifica a la escena
	 */
	void setActiveScene(SceneID theSceneID);

	/**
	 * Elimina una escena de la pila, no puede ser la escena activa
	 *
	 * Se encarga de llamar a su método Cleanup y de eliminarla de la memoria
	 *
	 * @param theSceneID Cadena única que identifica a la escena
	 */
	void removeScene(SceneID theSceneID);

	/**
	 * Elimina todas las escenas inactivas
	 */
	void removeAllInactiveScene();

private:
	App* m_app;
	// Declaramos la clase App friend
	friend class App;
	/// Escena actualmente activa
	Scene* m_activeScene;
	/// Próxima escena activa
	SceneID m_nextScene;
	// Lista de escenas inacticas
	std::map<SceneID, Scene*> m_inactivesScenes;

	SceneManager();
	SceneManager(const SceneManager&);
	SceneManager& operator=(const SceneManager&);
	~SceneManager();

	/**
	 * Cambia la escena activa inmediatamente. USAR SetActiveScene() para
	 * cambiar de escena
	 *
	 * @param id_scene ID de la escena a cambiar
	 */
	void changeScene(SceneID theSceneID);

	/**
	 * Elimina todas las escenas de la pila.
	 *
	 * Elimina todas las escenas incluso la escena activa, se encarga de llamar
	 * a los métodos Cleanup() de las escenas y de eleminarlas de la memoria
	 */
	void removeAllScene();

	/**
	 * Llama el método Event() de la escena activa
	 *
	 * @param theEvent representa a un evento del sistema
	 */
	void eventScene(sf::Event theEvent);

	/**
	 * Llama el método Draw() de la escena activa
	 */
	void drawScene();

	/**
	 * Llama al método Update() de la escena activa
	 */
	void updateScene();

	/**
	 * Llama al método Resume de la escena activa
	 */
	void resumeScene();

	/**
	 * Llama al método Pause de la escena activa
	 */
	void pauseScene();

	bool handleChangeScene();

}; // class SceneManager

} // namespace ra

#endif // RAGE_CORE_SCENEMANAGER_HPP