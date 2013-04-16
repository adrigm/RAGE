#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

#include <SFML/Window.hpp>
#include <RAGE/Core.hpp>

class SceneMenu : public ra::Scene
{
public:
	SceneMenu(ra::SceneID ID);
	~SceneMenu();

	void init();

	void active();

	void desactive();

	void update();

	void event(sf::Event theEvent);

	void resume();

	void pause() ;

	void cleanup();

private:

}; // class SceneMenu

#endif // SCENE_MENU_HPP