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
	cam = ra::Camera::Instance();
	am->SetPath("Data");

	sp.setTexture(*am->GetTexture("indiana.png"));
	tx.setFont(*am->GetFont("segoeui.ttf"));
	tx.setCharacterSize(20);
	tx.setString("RAGE App");
	tx.setColor(sf::Color(255, 255, 220));
	tx.setPosition(100, 200);
	cir.setRadius(40);
	cir.setPosition(200, 300);
	cir.setFillColor(sf::Color(255, 0, 0));
	cir.setOutlineColor(sf::Color(0, 255, 0));
	cir.setOutlineThickness(4);
	rect.setPosition(254, 458);
	rect.setSize(sf::Vector2f(100, 40));
	polygon.setPointCount(3);
	polygon.setPoint(0, sf::Vector2f(0, 0));
	polygon.setPoint(1, sf::Vector2f(0, 10));
	polygon.setPoint(2, sf::Vector2f(25, 5));
	polygon.setOutlineColor(sf::Color::Magenta);
	polygon.setOutlineThickness(-5);
	polygon.setPosition(10, 20);

}

void SceneMain::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
	}
}

void SceneMain::Event(sf::Event theEvent)
{
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
	if (cam->GetRect().intersects(sp.getLocalBounds()))
	{
		m_app->window.draw(sp);
	}
	else
	{
		std::cout << "No me dibujo\n";
	}
	m_app->window.draw(tx);
	m_app->window.draw(cir);
	m_app->window.draw(rect);
	m_app->window.draw(polygon);
}