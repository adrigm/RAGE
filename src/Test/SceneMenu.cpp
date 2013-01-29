#include <SFML/Graphics.hpp>
#include "SceneMenu.hpp"
#include <iostream> // Quitar

SceneMenu::SceneMenu(ra::SceneID theID) :
	ra::Scene(theID)
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Init()
{
	app = ra::App::Instance();
	sm = ra::SceneManager::Instance();
	am = ra::AssetManager::Instance();
	cam = ra::Camera::Instance();

	this->SetBackgroundColor(sf::Color(125, 255, 200));
}

void SceneMenu::Update()
{
}

void SceneMenu::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
		sm->SetActiveScene("Main");
	}
}

void SceneMenu::Resume()
{
	back.setTexture(*am->GetTexture("captura"));
	this->AddGraph(back);
	std::cout << "Resume" << std::endl;
	sm->SetActiveScene("Main");
}

void SceneMenu::Pause()
{
}

void SceneMenu::Cleanup()
{
}