#ifndef GAMESTRUCT_H
#define GAMESTRUCT_H

#include "SK_lib.h"
#include "Account.h"

#define BUFF_SIZE 1024
#define BACKLOG 30 
#define WAIT_TIME 15

// Define communicate message
typedef enum conn_msg_type_type_t
{
    LOGIN,
    JOIN,
    REFUSE,
    WAITING_ROOM,
    GAME_STATE,
    NOTIFICATION,
    POINT,
    END_GAME
} conn_msg_type_type;

// Define data of communicate message
typedef union conn_data_type_R
{
    game_state_type game_state;
    player_type player;
    player_point_type player_point;
    waiting_room_type waiting_room;
    char notification[300];
} conn_data_type;

// Define communicate message
typedef struct conn_msg_type_R
{
    conn_msg_type_type type;
    conn_data_type data;
} conn_msg_type;

// Define client's room
typedef struct client_room_type_t
{
    int connfd[2];
    char username[2][50];
    int point[2];
    // status of client
    // 0: not ready, 1: ready, 2: finished
    int status[2];
    int joined;
} client_room_type;

// Define function's prototype
conn_msg_type make_conn_msg(conn_msg_type_type type, conn_data_type data);

client_room_type* init_client_room();

void send_all(client_room_type client_room, conn_msg_type conn_msg);





#endif // !GAMESTRUCT_H