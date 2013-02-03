#ifndef SCENE_TETRIS
#define SCENE_TETRIS

#include <RAGE\Core.hpp>

class SceneTetris : public ra::Scene
{
public:
	SceneTetris(ra::SceneID theID);
	~SceneTetris();

	void Init() ;

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

}; // SceneMain

#endif // SCENE_TETRIS