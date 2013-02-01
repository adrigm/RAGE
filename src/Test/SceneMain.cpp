#include <SFML/Graphics.hpp>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"
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
	Scene::Init();

	app = ra::App::Instance();
	sm = ra::SceneManager::Instance();
	am = ra::AssetManager::Instance();
	cam = ra::Camera::Instance();
	am->SetPath("Data");

	this->SetBackgroundColor(sf::Color(180, 200, 255));

	a.setPosition(100, 100);
	a.setRadius(50);
	a.setFillColor(sf::Color(255, 0, 0));

	b.setPosition(100, 250);
	b.setRadius(50);
	b.setFillColor(sf::Color(0, 0, 255));

	c.setRadius(50);
	c.setOrigin(c.getRadius(), c.getRadius());
	c.setPosition(0, 0);
	c.setFillColor(sf::Color(0, 255, 0));

	this->AddGraph(a);
	this->AddGraph(b);
	this->AddGraph(c);

	time = 0.0f;

	sm->AddScene(new SceneMenu("Menu"));
}

void SceneMain::Active()
{
}

void SceneMain::Update()
{
	time += app->GetUpdateTime().asSeconds();

	std::cout << time << std::endl;
	
	if (time <= 10.0f)
	{
		a.move(200*app->GetUpdateTime().asSeconds(), 0);
		b.move(200*app->GetUpdateTime().asSeconds(), 0);
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cam->move(-5.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cam->move(5.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cam->move(0.f, -5.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cam->move(0.f, 5.f);
	}*/
}

void SceneMain::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
		this->Pause();
	}
}

void SceneMain::Resume()
{
	std::cout << "Resume" << std::endl;
}

void SceneMain::Pause()
{
	std::cout << "Pausa" << std::endl;
	sm->SetActiveScene("Menu");

	sf::Texture *t = new sf::Texture();
	t->create(app->window.getSize().x, app->window.getSize().y); 
	t->update(app->window);

	am->DeleteTexture("captura");
	am->GetTexture("captura", t);

	/*am->DeleteTexture("captura");
	sf::Image *cap_img = new sf::Image(app->window.capture());
	am->GetTextureFromImage("captura", cap_img);*/
}

void SceneMain::Cleanup()
{
}