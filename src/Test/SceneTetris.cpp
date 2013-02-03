#include <SFML/Graphics.hpp>
#include "SceneTetris.hpp"
#include <iostream> // Quitar

SceneTetris::SceneTetris(ra::SceneID theID) :
	ra::Scene(theID)
{
}

SceneTetris::~SceneTetris()
{
}

void SceneTetris::Init()
{
	Scene::Init();

	app = ra::App::Instance();
	sm = ra::SceneManager::Instance();
	am = ra::AssetManager::Instance();
	cam = ra::Camera::Instance();

	this->SetBackgroundColor(sf::Color(125, 255, 200));
}

void SceneTetris::Active()
{

}

void SceneTetris::Update()
{
	//std::cout << app->GetTotalTime().asSeconds() << std::endl; 
}

void SceneTetris::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
	}
}

void SceneTetris::Resume()
{
}

void SceneTetris::Pause()
{
}

void SceneTetris::Cleanup()
{
}