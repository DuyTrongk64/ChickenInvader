#include "Handler.h"

#define server_ip "127.0.0.1"
#define server_port 5500

conn_data_type conn_data;
conn_msg_type conn_msg;
char username[20];
char password[20];
int client_sock=0;
struct sockaddr_in server_addr;
int bytes_sent, bytes_received, sin_size;
int connect_to_server()
{
    // Step 1: Construct a TCP socket
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // Call socket() to create a socket
        perror("\nError in connection.\n ");
        return 0;
    }
    printf("Client Socket is created.\n");
    // Step 2: Define the address of the server
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
     printf("Server IP: %s - Port: %d\n", server_ip, server_port);

    // Step 3: Request to connect server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }

    return 1;
}

int disconnect_from_server()
{
    close(client_sock);
    return 1;
}

bool login(char user_name[], char pass_word[])
{
    // Step 3: Request to connect server
    /*if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }*/
    char buffer[1024];
    send(client_sock, user_name, 32, 0);
    send(client_sock, pass_word, 32, 0);
    if (recv(client_sock, &buffer, sizeof(buffer), 0) == 1)
        printf("Tu server: %s\n", buffer);
    else printf("ko nhan dc phan hoi\n");
    if (strcmp(buffer, "User signed in!\n") != 0)
        return false;

    return true;
}

void send_server()
{
    bytes_sent = send(client_sock, &conn_msg, sizeof(conn_msg), 0);
    printf("[DEBUG] Send %d bytes\n", bytes_sent);
    if (bytes_sent < 0)
    {
        printf("Error: Cannot send message to server!\n");
        exit(1);
    }
}

void receive_server()
{
    bytes_received = recv(client_sock, &conn_msg, sizeof(conn_msg), 0);
    printf("[DEBUG] Receive %d bytes\n", bytes_received);
    if (bytes_received < 0)
    {
        printf("Error: Cannot receive message from server!\n");
        exit(1);
    }
}

int getClient()
{
    return client_sock;
}

//void send_msg_handler() {
//    char message[LENGTH];
//    char buffer[LENGTH + 32];
//
//    while (1) {
//        
//        fgets(message, LENGTH, stdin);
//        str_trim_lf(message, LENGTH);
//
//        if (strcmp(message, "exit") == 0) {
//            break;
//        }
//        else {
//            sprintf(buffer, "%s: %s\n", username, message);
//            send(client_sock, buffer, strlen(buffer), 0);
//        }
//
//        bzero(message, LENGTH);
//        bzero(buffer, LENGTH + 32);
//    }
//
//}
//
//void recv_msg_handler() {
//    char message[LENGTH] = {};
//    while (1) {
//        int receive = recv(client_sock, message, LENGTH, 0);
//        if (receive > 0) {
//            printf("%s", message);
//            
//        }
//        else if (receive == 0) {
//            break;
//        }
//        else {
//            // -1
//        }
//        memset(message, 0, sizeof(message));
//    }
//}
//
//void messs()
//{
//    pthread_t send_msg_thread;
//    if (pthread_create(&send_msg_thread, NULL, (void*)send_msg_handler, NULL) != 0) {
//        printf("ERROR: pthread\n");
//    }
//
//    pthread_t recv_msg_thread;
//    if (pthread_create(&recv_msg_thread, NULL, (void*)recv_msg_handler, NULL) != 0) {
//        printf("ERROR: pthread\n");
//    }
//}

void str_trim_lf(char* arr, int length) {
    int i;
    for (i = 0; i < length; i++) { // trim \n
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}