#ifndef SingleGameState_H
#define SingleGameState_H

#include "lib.h"

#include "Buttons.h"
#include "State.h"
#include "LoginState.h"

class SingleGameState :
	public State
{
private:
	//Resources
	std::map<std::string, sf::Texture*> textures;

	std::vector<plBullet*> plBullets;
	std::vector<ckBullets*> ckBullet;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Sprite sprite;
	sf::Text gameOverText;

	std::map<std::string, sf::Text> text;

	sf::Clock time;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;
	float dt;

	//Player
	Player* player;
	//Checkens* chickens;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Checkens*> chickens;

	float spawnTimer1;
	float spawnTimerMax1;
	//Private functions

	void initTextures();

	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initCheckens();
	void initckBullets();
	void initKeybinds();

public:
	SingleGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Handler* handler);
	virtual ~SingleGameState();

	//Functions
	void endState();

	void updateKeybinds();

	//Functions
	void run();

	void updateInput();
	void updateGUI();
	void updateText();
	void updateWorld();
	void updateCollision();
	void updateplBullets();
	void updateckBullet();
	void updateCheckens();
	void updateCombat();

	virtual void update(const float& dt);

	void renderGUI();
	void renderWorld();
	virtual void render(sf::RenderTarget* target = NULL);

};

#endif // !SingleGameState_H