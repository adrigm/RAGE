#ifndef RAGE_CORE_CAMERA_HPP
#define RAGE_CORE_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>

namespace ra
{

class App;

class Camera : public sf::View
{
public:
	Camera();

	~Camera();

	void update();
	void setDefaultCamera();

	sf::FloatRect getRect() const;

private:
	friend App;
	App* m_app;
}; // class Camera

} // namespace ra

#endif // RAGE_CORE_CAMERA_HPP
