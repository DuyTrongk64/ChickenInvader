#ifndef HANDLER_H
#define HANDLER_H

#include "SK_lib.h"
#include "Account.h"
#include "GameStruct.h"

#define LENGTH 2048

int connect_to_server();

int disconnect_from_server();

bool login(char user_name[], char pass_word[]);

void send_server();

void receive_server();

int getClient();

void send_msg_handler();

void recv_msg_handler();

void messs();

void str_trim_lf(char* arr, int length);
#endif // !HANDLER_H

