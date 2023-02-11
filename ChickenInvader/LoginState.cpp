#include "LoginState.h"


void LoginState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::LoginState::COULD NOT LOAD FONT");
	}
}

void LoginState::intKeybinds()
{
	std::ifstream ifs("Config/LoginState_keybinds.ini");

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

void LoginState::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/logo.jpg"))
	{
		std::cout << "ERROR::GameState::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void LoginState::initTextbox(std::string text)
{
	sf::RenderWindow create(sf::VideoMode(400, 200, 32), "Enter a new " + text);
	
	mine.setFont(font);
	mine.setCharacterSize(25);
	mine.setString(text);
	mine.setPosition(create.getSize().x / 2 - 7 * mine.getString().getSize(), 50);
	
	this->yours.setFont(font);
	this->yours.setCharacterSize(25);
	this->yours.setString("");
	
	done.setFont(font);
	done.setCharacterSize(25);
	done.setString("Done");
	sf::Clock backspacetimer;
	while (create.isOpen())
	{
		done.setFillColor(sf::Color::White);
		this->yours.setPosition(create.getSize().x / 2 - 7.5 * this->yours.getString().getSize(), 100);
		if (this->yours.getString().getSize() > 0) { done.setPosition(create.getSize().x - 60, create.getSize().y - 30); }
		else { done.setPosition(create.getSize().x, create.getSize().y); }
		sf::Event event2;
		while (create.pollEvent(event2))
		{
			if ((event2.type == sf::Event::Closed) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))))
				create.close();
		}
		if (done.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(create))))
		{
			done.setFillColor(sf::Color::Red);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && backspacetimer.getElapsedTime().asSeconds() > 0.15)
		{
			std::string s = std::string(this->yours.getString()); if (s.size() > 0)s.resize(s.size() - 1);
			this->yours.setString(s);
			backspacetimer.restart();
		}
		else
			for (int i = 0; i < 102; i++)if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)) && backspacetimer.getElapsedTime().asSeconds() > 0.15)
			{
				if (i != 57 && i != 59) { this->yours.setString(std::string(this->yours.getString()) + fromKtoS(sf::Keyboard::Key(i))); }
				backspacetimer.restart();
			}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && done.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(create))))
		{
			create.close();
		}
		create.clear(sf::Color(169, 169, 169));
		create.draw(mine);
		create.draw(this->yours);
		create.draw(done);
		create.display();
	}
}



void LoginState::initButtons()
{
	this->buttons["USER_NAME"] = new Buttons(325, 300, 150, 50, &this->font, "User name");

	this->buttons["PASS_WORD"] = new Buttons(325, 400, 150, 50, &this->font, "Pass word");

	this->buttons["LOG_IN"] = new Buttons(200, 500, 150, 50, &this->font, "Log in");

	this->buttons["SIGN_IN"] = new Buttons(450, 500, 150, 50, &this->font, "Sign in");
}

LoginState::LoginState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initFonts();
	this->intKeybinds();
	this->initButtons();
	this->initWorld();

}

LoginState::~LoginState()
{
	auto it = this->buttons.begin();

	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void LoginState::endState()
{
	std::cout << "End login state" << "\n";
}

void LoginState::addplayer(std::string user_name, std::string pass_word)
{

}


void LoginState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["USER_NAME"]->isPressed())
	{
		this->initTextbox("User name");
		this->user_name = std::string(this->yours.getString());
		this->buttons["USER_NAME"]->setText(std::string(this->yours.getString()));
	}
	if (this->buttons["PASS_WORD"]->isPressed())
	{
		this->initTextbox("Pass word");
		this->pass_word = std::string(this->yours.getString());
		this->buttons["PASS_WORD"]->setText(std::string(this->yours.getString()));
	}
	if (this->buttons["LOG_IN"]->isPressed())
	{
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
	}
	if (this->buttons["SIGN_IN"]->isPressed())
	{
		//this->client->login(this->user_name,this->pass_word);
	}
}



