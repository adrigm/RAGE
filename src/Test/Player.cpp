#include "Player.hpp"

Player::Player()
	: ra::Actor()
{
	m_status = Q_DOWN;
	m_speed = sf::Vector2f(10, 10);

	setTexture(*ra::AssetManager::instance()->getTexture("sprite.png"));
	SetFramesByGrid(4, 4);

	AddAnimation("down", ra::Animation(1, 4, 8));
	AddAnimation("up", ra::Animation(13, 16, 8));
	AddAnimation("left", ra::Animation(5, 8, 8));
	AddAnimation("right", ra::Animation(9, 12, 8));
	AddAnimation("q_down", ra::Animation(1, 1, 1));
	AddAnimation("q_up", ra::Animation(13, 13, 1));
	AddAnimation("q_left", ra::Animation(5, 5, 1));
	AddAnimation("q_right", ra::Animation(9, 9, 1));
	SetActiveAnimation("up");
}

void Player::update()
{
	switch (m_status)
	{
	case DOWN:
		break;
	case UP:
		break;
	case LEFT:
		break;
	case RIGHT:
		break;
	case Q_DOWN:
		break;
	case Q_UP:
		break;
	case Q_LEFT:
		break;
	case Q_RIGHT:
		break;
	}

	this->Animate();
}
