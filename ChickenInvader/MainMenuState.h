#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "lib.h"

#include "GameState.h"
#include "Buttons.h"

class MainMenuState :
    public State
{
protected:
    //variables
    sf::RectangleShape background;
    sf::Font font;

    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    std::map<std::string, Buttons*> buttons;
    
    //functions
    void initFonts();
    void intKeybinds();
    void initButtons();
    void initWorld();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*>* states, Handler* handler);
    virtual ~MainMenuState();

    //Functions
    void endState();

    void updateButtons();
    void updateKeybinds(const float& dt);
    virtual void update(const float& dt);
    void renderButtons(sf::RenderTarget* target);
    virtual void render(sf::RenderTarget* target = NULL);
};

#endif // !MAINMENUSTATE_H