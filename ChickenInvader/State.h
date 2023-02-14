#ifndef STATE_H
#define STATE_H

#include"Player.h"
#include"plBullet.h"
#include"Chickens.h"
#include"ckBullets.h"
#include"lib.h"
#include"Handler.h"


class State
{
protected:
	
	std::vector<sf::Texture> textures;
	bool quit;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	Handler* handler;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
public:

	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Handler* handler);
	virtual ~State();

	const bool& getQuit() const;
	virtual void initSocket();
	virtual void checkForQuit();
	virtual void endState() = 0;
	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif