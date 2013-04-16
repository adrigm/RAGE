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

	ra::SceneManager* sm = getApp()->getSceneManager();
	ra::AssetManager* am = getApp()->getAssetManager();

	am->setPath("Data");
	sm->addScene(new SceneMenu("Menu"));

	sp.setTexture(*am->getTexture("sprite.png"));
	this->addObject(sp);

	ra::ConfigReader *f = am->getConfig("../window.cfg");
	int a = f->getUint32("window", "bpp", 0);


	ra::Tmx::Map map;
	map.ParseFile("Data/pueblo.tmx");
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
		getApp()->getCamera().move(-5, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		getApp()->getCamera().move(5, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		getApp()->getCamera().move(0, -5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		getApp()->getCamera().move(0, 5);

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
			getApp()->getSceneManager()->setActiveScene("Menu");
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