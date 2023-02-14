"# ChickenInvader" 

compile on linux:

game: 

g++ -pthread -o game  Game.cpp Buttons.cpp GameState.cpp SingleGameState.cpp LoginState.cpp MainMenuState.cpp State.cpp Textbox.cpp Chickens.cpp ckBullets.cpp Player.cpp plBullet.cpp Account.c GameStruct.c Handler.cpp -lsfml-graphics -lsfml-window -lsfml-system

server:

gcc -pthread -o server server.c Account.c GameStruct.c

