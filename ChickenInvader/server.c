#include "SK_lib.h"
#include "Account.h"
#include "GameStruct.h"

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

linkedList list;
// Global variables
client_room_type client_room;


/* Handle all communication with the client */
void* client_handle(void* arg);

int main(int argc, char* argv[]) {
	if (argc != 2) {
			printf("\nUsage: %s <Server Port>", argv[0]);
			return EXIT_FAILURE;
		}

	int listenfd, * connfd;
	int break_nested_loop = 0;
	struct sockaddr_in server, * client; // Server's address information
	int sin_size;
	pthread_t tid;
	int bytes_received, bytes_sent;
	int current_joined;
	char temp[300];

	// Ignore SIGPIPE signal (when server try to send data to client but client is disconnected)
	sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);

	// Create new communicate message variable
	conn_msg_type conn_msg;

	/* Socket settings */
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{ /* calls sockets() */
		perror("\nError: ");
		return 0;
	}
	printf("Server Socket is created.\n");

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listenfd, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		perror("\nError: ");
		return 0;
	}

	if (listen(listenfd, BACKLOG) == -1)
	{
		perror("\nError: ");
		return 0;
	}

	sin_size = sizeof(struct sockaddr_in);
	client = malloc(sin_size);

	printf("=== List account ===\n");
	createSingleList(&list);
	readPlayerData(&list);
	printSingleList(&list);

	while (1)
	{
		client_room_type* client_room = init_client_room();
		waiting_room_type waiting_room = init_waiting_room();
		current_joined = 0;

		
	
		break_nested_loop = 0;

		while (current_joined<2)
			{

			if ((client_room->connfd[current_joined] = accept(listenfd, (struct sockaddr*)client, &sin_size)) == -1)
				perror("\nError: ");
			printf("You got a connection from %s\n", inet_ntoa((*client).sin_addr)); /* Print client's IP */
			
			// Receive username from client
			bytes_received = recv(client_room->connfd[current_joined], &conn_msg, sizeof(conn_msg), 0);
			if (bytes_received <= 0)
			{
				close(client_room->connfd[current_joined]);
				continue;
			}

			if (break_nested_loop)
			{
				close(client_room->connfd[current_joined]);
				continue;
			}

			printf("Waiting room: received %d bytes\n", bytes_received);
			fflush(stdout);
			strcpy(client_room->username[current_joined], conn_msg.data.player.user_name);
			strcpy(waiting_room.player[current_joined].user_name, conn_msg.data.player.user_name);

			// Set active status
			client_room->status[current_joined] = 1;

			client_room->joined++;
			waiting_room.joined++;

			// Send waiting room to client
			copy_waiting_room_type(&conn_msg.data.waiting_room, waiting_room);
			conn_msg = make_conn_msg(WAITING_ROOM, conn_msg.data);
			send_all(*client_room, conn_msg);

			current_joined++;
		}

		// For each client's room, spawns a thread, and the thread handles the new client's room
		pthread_create(&tid, NULL, &client_handle, (void*)client_room);
	}
	}


void* client_handle(void* arg)
{

		int i;
		srand(time(0));
		client_room_type client_room = *(client_room_type*)arg;

		free(arg);
		int correct = 1;

		int bytes_sent, bytes_received;
		conn_msg_type conn_msg;

		// Init game state
		game_state_type game_state = init_game_state();

		// Init player
		for (i = 0; i < client_room.joined; i++)
		{
			game_state.player[i] = init_player(client_room.username[i], client_room.connfd[i]);
		}

		for (i = 0; i < client_room.joined; i++)
		{
			printf("Player %d: %s\n", i, game_state.player[i].user_name);
		}
		int current_joined = 0;
		while (current_joined <2)
		{
			recv(client_room.connfd[current_joined], &conn_msg, sizeof(conn_msg), 0);
			strcpy(client_room.point[current_joined], conn_msg.data.player.cur_point);
			current_joined++;
		}


		if (client_room.point[1] > client_room.point[2])
		{
			printf("Player %s win  \n", client_room.username[1]);
		}
		else
		{
			printf("Player %s win  \n", client_room.username[2]);
		}
		// Send game summary to all clients
		copy_game_state_type(&conn_msg.data.game_state, game_state);
		conn_msg = make_conn_msg(END_GAME, conn_msg.data);
		send_all(client_room, conn_msg);

		printf("Close thread\n");
		pthread_exit(NULL);

	
}
