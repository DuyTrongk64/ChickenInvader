#ifndef HANDLER_H
#define HANDLER_H

#include "SK_lib.h"
#include "Account.h"
#include "GameStruct.h"

#define LENGTH 2048
#define server_ip "127.0.0.1"
#define server_port 5500
class Handler
{
public:


	conn_data_type conn_data;
	conn_msg_type conn_msg;
	char username[20];
	char password[20];
	int client_sock = 0;
	struct sockaddr_in server_addr;
	int bytes_sent, bytes_received, sin_size;

	Handler();
	virtual ~Handler();

	int connect_to_server();

	int disconnect_from_server();

	bool login(char user_name[], char pass_word[]);

	void send_server();

	void receive_server();

	void wait();

	void send_server(int connfd, conn_msg_type conn_msg);

	void print_waiting_room(waiting_room_type waiting_room);

	void print_game_state(game_state_type game_state);

	void handle_game_state(game_state_type* game_state);

	void print_notification(char* notification);

	void sendPoint(int point);

	void join(char username[20]);
};


#endif // !HANDLER_H

