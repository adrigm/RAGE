#ifndef RAGE_CORE_SCENE_MANAGER_HPP
#define RAGE_CORE_SCENE_MANAGER_HPP

#include <map>
#include <SFML/Window.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Core_types.hpp>

namespace ra
{

class RAGE_CORE_API SceneManager
{
	static SceneManager* ms_instance;

public:
	static SceneManager* Instance();

	static void Release();

/**
	 * Añade una escena a la pila de escenas inactivas
	 *
	 * Solo añade una escena a la pila, no la inicializa
	 *
	 * @param theScene Puntero a la escena que vamos a añadir
	 */
	void AddScene(Scene* theScene);


	/**
	 * Establece la escena indicada como activa
	 *
	 * Establece la escena como activa si se encuentra en la pila y llama a su
	 * Init() si no ha sido llamado. Cambia la escena al final del ciclo
	 *
	 * @param theSceneID Cadena única que identifica a la escena
	 */
	void SetActiveScene(SceneID theSceneID);

	/**
	 * Elimina una escena de la pila, no puede ser la escena activa
	 *
	 * Se encarga de llamar a su método Cleanup y de eliminarla de la memoria
	 *
	 * @param theSceneID Cadena única que identifica a la escena
	 */
	void RemoveScene(SceneID theSceneID);

	/**
	 * Elimina todas las escenas inactivas
	 */
	void RemoveAllInactiveScene();

protected:
	// Puntero a la aplicación
	ra::App* m_app;

private:
	// Declaramos la clase App friend
	friend class ra::App;
	/// Escena actualmente activa
	Scene* mActiveScene;
	/// Próxima escena activa
	SceneID mNextScene;
	// Lista de escenas inacticas
	std::map<SceneID, Scene*> mInactivesScenes;

	/**
	 * Cambia la escena activa inmediatamente. USAR SetActiveScene() para
	 * cambiar de escena
	 *
	 * @param id_scene ID de la escena a cambiar
	 */
	void ChangeScene(SceneID theSceneID);

	/**
	 * Elimina todas las escenas de la pila.
	 *
	 * Elimina todas las escenas incluso la escena activa, se encarga de llamar
	 * a los métodos Cleanup() de las escenas y de eleminarlas de la memoria
	 */
	void RemoveAllScene();

	/**
	 * Llama el método Event() de la escena activa
	 *
	 * @param theEvent representa a un evento del sistema
	 */
	void EventScene(sf::Event theEvent);

	/**
	 * Llama el método Draw() de la escena activa
	 */
	void DrawScene();

	/**
	 * Llama al método Update() de la escena activa
	 */
	void UpdateScene();

	/**
	 * Llama al método Resume de la escena activa
	 */
	void ResumeScene();

	/**
	 * Llama al método Pause de la escena activa
	 */
	void PauseScene();

	bool HandleChangeScene(); 

	SceneManager();
	~SceneManager();

}; // class SceneManager

} // namespace ra

#endif // RAGE_CORE_SCENE_MANAGER_HPP