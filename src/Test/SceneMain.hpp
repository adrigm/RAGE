#ifndef SCENE_MAIN
#define SCENE_MAIN

#include <RAGE\Core.hpp>

class SceneMain : public ra::Scene
{
public:
	SceneMain(ra::SceneID theID);
	~SceneMain();

	void Init();

	void Active();

	void Update() ;

	void Event(sf::Event theEvent) ;

	void Resume();

	void Pause();

	virtual void Cleanup() ;

private:
	ra::App* app;
	ra::SceneManager* sm;
	ra::AssetManager* am;
	ra::Camera* cam;
	ra::CircleShape a;
	ra::CircleShape b;
	ra::CircleShape c;

	float time;
}; // SceneMain

#endif // SCENE_MAIN