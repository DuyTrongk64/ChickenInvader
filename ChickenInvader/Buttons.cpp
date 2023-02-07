#include "Buttons.h"

Buttons::Buttons(float x, float y, float witdth, float height, sf::Font* font, std::string text)
{
	this->buttonState = BTN_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(witdth, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(16);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
		);
	this->shape.setFillColor(sf::Color::Black);
}

Buttons::~Buttons()
{
}

const bool Buttons::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE) return true;
	
	return false;
}

void Buttons::setText(std::string text)
{
	this->text.setString(text);
}

void Buttons::setTextSize(int size)
{
	this->text.setCharacterSize(size);
}

void Buttons::update(sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
}

void Buttons::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
