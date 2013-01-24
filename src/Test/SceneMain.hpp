#ifndef SCENE_MAIN
#define SCENE_MAIN

#include <RAGE\Core.hpp>

class SceneMain : public ra::Scene
{
public:
	SceneMain(ra::SceneID theID);
	~SceneMain();

	virtual void Init() ;

	virtual void Update() ;

	virtual void Event(sf::Event theEvent) ;

	virtual void Resume();

	virtual void Pause();

	virtual void Cleanup() ;

private:
}; // SceneMain

#endif // SCENE_MAIN