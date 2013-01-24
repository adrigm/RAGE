#include <SFML/Graphics.hpp>
#include "SceneMain.hpp"
#include <iostream>

SceneMain::SceneMain(ra::SceneID theID) :
	ra::Scene(theID)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	this->SetBackgroundColor(sf::Color(180, 200, 255));
	ra::AssetManager* am = ra::AssetManager::Instance();
	am->SetPath("Data");
}

void SceneMain::Update()
{
}

void SceneMain::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
	}
}

void SceneMain::Resume()
{
}

void SceneMain::Pause()
{
}

void SceneMain::Cleanup()
{
}