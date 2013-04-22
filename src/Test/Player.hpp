#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <RAGE/Core.hpp>
#include <SFML/System.hpp>

enum Status { DOWN, UP, LEFT, RIGHT, Q_DOWN, Q_UP, Q_LEFT, Q_RIGHT};

class Player : public ra::Actor
{
public:
	Player();

	void update();

private:
	sf::Vector2f m_speed;
	Status m_status;
}; // class Player

#endif // PLAYER_HPP