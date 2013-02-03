#ifndef SCENE_MENU
#define SCENE_MENU

#include <RAGE\Core.hpp>

class SceneMenu : public ra::Scene
{
public:
	SceneMenu(ra::SceneID theID);
	~SceneMenu();

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
	ra::Text pause;
	ra::Sprite back;
}; // SceneMenu

#endif // SCENE_MENU