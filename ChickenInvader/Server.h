#include "lib.h"
using namespace std;
using namespace sf;
#define MAX_NUMBER_OF_PLAYERS 5

class Server
{
public:
	
private:
	
	Socket::Status status;
	Packet packet;
	int index = 0;
	vector <unique_ptr<TcpSocket>> socket;
	string str;
	TcpListener listener;
	Event e;
	sf::Font font;

};
