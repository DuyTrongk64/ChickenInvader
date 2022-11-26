#include "Chickens.h"


void Checkens::initVariables()
{
	this->pointCount = 5;
	this->type = 0;
	this->speed = 0.1f;
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	
	this->points = this->pointCount;
}

void Checkens::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/chicken.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Checkens::initSprite(const sf::RenderWindow& window)
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.1f, 0.1f);

	this->sprite.setPosition(sf::Vector2f(static_cast<float>(rand() % (window.getSize().x - (int)this->sprite.getGlobalBounds().width) + 0.f), 0.f));
	
}



Checkens::Checkens(const sf::RenderWindow& window)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(window);
}

Checkens::~Checkens()
{

}

//Accessors
const sf::FloatRect Checkens::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Checkens::getPoints() const
{
	return this->points;
}

const int& Checkens::getDamage() const
{
	return this->damage;
}

void Checkens::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Checkens::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

const sf::Vector2f& Checkens::getPos() const
{
	return this->sprite.getPosition();
}
//Functions
void Checkens::update()
{
	this->sprite.move(0.f, this->speed);
}

void Checkens::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
