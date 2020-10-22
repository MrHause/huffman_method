#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define FILM_NAME_MAX_LEN 50

typedef struct film{
    char title[FILM_NAME_MAX_LEN];
    uint8_t note;
}Position;

typedef struct node{
    Position position;
    struct node *next;
}Node;

typedef Node * List;        //wskaźnik do węzła. List films --> struct node * List. 
Node *films2;               //alternative to test. the functions arguments must be changed
void List_init( List *wlist );
void List_init2( Node **wlist );

bool List_isEmpty( List *wList );
bool List_isEmpty2( Node *wList );

bool List_isFull( List *wList );
bool List_isFull2( Node *wList );

uint16_t List_PositionNumber( List *wList );
uint16_t List_PositionNumber2( Node *wList );

bool List_AddPosition( Position position, List *wList );
bool List_AddPosition2( Position position, Node **wList );

void List_move( List *wList, void (*func)(Position position));
void List_move2( Node *wList, void (*func)(Position position));

void List_clear( List *wList );
void List_clear2( Node *wList );


#endif