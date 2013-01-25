#ifndef SCENE_MAIN
#define SCENE_MAIN

#include <RAGE\Core.hpp>

class SceneMain : public ra::Scene
{
public:
	SceneMain(ra::SceneID theID);
	~SceneMain();

	void Init() ;

	void Update() ;

	void Event(sf::Event theEvent) ;

	void Resume();

	void Pause();

	void Draw();

	virtual void Cleanup() ;

private:
	ra::App* app;
	ra::SceneManager* sm;
	ra::AssetManager* am;
	ra::Sprite sp;
	ra::Text tx;
	ra::CircleShape cir;
	ra::RectangleShape rect;
	ra::ConvexShape polygon;
}; // SceneMain

#endif // SCENE_MAIN