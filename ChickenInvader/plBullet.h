#ifndef plBullet_H
#define plBullet_H

#include "lib.h"

class plBullet
{
protected:

	sf::Sprite shape;

	sf::Vector2f direction;

	int damage;
	float movementSpeed;

public:
	plBullet();
	plBullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~plBullet();

	//Accessor
	const sf::FloatRect getBounds() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !plBullet_H