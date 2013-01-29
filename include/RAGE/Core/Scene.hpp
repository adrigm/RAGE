#ifndef RAGE_CORE_SCENE_HPP
#define RAGE_CORE_SCENE_HPP

#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Core_types.hpp>
#include <RAGE/Core/App.hpp>
#include <list>

namespace ra
{

class RAGE_CORE_API Scene
{
public:
	/**
	 * Scene Destructor
	 */
	virtual ~Scene();

	/**
	 * Devuelve el identificador único de la escena
	 *
	 * @return GGE::SceneID el ID de la escena
	 */
	const SceneID GetID() const;

	/**
	 * Devuelve true si el Init() ya ha sido llamado
	 */
	const bool IsInitComplete() const;

	void SetBackgroundColor(const sf::Color &theColor);

	/**
	 * Devuelve true si la escena está pausada
	 */
	const bool IsPaused() const;

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Event(sf::Event theEvent) = 0;

	virtual void Resume() = 0;

	virtual void Pause() = 0;

	virtual void Draw();

	virtual void Cleanup() = 0;

	void AddGraph(ra::SceneGraph& theGraph);
	void QuitGraph(ra::SceneGraph& theGraph);
	void DeleteGraph(ra::SceneGraph& theGraph);

protected:
	/// Puntero a la aplicación padre
	ra::App* m_app;

	/**
	 * Constructor de la escena
	 * 
	 * @param m_id Cadena de texto que establece un identificador único
	 */
	Scene(SceneID theID);


private:
	// Puntero a la camara
	ra::Camera *m_camera;
	/// Representa el id único de la escena
	const SceneID m_ID;
	/// Comprueba si cleanup debe ser llamado
	bool m_cleanup;
	/// Comprueba si la escena está inicializada
	bool m_init;
	/// Comprueba si la escena está pausada
	bool m_paused;
	/// Color de fondo de la escena
	sf::Color m_colorBack;
	/// Lista de Actores a dibujar
	std::list<ra::SceneGraph*> m_sceneGraph;

}; // class Scene

} // namespace ra

#endif // RAGE_CORE_SCENE_HPP