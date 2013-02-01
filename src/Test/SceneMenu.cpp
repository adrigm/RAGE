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
	Scene::Init();

	app = ra::App::Instance();
	sm = ra::SceneManager::Instance();
	am = ra::AssetManager::Instance();
	cam = ra::Camera::Instance();

	this->SetBackgroundColor(sf::Color(125, 255, 200));

	pause.setFont(*am->GetFont("segoeui.ttf"));
	pause.setCharacterSize(50);
	pause.setString("PAUSA");
	pause.setOrigin(pause.getLocalBounds().width/2.0f, pause.getLocalBounds().height/2.0f);
	pause.setPosition(app->window.getSize().x/2.0f, app->window.getSize().y/2.0f);
	pause.setColor(sf::Color::Magenta);
	pause.SetZOrder(10);

	this->AddGraph(pause);
}

void SceneMenu::Active()
{
	back.setTexture(*am->GetTexture("captura"));
	this->AddGraph(back);
}

void SceneMenu::Update()
{
	//std::cout << app->GetTotalTime().asSeconds() << std::endl; 
}

void SceneMenu::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
		this->Resume();
	}
}

void SceneMenu::Resume()
{
	std::cout << "Resume" << std::endl;
	sm->SetActiveScene("Main");
}

void SceneMenu::Pause()
{
}

void SceneMenu::Cleanup()
{
}