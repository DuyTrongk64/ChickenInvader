#include "SK_lib.h"
#include "Account.h"
#include "GameStruct.h"

conn_data_type conn_data;
conn_msg_type conn_msg;
char username[20];
char password[20];
char guess_char;
int client_sock;

void wait()
{
    sleep(2);
}

void send_server(int connfd, conn_msg_type conn_msg);

void print_title();

void print_waiting_room(waiting_room_type waiting_room);

void print_game_state(game_state_type game_state);

void handle_game_state(game_state_type* game_state);

void print_notification(char* notification);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
        return 0;
    }
    struct sockaddr_in server_addr;
    int bytes_sent, bytes_received, sin_size;

    // Step 1: Construct a TCP socket
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // Call socket() to create a socket
        perror("\nError: ");
        return 0;
    }

    // Step 2: Define the address of the server
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    printf("Server IP: %s - Port: %d\n", argv[1], atoi(argv[2]));

    // Step 3: Request to connect server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }

    // Step 4: Communicate with server
    // Step 4.1: Send username to server

    printf("Welcome to Wheel of Fortune\n");

back:
    printf("Please enter your username: ");
    scanf("%s%*c", username);
    player_type player = init_player(username);

    printf("Connecting to server...\n");
    // Init communicate message
    copy_player_type(&conn_data.player, player);
    conn_msg = make_conn_msg(JOIN, conn_data);

    // Send message to server
    bytes_sent = send(client_sock, &conn_msg, sizeof(conn_msg), 0);
    if (bytes_sent <= 0)
    {
        perror("\nError: ");
        close(client_sock);
        return 0;
    }

    // Step 4.2: Infinitely receive message from server
    while (1)
    {
        printf("Waiting for server's response...\n");
        bytes_received = recv(client_sock, &conn_msg, sizeof(conn_msg), 0);
        printf("[DEBUG] Received %d bytes\n", bytes_received);
        wait();
        if (bytes_received <= 0)
        {
            printf("Lost server's connection\n");
            close(client_sock);
            return 0;
        }

        fflush(stdout);

        // Handle message from server
        switch (conn_msg.type)
        {

        case REFUSE:
            print_notification(conn_msg.data.notification);
            goto back;

        case WAITING_ROOM:
            print_waiting_room(conn_msg.data.waiting_room);
            break;

        case GAME_STATE:
            handle_game_state(&conn_msg.data.game_state);
            break;

        case NOTIFICATION:
            print_notification(conn_msg.data.notification);
            break;

        case END_GAME:
            print_game_state(conn_msg.data.game_state);
            wait();
            return 0;
        }
    }

    // Step 5: Close socket
    close(client_sock);
    return 0;
}

void send_server(int connfd, conn_msg_type conn_msg)
{
    int bytes_sent;
    bytes_sent = send(connfd, &conn_msg, sizeof(conn_msg), 0);
    printf("[DEBUG] Send %d bytes\n", bytes_sent);
    wait();
    if (bytes_sent < 0)
    {
        printf("Error: Cannot send message to server!\n");
        exit(1);
    }
}

void print_title()
{
    printf("Chicken Invader\n");
    printf("====================================\n\n");
}

void print_waiting_room(waiting_room_type waiting_room)
{
    // Clear screen
    printf("\033[2J");

    // Print title
    print_title();

    // Print waiting room
    printf("Waiting room:\n");
    printf("Waiting room joined: %d\n", waiting_room.joined);
    for (int i = 0; i < waiting_room.joined; i++)
    {
        printf("Player %d: %s\n", i + 1, waiting_room.player[i].user_name);
    }
    printf("\n");
}

void print_game_state(game_state_type game_state)
{

    // Clear screen
    printf("\033[2J");

    // Print title
    print_title();

    // Print game state
    printf("====================================\n\n");
    printf("Game state:\n\n");

    // Print player
    for (int i = 0; i < 2; i++)
    {
        printf("Player %d: %s\n", i + 1, game_state.player[i].user_name);
        printf("Point: %d\n\n", game_state.player[i].cur_point);
    }

    // Print server's message
    printf("Server's message: \n%s\n", game_state.game_message);


    return;
}

void handle_game_state(game_state_type* game_state)
{
    int i;
    int bytes_sent;

    print_game_state(*game_state);

 
    
}

void print_notification(char* notification)
{
    // Clear screen
    printf("\033[2J");
    printf("====================================\n\n");
    printf("%s\n", notification);
}
