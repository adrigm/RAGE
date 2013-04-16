#ifndef RAGE_CORE_SCENEOBJECT_HPP
#define RAGE_CORE_SCENEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Config.hpp>

namespace ra
{

class RAGE_CORE_API SceneObject : public sf::Transformable, public sf::Drawable
{
public:
	SceneObject();
	virtual ~SceneObject();

	Int32 GetZOrder() const;
	void SetZOrder(Int32 z);

	bool IsVisible() const;
	void Show();
	void Hide();

	virtual sf::FloatRect getLocalBounds() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;

private:
	/// Representa el orden de dibujado entre mayor más cerca de la cámara
	Int32 m_ZOrder;
	/// Verdadero si el Objeto es visible
	bool m_visible;
};

} // namespace ra

#endif // RAGE_CORE_SCENEOBJECT_HPP