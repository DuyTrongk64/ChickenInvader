#include "MainMenuState.h"

void MainMenuState::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/logo.jpg"))
	{
		std::cout << "ERROR::GameState::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::intKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["PLAY_VS_AI"] = new Buttons(325, 300, 150, 50, &this->font, "Play vs AI");
	this->buttons["CHALLENGE"] = new Buttons(325, 400, 150, 50, &this->font, "Challenge");
	this->buttons["EXIT"] = new Buttons(325, 500, 150, 50, &this->font, "Quit");
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Handler* handler)
	:State(window,supportedKeys,states,handler)
{
	this->initFonts();
	this->intKeybinds();
	this->initButtons();
	this->initWorld();
	//this->initSocket();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();

	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::endState()
{
	std::cout << "End menu state" << "\n";
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["PLAY_VS_AI"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys,this->states,this->handler));
	}
	if (this->buttons["EXIT"]->isPressed())
	{
		this->quit=true;
	}
}

void MainMenuState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeybinds(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->worldBackground);

	this->renderButtons(target);
}

