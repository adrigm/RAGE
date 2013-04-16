#ifndef SCENE_GAME_HPP
#define SCENE_GAME_HPP

#include <SFML/Window.hpp>
#include <RAGE/Core.hpp>
#include <vector>

class SceneGame : public ra::Scene
{
public:
	SceneGame(ra::SceneID ID);
	~SceneGame();

	void init();

	void active();

	void desactive();

	void update();

	void event(sf::Event theEvent);

	void resume();

	void pause() ;

	void cleanup();
private:
	ra::Sprite sp;
	ra::Text tx;
	ra::RectangleShape r;
	ra::CircleShape c;
	std::vector<ra::Sprite*> l;
}; // class SceneGame

#endif // SCENE_GAME_HPP