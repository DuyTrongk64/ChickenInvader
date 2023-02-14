#include "State.h"


State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Handler* handler)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->handler = handler;
	this->quit = false;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::initSocket()
{
	this->handler = new Handler();
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
