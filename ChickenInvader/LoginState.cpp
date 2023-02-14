#include "LoginState.h"

extern conn_msg_type conn_msg;
extern char username[20];
extern char password[20];
extern int bytes_received;
extern int bytes_sent;
extern int client_sock;

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

void LoginState::initText()
{
	this->text["USER_NAME"].setFont(this->font);
	this->text["USER_NAME"].setCharacterSize(20);
	this->text["USER_NAME"].setFillColor(sf::Color::White);
	this->text["USER_NAME"].setString("User name");
	this->text["USER_NAME"].setPosition(355, 300);

	this->text["PASS_WORD"].setFont(this->font);
	this->text["PASS_WORD"].setCharacterSize(20);
	this->text["PASS_WORD"].setFillColor(sf::Color::White);
	this->text["PASS_WORD"].setString("Pass word");
	this->text["PASS_WORD"].setPosition(355, 400);
}

void LoginState::initBorder()
{
	border.setFillColor(sf::Color::Transparent);
	border1.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(2);
	border1.setOutlineThickness(2);
	border.setSize(sf::Vector2f(this->text["USER_NAME"].getCharacterSize()
		* this->text["USER_NAME"].getString().getSize() / 1.9 + 30, 1.5 * this->text["USER_NAME"].getCharacterSize()));
	border.setPosition(this->text["USER_NAME"].getPosition().x-20, this->text["USER_NAME"].getPosition().y);
	border1.setSize(sf::Vector2f(this->text["USER_NAME"].getCharacterSize()
		* this->text["USER_NAME"].getString().getSize() / 1.9 + 30, 1.5 * this->text["USER_NAME"].getCharacterSize()));
	border1.setPosition(this->text["PASS_WORD"].getPosition().x-20, this->text["PASS_WORD"].getPosition().y);
}

void LoginState::initButtons()
{
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
	this->initText();
	this->initBorder();
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

std::string LoginState::getUsername()
{
	return this->user_name;
}

std::string LoginState::getPassword()
{
	return this->pass_word;
}

void LoginState::updateText()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->text["USER_NAME"].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window))))
		{
			this->initTextbox("User name");
			this->user_name = std::string(this->yours.getString());
			this->text["USER_NAME"].setString(std::string(this->yours.getString()));
		}

		if (this->text["PASS_WORD"].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window))))
		{
			this->initTextbox("Pass word");
			this->pass_word = std::string(this->yours.getString());
			this->text["PASS_WORD"].setString(std::string(this->yours.getString()));
		}
	}

}

void LoginState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	
	if (this->buttons["LOG_IN"]->isPressed())
	{
		strcpy(username, this->user_name.c_str());
		str_trim_lf(username, strlen(username));
		strcpy(password, this->pass_word.c_str());
		str_trim_lf(password, strlen(password));
		if (login(username, password))
			this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
		else
		std::cout << "dang nhap that bai\n";
		//messs();
	}
	if (this->buttons["SIGN_IN"]->isPressed())
	{
		//printf("dm son linh");
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
	
	this->updateText();
}

void LoginState::renderText(sf::RenderTarget* target)
{
	for (auto& it : this->text)
	{
		target->draw(it.second);
	}
}

void LoginState::renderBorder(sf::RenderTarget* target)
{
	target->draw(this->border);
	target->draw(this->border1);
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

	this->renderText(target);
	
	this->renderBorder(target);
}

std::string LoginState::fromKtoS(const sf::Keyboard::Key& k) {
	std::string ret;
	switch (k) {

	case sf::Keyboard::A:

		ret = "a";
		break;
	case sf::Keyboard::B:

		ret = "b";
		break;
	case sf::Keyboard::C:

		ret = "c";
		break;
	case sf::Keyboard::D:

		ret = "d";
		break;
	case sf::Keyboard::E:

		ret = "e";
		break;
	case sf::Keyboard::F:

		ret = "f";
		break;
	case sf::Keyboard::G:

		ret = "g";
		break;
	case sf::Keyboard::H:

		ret = "h";
		break;
	case sf::Keyboard::I:

		ret = "i";
		break;
	case sf::Keyboard::J:

		ret = "j";
		break;
	case sf::Keyboard::K:

		ret = "k";
		break;
	case sf::Keyboard::L:

		ret = "l";
		break;
	case sf::Keyboard::M:

		ret = "m";
		break;
	case sf::Keyboard::N:

		ret = "n";
		break;
	case sf::Keyboard::O:

		ret = "o";
		break;
	case sf::Keyboard::P:

		ret = "p";
		break;
	case sf::Keyboard::Q:

		ret = "q";
		break;
	case sf::Keyboard::R:

		ret = "r";
		break;
	case sf::Keyboard::S:

		ret = "s";
		break;
	case sf::Keyboard::T:

		ret = "t";
		break;
	case sf::Keyboard::U:

		ret = "u";
		break;
	case sf::Keyboard::V:

		ret = "v";
		break;
	case sf::Keyboard::W:

		ret = "w";
		break;
	case sf::Keyboard::X:

		ret = "x";
		break;
	case sf::Keyboard::Y:

		ret = "y";
		break;
	case sf::Keyboard::Z:

		ret = "z";
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