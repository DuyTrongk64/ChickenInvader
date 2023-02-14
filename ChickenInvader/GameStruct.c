#include "GameStruct.h"
// Define function's body
conn_msg_type make_conn_msg(conn_msg_type_type type, conn_data_type data)
{
    conn_msg_type conn_msg;
    conn_msg.type = type;
    switch (type)
    {
    case JOIN:
        copy_player_type(&conn_msg.data.player, data.player);
        break;

    case WAITING_ROOM:
        copy_waiting_room_type(&conn_msg.data.waiting_room, data.waiting_room);
        break;

    case GAME_STATE:
        copy_game_state_type(&conn_msg.data.game_state, data.game_state);
        break;

    case NOTIFICATION:
        strcpy(conn_msg.data.notification, data.notification);
        break;

    case END_GAME:
        copy_game_state_type(&conn_msg.data.game_state, data.game_state);
        break;

    case REFUSE:
        strcpy(conn_msg.data.notification, data.notification);
        break;

    }
    return conn_msg;
}

client_room_type* init_client_room()
{
    // Initialize client room
    client_room_type* client_room = (client_room_type*)malloc(sizeof(client_room_type));
    for (int i = 0; i < client_room->joined; i++)
    {
        client_room->connfd[i] = -1;
        client_room->status[i] = 0;
    }
    client_room->joined = 0;
    return client_room;
}