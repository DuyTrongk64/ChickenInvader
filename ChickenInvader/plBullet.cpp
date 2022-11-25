#include "plBullet.h"

plBullet::plBullet()
{

}

plBullet::plBullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);

	this->damage = 5;
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->shape.setScale(0.5f, 0.5f);
}

plBullet::~plBullet()
{

}

const sf::FloatRect plBullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& plBullet::getDamage() const
{
	return this->damage;
}

void plBullet::update()
{
	//Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void plBullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
