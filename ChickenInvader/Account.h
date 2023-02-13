#ifndef player_type_H
#define player_type_H

#include "lib.h"

typedef struct player_type_R
{
	char user_name[20];
	char pass_word[20];
    int status;
	int hight_point;
	int cur_point;
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
player_type init_player(char username[]);

void copy_player_type(player_type* dest, player_type src);
void copy_waiting_room_type(waiting_room_type* dest, waiting_room_type src);
void copy_game_state_type(game_state_type* dest, game_state_type src);

int getLength(linkedList* list);
void printSingleList(linkedList* list);
void* createSingleList(linkedList* list);
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
int getUserAndPass(linkedList* list, char username[30], char password[30]);

// Function's body
player_type init_player(char username[])
{
    player_type player;
    strcpy(player.user_name, username);
    player.cur_point = 0;
    return player;
}

waiting_room_type init_waiting_room()
{
    waiting_room_type waiting_room;
    waiting_room.joined = 0;
    return waiting_room;
}

game_state_type init_game_state(char key[])
{
    game_state_type game_state;
    return game_state;
}

void copy_player_type(player_type* dest, player_type src)
{
    strcpy(dest->user_name, src.user_name);
    dest->cur_point = src.cur_point;
}

void copy_waiting_room_type(waiting_room_type* dest, waiting_room_type src)
{
    for (int i = 0; i < 2; i++)
    {
        copy_player_type(&dest->player[i], src.player[i]);
    }
    dest->joined = src.joined;
}

void copy_game_state_type(game_state_type* dest, game_state_type src)
{
    for (int i = 0; i < 2; i++)
    {
        copy_player_type(&dest->player[i], src.player[i]);
    }
}
int getLength(linkedList* list)
{
    int count = 0;
    Node* cur = list->root;
    while (cur != NULL)
    {
        cur = cur->next;
        count++;
    }
    return count;
}
void printSingleList(linkedList* list)
{
    player_type nodeAcc;
    if (list == NULL)
        return;
    Node* cur = list->root;
    while (cur != NULL)
    {
        nodeAcc = cur->acc;
        printf("%s\t\t%s\t\t%d\n", nodeAcc.user_name, nodeAcc.pass_word, nodeAcc.hight_point);
        cur = cur->next;
    }
    printf("\n");
}
void* createSingleList(linkedList* list)
{
    list->root = NULL;
    list->tail = NULL;
}
Node* makeNewNode(player_type acc)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->acc = acc;
    newNode->next = NULL;
    return newNode;
}
Node* getNodeAt(linkedList* list, int pos)
{
    if (pos <= 0)
        return list->root;
    if (pos > getLength(list))
        return list->tail;
    Node* cur = list->root;
    int i = 1;
    while (i != pos)
    {
        cur = cur->next;
        i++;
    }
    return cur;
};
Node* insertBegin(linkedList* list, player_type acc)
{
    Node* newNode = makeNewNode(acc);
    if ((*list).root == NULL)
    {
        (*list).root = (*list).tail = newNode;
    }
    else
    {
        newNode->next = (*list).root;
        (*list).root = newNode;
    }
    return (*list).root;
}
Node* insertEnd(linkedList* list, player_type e)
{
    Node* newNode = makeNewNode(e);
    if (list->root == NULL)
    {
        list->root = list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    return list->root;
};
Node* insertAt(linkedList* list, player_type e, int pos)
{
    Node* cur = getNodeAt(list, pos - 1);
    Node* newNode = makeNewNode(e);
    newNode->next = cur->next;
    cur->next = newNode;
    return list->root;
}
Node* deleteBegin(linkedList* list)
{
    if (list->root != NULL)
    {
        Node* newNode = list->root;
        list->root = list->root->next;
        free(newNode);
    }
    return list->root;
};
Node* deleteEnd(linkedList* list)
{
    Node* beforeTail = getNodeAt(list, getLength(list) - 1);
    beforeTail->next = NULL;
    free(list->tail);
    list->tail = beforeTail;
    return list->root;
};
Node* deleteAt(linkedList* list, int pos)
{
    if (pos > getLength(list))
        return NULL;
    Node* prevNode = getNodeAt(list, pos - 1);
    Node* currNode = getNodeAt(list, pos);
    prevNode->next = currNode->next;
    free(currNode);
    return list->root;
};

void readFile()
{
    FILE* filename;
    char chat[1024];
    if ((filename = fopen("groupchat.txt", "r+")) == NULL)
    {
        printf("Khong tim thay filename!\n");
        return;
    }
    while (fgets(chat, 1024, filename))
    {
        printf("%s\n", chat);
    }

    fclose(filename);
    return;
}

void addChat(char* chat)
{
    FILE* filename;

    if ((filename = fopen("groupchat.txt", "a+")) == NULL)
    {
        printf("Khong tim thay filename!\n");
        return;
    }

    fprintf(filename, chat);

    fclose(filename);
    return;
}

void readPlayerData(linkedList* list)
{
    player_type node;
    FILE* filename;
    if ((filename = fopen("player_type.txt", "r+")) == NULL)
    {
        printf("Khong tim thay filename!\n");
        return;
    }
    while (!feof(filename))
    {
        int scan = fscanf(filename, "%s %s %d\n", node.user_name, node.pass_word, &node.status);
        insertEnd(list, node);
    }
    fclose(filename);
}

void appendDataToFile(FILE* filename, player_type acc)
{
    fprintf(filename, "%s %s %d\n", acc.user_name, acc.pass_word, acc.status);
}

void writeListToFile(linkedList* list)
{
    FILE* filename;
    Node* huan = list->root;
    if ((filename = fopen("taikhoan.txt", "w")) == NULL)
    {
        printf("Khong tim thay filename!\n");
        return;
    }
    while (huan != NULL)
    {
        appendDataToFile(filename, huan->acc);
        huan = huan->next;
    }
    fclose(filename);
}

int getUserAndPass(linkedList* list, char username[30], char password[30])
{
    Node* cur = list->root;
    while (cur != NULL)
    {
        if (strcmp(cur->acc.user_name, username) == 0)
        {
            if (strcmp(cur->acc.pass_word, password) == 0)
            {
                if (cur->acc.status == 1) return 1;
                else return 0;
            }
        }
        cur = cur->next;
    }
    return 2;
}

#endif // !player_type_H

