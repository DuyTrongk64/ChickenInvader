#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "lib.h"
#include "Buttons.h"
#include "State.h"

class GameState :
    public State
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Texture*> textures2;
	std::vector<plBullet*> plBullets;
	std::vector<ckBullets*> ckBullet;
	std::map<std::string, Buttons*> buttons;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;
	

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
	void initWindow();
	void initTextures();
	void initButtons();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initCheckens();
	void initckBullets();
    void initKeybinds();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions
    void endState();

    void updateKeybinds();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateplBullets();
	void updateckBullet();
	void updateCheckens();
	void updateCombat();
	void updateButtons();
	void update(const float& dt);


    //virtual void update(const float& dt);
	void renderGUI();
	void renderButtons(sf::RenderTarget* target);
	void renderWorld();
	void render(sf::RenderTarget* target = NULL);
    //virtual void render(sf::RenderTarget* target = nullptr);
};

#endif // !GAMESTATE_H