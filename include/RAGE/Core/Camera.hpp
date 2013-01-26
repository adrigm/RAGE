#ifndef RAGE_CORE_CAMERA_HPP
#define RAGE_CORE_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/App.hpp>

namespace ra
{

class RAGE_CORE_API Camera : public sf::View
{
	static Camera* ms_instance;

public:
	static Camera* Instance();
	static void Release();

	void Update();

	void ConnectToGraph(ra::SceneGraph& theGraph);
	void DisconnectToSprite();

	//void LockToMap(GGE::Map& theMap);

	void SetDefaultCamera();

	sf::FloatRect GetRect() const;

private:
	/// Puntero a App
	App* m_app;
	/// Puntero al Sprite conectado
	ra::SceneGraph* m_graph;
	/// Puntero al Mapa conectado
	//GGE::Map* mMap;
	/// Dice si la Cámara está conectada a un Sprite
	bool m_conectToGraph;
	/// Dice si la Cámara está conectada a un mapa
	//bool mConectToMap;

	Camera();
	virtual ~Camera();

}; // Class Camera

} // Namespace ra

#endif // RAGE_CORE_CAMERA_HPP