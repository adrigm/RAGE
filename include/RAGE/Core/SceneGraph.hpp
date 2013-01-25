#ifndef RAGE_CORE_SCENE_GRAPH_HPP
#define RAGE_CORE_SCENE_GRAPH_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Config.hpp>

namespace ra
{

class RAGE_CORE_API SceneGraph : public sf::Drawable, public sf::Transformable
{
public:
	SceneGraph();
	virtual ~SceneGraph();

	ra::Int32 GetZOrder() const;
	void SetZOrder(ra::Int32 z);

	bool IsVisible() const;
	void Show();
	void Hide();

	virtual sf::FloatRect getLocalBounds() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;

private:
	/// Representa el orden de dibujado entre mayor más cerca de la cámara
	ra::Int32 m_ZOrder;
	/// Verdadero si el Objeto es visible
	bool m_visible;
}; // SceneGraph

} // namespace ra

#endif // RAGE_CORE_SCENE_GRAPH_HPP