#include "SceneMenu.hpp"
#include <iostream> // Quitar

SceneMenu::SceneMenu(ra::SceneID ID)
	: ra::Scene(ID)
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::init()
{
	this->setBackgroundColor(sf::Color(180, 255, 205));
}

void SceneMenu::active()
{
}

void SceneMenu::desactive()
{
}

void SceneMenu::update()
{
}

void SceneMenu::event(sf::Event theEvent)
{
	if (theEvent.KeyPressed && theEvent.key.code == sf::Keyboard::A)
	{
		ra::SceneManager::instance()->setActiveScene("Game");
	}
}

void SceneMenu::resume()
{
}

void SceneMenu::pause()
{
}

void SceneMenu::cleanup()
{
}