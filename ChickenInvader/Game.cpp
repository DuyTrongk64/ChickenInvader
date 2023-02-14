#include "Game.h"

extern conn_msg_type conn_msg;
extern char username[20];
extern char password[20];
extern int bytes_received;
extern int bytes_sent;
extern int client_sock;

//Initializer functions
void Game::initVariables()
{
	this->window = NULL;

	this->dt = 0.f;

	this->gridSize = 64.f;
}


void Game::initWindow()
{
	this->window = new sf::RenderWindow (sf::VideoMode(800, 600), "test state", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	//DEBUG REMOVE LATER!
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}



void Game::initStates()
{
	this->states.push(new LoginState(this->window,&this->supportedKeys, &this->states));
}

//Constructors/Destructors
Game::Game()
{
	this->initVariables();
	
	this->initWindow();
	this->initKeys();
	
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}


void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/

	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	//Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render items
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

int main()
{
	LoginState* Login;
	Game game;
	game.run();
	

	connect_to_server();
	
	
	/*strcpy(username, Login->getUsername().c_str());
	str_trim_lf(username, strlen(username));
	strcpy(password, Login->getPassword().c_str());
	str_trim_lf(password, strlen(password));

	Login->updateButtons(login(username, password));*/
}