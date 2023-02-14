#ifndef LOGINSTATE_H
#define LOGINSTATE_H

#include "lib.h"
#include "MainMenuState.h"
#include "Buttons.h"
#include "Textbox.h"
#include "Game.h"


class LoginState:
    public State
{
protected:
    //variables
 
    sf::Font font;

    std::map<std::string, Buttons*> buttons;
    std::map<std::string, sf::Text> text;
    sf::RectangleShape border, border1;
    

    sf::Text mine;
    sf::Text yours;
    sf::Text done;

    std::string user_name;
    std::string pass_word;

    bool IsGameOver = 0;
    bool isReady = 0;

    float dt;
    //World
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    //functions
    void initFonts();
    void intKeybinds();
    void initButtons();
    void initWorld();
    void initTextbox(std::string text);
    void initText();
    void initBorder();
public:
    
    LoginState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~LoginState();

    //Functions
    std::string fromKtoS(const sf::Keyboard::Key& k);
    void endState();
    void addplayer(std::string user_name, std::string pass_word );
    std::string getUsername();
    std::string getPassword();
    void updateText();
    void updateButtons();
   
    void updateKeybinds(const float& dt);
    virtual void update(const float& dt);

    void renderText(sf::RenderTarget* target);
    void renderBorder(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget* target);
    
    virtual void render(sf::RenderTarget* target = NULL);

};

#endif // !LOGINSTATE_H