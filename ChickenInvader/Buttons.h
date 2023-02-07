#ifndef BUTTONS_H
#define BUTTONS_H


#include "lib.h"


enum button_states{BTN_IDLE=0,BTN_HOVER,BTN_ACTIVE};
class Buttons
{
protected:
	short unsigned buttonState;
	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

public:
	Buttons(float x, float y, float witdth, float height, sf::Font* font, std::string text);
	~Buttons();

	//accessor
	const bool isPressed() const;
	void setText(std::string text);
	void setTextSize(int size);
	//functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

#endif // !BUTTONS_H