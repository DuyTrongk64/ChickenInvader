#include "GameState.h"



GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Handler* handler)
	: State(window,supportedKeys,states,handler)
{
	//this->initWindow();
	this->initTextures();
	this->initWorld();
	this->initGUI();
	
	this->initSystems();

	this->initPlayer();
	this->initCheckens();
	//this->initSocket();
	//this->run();
}

GameState::~GameState()
{
	//delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete plBullets
	for (auto* i : this->plBullets)
	{
		delete i;
	}

	//Delete ckBullets
	for (auto* i : this->ckBullet)
	{
		delete i;
	}

	//Delete chickens
	for (auto* i : this->chickens)
	{
		delete i;
	}

}

//Private functions

void GameState::initTextures()
{
	this->textures["plBULLET"] = new sf::Texture();
	this->textures["plBULLET"]->loadFromFile("Textures/bullet.png");

	this->textures["ckBULLET"] = new sf::Texture();
	this->textures["ckBULLET"]->loadFromFile("Textures/egg.png");
}

void GameState::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GameState::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::Red);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f - 60);

	this->text["PLAY_AGAIN"].setFont(this->font);
	this->text["PLAY_AGAIN"].setCharacterSize(60);
	this->text["PLAY_AGAIN"].setFillColor(sf::Color::White);
	this->text["PLAY_AGAIN"].setString("Play again");
	this->text["PLAY_AGAIN"].setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f +20);

	this->text["EXIT"].setFont(this->font);
	this->text["EXIT"].setCharacterSize(60);
	this->text["EXIT"].setFillColor(sf::Color::White);
	this->text["EXIT"].setString("Exit");
	this->text["EXIT"].setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f + 100);

	

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void GameState::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "ERROR::GameState::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void GameState::initSystems()
{
	this->points = 0;
}

void GameState::initPlayer()
{
	this->player = new Player();
	this->player->setPosition((this->window->getSize().x - this->player->getBounds().width) / 2, (this->window->getSize().y - this->player->getBounds().height));
}

void GameState::initCheckens()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void GameState::initckBullets()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer1 = this->spawnTimerMax;
}
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}
void GameState::endState()
{
	std::cout << "End game" << "\n";
}

void GameState::updateKeybinds()
{
	this->checkForQuit();
}

//Functions
void GameState::run()
{

	this->updateKeybinds();

	this->updateText();
	while (1)
	{
		if (this->player->getHp() > 0)
			this->update(this->dt);
		if (this->player->getHp() < 0)
		{
			handler->sendPoint(this->points);
		}
	}
	
;
	/*if (this->time.getElapsedTime().asSeconds() > 5)
		this->window->close();*/

	this->render();
}



void GameState::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->plBullets.push_back(
			new plBullet(
				this->textures["plBULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y, 0.f, -1.f, 5.f)
		);
	}
}

void GameState::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void GameState::updateText()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->text["PLAY_AGAIN"].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window))))
		{
			this->text["PLAY_AGAIN"].setFillColor(sf::Color::Red);
			
		}

		if (this->text["EXIT"].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window))))
		{
			this->text["EXIT"].setFillColor(sf::Color::Red);
			std::cout << "quit game\n";
			this->quit = true;
		}
	}
}

void GameState::updateWorld()
{

}

void GameState::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void GameState::updateplBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->plBullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->plBullets.at(counter);
			this->plBullets.erase(this->plBullets.begin() + counter);
		}

		++counter;
	}
}

void GameState::updateckBullet()
{
	unsigned counter = 0;
	for (auto* bullet : this->ckBullet)
	{
		bullet->update();

		//Enemy player collision
		if (bullet->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->ckBullet.at(counter)->getDamage());
			delete this->ckBullet.at(counter);
			this->ckBullet.erase(this->ckBullet.begin() + counter);
		}

		/*
		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->plBullets.at(counter);
			this->ckBullet.erase(this->ckBullet.begin() + counter);
		}
		*/
		++counter;
	}
}

void GameState::updateCheckens()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->chickens.push_back(new Checkens(*this->window));
		this->spawnTimer = 0.f;

	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->chickens)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->chickens.at(counter);
			this->chickens.erase(this->chickens.begin() + counter);
		}


		//Spawning
		this->spawnTimer += 0.1f;
		if (this->spawnTimer >= this->spawnTimerMax)
		{
			this->ckBullet.push_back(
				new ckBullets(
					this->textures["ckBULLET"],
					enemy->getPos().x + enemy->getBounds().width / 2.f - 8.f,
					enemy->getPos().y + enemy->getBounds().height / 2.f, 0.f, 1.f, 1.f)
			);
			this->spawnTimer = 0.f;

		}
		++counter;
	}
}

void GameState::updateCombat()
{
	for (int i = 0; i < this->chickens.size(); ++i)
	{


		bool enemy_deleted = false;
		for (size_t k = 0; k < this->plBullets.size() && enemy_deleted == false; k++)
		{


			if (this->chickens[i]->getBounds().intersects(this->plBullets[k]->getBounds()))
			{
				this->points += this->chickens[i]->getPoints();

				delete this->chickens[i];
				this->chickens.erase(this->chickens.begin() + i);

				delete this->plBullets[k];
				this->plBullets.erase(this->plBullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void GameState::update(const float& dt)
{
	this->updateKeybinds();
	this->updateText();

	if(this->player->getHp() > 0)
	{
		this->updateInput();

		this->player->update();

		this->updateCollision();

		this->updateplBullets();

		this->updateckBullet();

		this->updateCheckens();

		this->updateCombat();

		this->updateGUI();

		this->updateWorld();
		this->updateMousePositions();
		
	}
}

void GameState::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void GameState::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	


	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*target);


	for (auto* bullet : this->plBullets)
	{
		bullet->render(target);
	}

	for (auto* ckBullet : this->ckBullet)
	{
		ckBullet->render(target);
	}

	for (auto* enemy : this->chickens)
	{
		enemy->render(target);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
	{
		target->draw(this->gameOverText);
		
		target->draw(this->text["PLAY_AGAIN"]);

		target->draw(this->text["EXIT"]);
	}

}
