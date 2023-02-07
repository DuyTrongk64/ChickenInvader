#ifndef ckBullets_H
#define ckBullets_H

#include "lib.h"
class ckBullets
{
protected:
	sf::Sprite sprite;

	sf::Vector2f direction;
	sf::Clock Timer;

	int damage;
	float movementSpeed;


public:
	ckBullets();
	ckBullets(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~ckBullets();

	//Accessor
	const sf::FloatRect getBounds() const;
	const int& getDamage() const;
	float getTimer() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !ckBullets_H