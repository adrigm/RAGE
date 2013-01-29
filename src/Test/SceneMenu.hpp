#ifndef SCENE_MENU
#define SCENE_MENU

#include <RAGE\Core.hpp>

class SceneMenu : public ra::Scene
{
public:
	SceneMenu(ra::SceneID theID);
	~SceneMenu();

	void Init() ;

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

	ra::Sprite back;
}; // SceneMain

#endif // SCENE_MENU