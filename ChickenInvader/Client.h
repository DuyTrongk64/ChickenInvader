//#ifndef CLIENT_H
//#define CLIENT_H
//
//#include "lib.h"
//
//
//using namespace std;
//using namespace sf;
//
//class Client
//{
//	/*struct Account
//	{
//		string user_name;
//		string pass_word;
//	};
//
//	struct Point
//	{
//		string user_name;
//		int point;
//	};
//
//	struct GameSTT
//	{
//		string user_name;
//		bool stt;
//	};
//
//	Packet& operator <<( const Account& acc)
//	{
//		return paket << acc.user_name << acc.pass_word;
//	}
//
//	Packet& operator <<(const Point& point)
//	{
//		return paket << point.user_name << point.point;
//	}*/
//
//	
//
//public:
//	Client();
//	~Client();
//	void SendPoint(string mess);
//	void sendLogin(string user_name, string pass_word);
//	bool ReceiName(sf::RenderWindow& window);
//	void Waiting(sf::RenderWindow& window);
//	bool recLogin(string mess);
//	//void InitiatePoint();
//	void ReceiveScore();
//	void calculatePoint();
//
//	vector<sf::Text> PList;
//	vector<sf::Text> PPoint;
//	vector<int> thu_tu;
//	bool DoneWaiting = 0;
//	bool ReceivedName = 0;
//	bool IsGameOver = 0;
//	bool isReady = 0;
//private:
//	sf::Font font;
//	int index = 0;
//	sf::Event e;
//	IpAddress ip;//= IpAddress::getLocalAddress();
//	TcpSocket socket;
//	Packet packet;
//	
//	void takeOut(std::string mess);
//	void deletePlayer(int j);
//
//
//};
//#endif // !CLIENT_H