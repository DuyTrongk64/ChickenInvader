#ifndef player_type_H
#define player_type_H

#include "SK_lib.h"

typedef struct player_type_R
{
	char user_name[20];
	char pass_word[20];
    int status;
	int hight_point;
	int cur_point;
	int id;
}player_type;

typedef struct waiting_room_type_t
{
	player_type player[2];
	int joined;
} waiting_room_type;

typedef struct game_state_type_R
{
	player_type player[2];
    char game_message[200];
}game_state_type;

typedef struct player_point_type_t
{
	char username[20];      // Username of player's turn
	int point;
} player_point_type;

typedef struct Node
{
	player_type acc;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct
{
	Node* root;
	Node* tail;
} linkedList;


game_state_type init_game_state();
waiting_room_type init_waiting_room();
player_type init_player(char username[],int id);

void copy_player_type(player_type* dest, player_type src);
void copy_waiting_room_type(waiting_room_type* dest, waiting_room_type src);
void copy_game_state_type(game_state_type* dest, game_state_type src);
void copy_sub_question_type(player_point_type* dest, player_point_type src);

int getLength(linkedList* list);
void printSingleList(linkedList* list);
void createSingleList(linkedList* list);
Node* makeNewNode(player_type e);
Node* getNodeAt(linkedList* list, int index);
Node* insertEnd(linkedList* list, player_type e);
Node* insertBegin(linkedList* list, player_type e);
Node* insertAt(linkedList* list, player_type e, int pos);
Node* deleteBegin(linkedList* list);
Node* deleteEnd(linkedList* list);
Node* deleteAt(linkedList* list, int pos);

void readFile();
void readPlayerData(linkedList* list);
void writeListToFile(linkedList* list);
void appendDataToFile(FILE* file, player_type acc);
int getUserAndPass(linkedList* list, char username[20], char password[20]);



#endif // !player_type_H

