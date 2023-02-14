#include "Handler.h"


int Handler::connect_to_server()
{
    // Step 1: Construct a TCP socket
    if ((this->client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // Call socket() to create a socket
        perror("\nError in connection.\n ");
        return 0;
    }
    printf("Client Socket is created.\n");
    // Step 2: Define the address of the server
    memset(&server_addr, '\0', sizeof(server_addr));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(server_port);
    this->server_addr.sin_addr.s_addr = inet_addr(server_ip);
     printf("Server IP: %s - Port: %d\n", server_ip, server_port);

    // Step 3: Request to connect server
    if (connect(this->client_sock, (struct sockaddr*)&this->server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }

    return 1;
}

int Handler::disconnect_from_server()
{
    close(client_sock);
    return 1;
}

bool Handler::login(char user_name[], char pass_word[])
{
    // Step 3: Request to connect server
    /*if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }*/
    char buffer[1024];
    send(this->client_sock, user_name, 32, 0);
    //send(this->client_sock, pass_word, 32, 0);
    if (recv(this->client_sock, &buffer, sizeof(buffer), 0) == 1)
        printf("Tu server: %s\n", buffer);
    else printf("ko nhan dc phan hoi\n");
    if (strcmp(buffer, "User signed in!\n") != 0)
        return false;

    return true;
}

void Handler::send_server()
{
    this->bytes_sent = send(this->client_sock, &conn_msg, sizeof(conn_msg), 0);
    printf("[DEBUG] Send %d bytes\n", this->bytes_sent);
    if (bytes_sent < 0)
    {
        printf("Error: Cannot send message to server!\n");
        exit(1);
    }
}

void Handler::receive_server()
{
    this->bytes_received = recv(client_sock, &conn_msg, sizeof(conn_msg), 0);
    printf("[DEBUG] Receive %d bytes\n", this->bytes_received);
    if (this->bytes_received < 0)
    {
        printf("Error: Cannot receive message from server!\n");
        exit(1);
    }
}

void Handler::wait()
{
    sleep(2);
}

void Handler::send_server(int connfd, conn_msg_type conn_data)
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

void Handler::print_waiting_room(waiting_room_type waiting_room)
{
    // Clear screen
    printf("\033[2J");

    // Print waiting room
    printf("Waiting room:\n");
    printf("Waiting room joined: %d\n", waiting_room.joined);
    for (int i = 0; i < waiting_room.joined; i++)
    {
        printf("Player %d: %s\n", i + 1, waiting_room.player[i].user_name);
    }
    printf("\n");
}

void Handler::print_game_state(game_state_type game_state)
{
    // Clear screen
    printf("\033[2J");

    // Print game state
    printf("====================================\n\n");
    printf("Game state:\n\n");

    // Print player
    for (int i = 0; i < 2; i++)
    {
        printf("Player %d: %s\n", i + 1, game_state.player[i].user_name);
        printf("Point: %d\n\n", game_state.player[i].cur_point);
    }

    return;
}

void Handler::handle_game_state(game_state_type* game_state)
{
    int i;
    int bytes_sent;

    print_game_state(*game_state);

    copy_game_state_type(&conn_msg.data.game_state, *game_state);
    conn_msg = make_conn_msg(POINT, conn_msg.data);
    send_server(client_sock, conn_msg);
}

void Handler::print_notification(char* notification)
{
}

void Handler::sendPoint(int point)
{
    conn_msg.data.player.cur_point = point;
    conn_msg.type = POINT;
    send_server();
}

void Handler::join(char username[20])
{
    conn_msg.data.player = init_player(username, -1);
    conn_msg.type = JOIN;
    send_server();
    receive_server();
    //pthread_t tid;
}



void str_trim_lf(char* arr, int length) {
    int i;
    for (i = 0; i < length; i++) { // trim \n
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

Handler::Handler()
{
    this->connect_to_server();
}

Handler::~Handler()
{
    this->disconnect_from_server();
}