void LoginState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void LoginState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeybinds(dt);

	this->updateButtons();
	
}

void LoginState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}



void LoginState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->worldBackground);
	
	this->renderButtons(target);
	
	
}

std::string LoginState::fromKtoS(const sf::Keyboard::Key& k) {
	std::string ret;
	switch (k) {

	case sf::Keyboard::A:

		ret = "A";
		break;
	case sf::Keyboard::B:

		ret = "B";
		break;
	case sf::Keyboard::C:

		ret = "C";
		break;
	case sf::Keyboard::D:

		ret = "D";
		break;
	case sf::Keyboard::E:

		ret = "E";
		break;
	case sf::Keyboard::F:

		ret = "F";
		break;
	case sf::Keyboard::G:

		ret = "G";
		break;
	case sf::Keyboard::H:

		ret = "H";
		break;
	case sf::Keyboard::I:

		ret = "I";
		break;
	case sf::Keyboard::J:

		ret = "J";
		break;
	case sf::Keyboard::K:

		ret = "K";
		break;
	case sf::Keyboard::L:

		ret = "L";
		break;
	case sf::Keyboard::M:

		ret = "M";
		break;
	case sf::Keyboard::N:

		ret = "N";
		break;
	case sf::Keyboard::O:

		ret = "O";
		break;
	case sf::Keyboard::P:

		ret = "P";
		break;
	case sf::Keyboard::Q:

		ret = "Q";
		break;
	case sf::Keyboard::R:

		ret = "R";
		break;
	case sf::Keyboard::S:

		ret = "S";
		break;
	case sf::Keyboard::T:

		ret = "T";
		break;
	case sf::Keyboard::U:

		ret = "U";
		break;
	case sf::Keyboard::V:

		ret = "V";
		break;
	case sf::Keyboard::W:

		ret = "W";
		break;
	case sf::Keyboard::X:

		ret = "X";
		break;
	case sf::Keyboard::Y:

		ret = "Y";
		break;
	case sf::Keyboard::Z:

		ret = "Z";
		break;
	case sf::Keyboard::Num0:

		ret = "0";
		break;
	case sf::Keyboard::Num1:

		ret = "1";
		break;
	case sf::Keyboard::Num2:

		ret = "2";
		break;
	case sf::Keyboard::Num3:

		ret = "3";
		break;
	case sf::Keyboard::Num4:

		ret = "4";
		break;
	case sf::Keyboard::Num5:

		ret = "5";
		break;
	case sf::Keyboard::Num6:

		ret = "6";
		break;
	case sf::Keyboard::Num7:

		ret = "7";
		break;
	case sf::Keyboard::Num8:

		ret = "8";
		break;
	case sf::Keyboard::Num9:

		ret = "9";
		break;

	case sf::Keyboard::Comma:

		ret = ",";
		break;
	case sf::Keyboard::Period:

		ret = ".";
		break;
	case sf::Keyboard::Equal:

		ret = "=";
		break;
	case sf::Keyboard::Dash:

		ret = "-";
		break;
	case sf::Keyboard::Space:

	case sf::Keyboard::Numpad0:

		ret = "0";
		break;
	case sf::Keyboard::Numpad1:

		ret = "1";
		break;
	case sf::Keyboard::Numpad2:

		ret = "2";
		break;
	case sf::Keyboard::Numpad3:

		ret = "3";
		break;
	case sf::Keyboard::Numpad4:

		ret = "4";
		break;
	case sf::Keyboard::Numpad5:

		ret = "5";
		break;
	case sf::Keyboard::Numpad6:

		ret = "6";
		break;
	case sf::Keyboard::Numpad7:

		ret = "7";
		break;
	case sf::Keyboard::Numpad8:

		ret = "8";
		break;
	case sf::Keyboard::Numpad9:

		ret = "9";
		break;


	default:
		ret = "";
		break;
	}
	return ret;


}