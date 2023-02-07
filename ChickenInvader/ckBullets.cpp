#include "ckBullets.h"


ckBullets::ckBullets()
{

}

ckBullets::ckBullets(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->sprite.setTexture(*texture);

	this->damage = 50;
	this->sprite.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->sprite.setScale(0.5f, 0.5f);
}

ckBullets::~ckBullets()
{

}

const sf::FloatRect ckBullets::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& ckBullets::getDamage() const
{
	return this->damage;
}

float ckBullets::getTimer()const {
	return Timer.getElapsedTime().asSeconds();
}


void ckBullets::update()
{
	//Movement
	this->sprite.move(this->movementSpeed * this->direction);
}

void ckBullets::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
