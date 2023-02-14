#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "LoginState.h"

class Game
{
private:
	//Variables
	
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;
	Handler* handler;

	float gridSize;

	bool inmain = true;

	
	//Initialization
	void initVariables();
	
	void initWindow();
	void initKeys();

	void initStates();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();
	
	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif