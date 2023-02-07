//#include "Client.h"
//
//
//Client::Client()
//{
//    
//}
//Client::~Client()
//{
//}
//void Client::SendPoint(string mess)
//{
//    packet.clear();
//    packet << mess;
//    socket.send(packet);
//}
//void Client::sendLogin(string user_name, string pass_word)
//{
//    packet.clear();
//    packet << user_name << pass_word;
//    socket.send(packet);
//}
//bool Client::ReceiName(sf::RenderWindow& window)
//{
//    packet.clear();
//    string buf;
//    while (window.pollEvent(e))
//    {
//        if (e.type == Event::Closed)
//            window.close();
//        if (e.type == Event::KeyPressed && e.key.code == Keyboard::R) {
//            SendPoint("ready");
//        }
//    }
//    if (socket.receive(packet) == Socket::Done)
//    {
//        if (ReceivedName != true)
//            while (1) {// Nhan  danh sach nguoi choi
//                packet >> buf;
//                if (buf == "") break;
//                else if (buf == "OK") { DoneWaiting = 1; break; }
//                takeOut(buf);
//            }
//        else
//            for (int i = 0; i <= index; i++) {// Nhan ten nguoi choi moi vao
//                packet >> buf;
//                if (i == index) { takeOut(buf); break; }
//                else if (buf == "OK") { DoneWaiting = 1; break; }
//            }
//        ReceivedName = true;
//        return 1;
//    }
//    return 0;
//}
//void Client::deletePlayer(int j)
//{
//    PList.erase(PList.begin() + j);
//    for (int i = 0; i < index; i++)
//    {
//        if (i >= j)  PList[index].setPosition(sf::Vector2f(20,
//            480 / (5 + 1) * (i)));
//    }
//}
//void Client::Waiting(sf::RenderWindow& window)
//{
//    string buf, buf2;
//    while (window.pollEvent(e))
//    {
//        if (e.type == Event::Closed)
//            window.close();
//        if (e.type == Event::KeyPressed && e.key.code == Keyboard::R) {
//            SendPoint("ready");
//        }
//    }
//    if (socket.receive(packet) == Socket::Done)
//    {
//        packet >> buf;
//        packet >> buf2;
//        if (buf == "OK") {
//            DoneWaiting = 1;
//        }
//        else if (buf == "ready") {
//            PList[stoi(buf2)].setFillColor(sf::Color::Green);
//        }
//        else if (buf == "Disconnected") {
//            deletePlayer(stoi(buf2));
//        }
//        else if (buf == "new Player") {
//            packet >> buf;
//            takeOut(buf2);
//        }
//    }
//}
//
//bool Client::recLogin(string mess)
//{
//    socket.receive(packet);
//    if(packet)
//    return false;
//}
//
//
//void Client::ReceiveScore()
//{
//    packet.clear();
//    if (socket.receive(packet) == Socket::Done)
//    {
//        string mess[3];
//        for (int i = 0; i < 3; i++) {
//            packet >> mess[i];
//        }
//        packet.clear();
//        if (mess[2] == "") {
//            mess[2] = mess[1];
//            mess[1] = mess[0];
//        }
//        if (mess[1] == "death") {
//            PList[stoi(mess[2])].setFillColor(sf::Color::Yellow);
//            PPoint[stoi(mess[2])].setFillColor(sf::Color::Yellow);
//        }
//        else if (mess[1] == "TheGameIsOver") {
//            IsGameOver = 1;
//        }
//        else  PPoint[stoi(mess[2])].setString(mess[1]);
//    }
//}
// void swap(int *a, int*b){
// 	int *c = a;
// 	a = b;
// 	b = c;
// }
//void Client::calculatePoint() {
//    std::vector<int> sss;
//    int i = 0;
//    for (auto const& value : PPoint) {
//        sss.push_back(stoi(value.getString().toAnsiString()));
//        thu_tu.push_back(i);
//        i++;
//    }
//    for (int counterrrs = i - 1; counterrrs >= 0; counterrrs--) {
//        for (int j = 0; j < counterrrs; j++) {
//            if (sss[j] < sss[j + 1]) {
//                swap(sss[j], sss[j + 1]);
//                swap(thu_tu[j], thu_tu[j + 1]);
//            }
//        }
//    }
//    i = 0;
//    for (auto const& value : thu_tu)
//    {
//        PList[i].setPosition(sf::Vector2f(120, (480 / 7) * (value + 1)));
//        PPoint[i].setPosition(sf::Vector2f(140, 30 + (480 / 7) * (value + 1)));
//        i++;
//    }
//}
