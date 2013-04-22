#include "SceneGame.hpp"
#include "SceneMenu.hpp"
#include <iostream> // Quitar

SceneGame::SceneGame(ra::SceneID ID)
	: ra::Scene(ID)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::init()
{
	this->setBackgroundColor(sf::Color(180, 200, 255));

	sm = ra::SceneManager::instance();
	am = ra::AssetManager::instance();

	sm->addScene(new SceneMenu("Menu"));

	this->addObject(player);
}

void SceneGame::active()
{
}

void SceneGame::desactive()
{
}

void SceneGame::update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	}

	player.update();

	sf::FloatRect r = getApp()->getCamera().getRect();
	//std::cout << r.left << ", " << r.top << ", " << r.width << ", " << r.height << std::endl;
	//std::cout << r.intersects(sp.getGlobalBounds()) << std::endl;
}

void SceneGame::event(sf::Event theEvent)
{
	if (theEvent.KeyPressed)
	{
		switch (theEvent.key.code)
		{
		case sf::Keyboard::Space:
			sm->setActiveScene("Menu");
			break;
		case sf::Keyboard::Subtract:
			//tx.SetZOrder(tx.GetZOrder() - 1);
			break;
		case sf::Keyboard::Add:
			//tx.SetZOrder(tx.GetZOrder() + 1);
			break;
		}
	}
}

void SceneGame::resume()
{
}

void SceneGame::pause()
{
}

void SceneGame::cleanup()
{
}