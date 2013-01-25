#include <SFML/Graphics.hpp>
#include "SceneMain.hpp"
#include <iostream> // Quitar

SceneMain::SceneMain(ra::SceneID theID) :
	ra::Scene(theID)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	app = ra::App::Instance();
	sm = ra::SceneManager::Instance();
	am = ra::AssetManager::Instance();
	am->SetPath("Data");
	sp.setTexture(*am->GetTexture("indiana.png"));
}

void SceneMain::Update()
{
	std::cout << app->GetTotalTime().asSeconds() << std::endl;
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

void SceneMain::Draw()
{
	m_app->window.clear(sf::Color(145, 204, 220));
	m_app->window.draw(sp);
}