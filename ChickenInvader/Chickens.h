#ifndef Checkens_H
#define Checkens_H

#include "lib.h"



class Checkens
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned pointCount;
	

	//Animation
	sf::IntRect currentFrame;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initTexture();
	void initSprite(const sf::RenderWindow& window);
	void initAnimations();

public:
	Checkens(const sf::RenderWindow& window);
	virtual ~Checkens();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	const sf::Vector2f& getPos() const;

	//Modifier
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	//Functions
	void updateAnimations();
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!Checkens_H