"# ChickenInvader" 

compile on linux:

g++ -pthread -o main Main.cpp Buttons.cpp Game.cpp GameState.cpp LoginState.cpp MainMenuState.cpp State.cpp Textbox.cpp Chickens.cpp ckBullets.cpp Player.cpp plBullet.cpp Client.cpp -lsfml-graphics -lsfml-window -lsfml-system
