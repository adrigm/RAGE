#ifndef RAGE_CORE_CAMERA_HPP
#define RAGE_CORE_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>

namespace ra
{

class Camera : public sf::View
{
public:
	Camera();

	~Camera();

	void update();
	void setDefaultCamera();

private:
	friend class App;
	App* m_app;
}; // class Camera

} // namespace ra

#endif // RAGE_CORE_CAMERA_HPP