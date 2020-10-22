#include "List.h"
#include <stdlib.h>
#include <stdio.h>

static void Copy_toNode( Position position, Node *node );

void List_init( List *wlist ){
    *wlist = NULL;
}

bool List_isEmpty( List *wList ){
    if( *wList == NULL )
        return true;
    else
        return false;
}

bool List_isFull(List *wList){
    Node *ptr;
    ptr = (Node *)malloc(sizeof(Node));
    if( ptr == NULL )
        return true;
    else{
        return false;
    }
    free(ptr);
}

uint16_t List_PositionNumber( List *wList ){
    uint16_t counter = 0;
    Node *actual = *wList;
    while( actual != NULL ){
        counter++;
        actual = actual->next;
    }
    return counter;
}

bool List_AddPosition( Position position, List *wList ){
    Node *new_pos;
    Node *actual = *wList;
    new_pos = (Node *)malloc( sizeof( Node ) );
    if( new_pos == NULL )
        return false;

    Copy_toNode( position, new_pos );
    new_pos->next = NULL;
    if( actual == NULL ){
        *wList = new_pos;
    }else{
        while( actual->next != NULL ){
            actual = actual->next;      //find end of the list
        }
        actual->next = new_pos;     //add new at the end
    }
    return true;
}
void List_move( List *wList, void (*func)(Position position)){
    Node *actual = *wList;
    while( actual != NULL ){
        (* func)(actual->position);
        actual = actual->next;
    }
}

void List_clear( List *wList ){
    Node *actual;
    while( *wList != NULL ){
        actual = (*wList)->next;
        free(*wList);
        *wList = actual;
    }
}
void List_clear2( Node *wList ){
    Node *actual;
    while( wList != NULL ){
        actual = wList->next;
        free(wList);
        wList = actual;
    }
}
void List_move2( Node *wList, void (*func)(Position position)){
    Node *actual = wList;
    while( actual != NULL ){
        (* func)(actual->position);
        actual = actual->next;
    }
}

bool List_AddPosition2( Position position, Node **wList ){
    Node *new_pos;
    Node *actual = *wList;
    new_pos = (Node *)malloc( sizeof( Node ) );
    if( new_pos == NULL )
        return false;

    Copy_toNode( position, new_pos );
    new_pos->next = NULL;
    if( actual == NULL ){
        *wList = new_pos;
    }else{
        while( actual->next != NULL ){
            actual = actual->next;      //find end of the list
        }
        actual->next = new_pos;     //add new at the end
    }
    return true;
}

uint16_t List_PositionNumber2( Node *wList ){
    uint16_t counter = 0;
    Node *actual = wList;
    while( actual != NULL ){
        counter++;
        actual = actual->next;
    }
    return counter;
}

void List_init2( Node **wlist ){
    *wlist = NULL;
}

bool List_isEmpty2( Node *wList ){
    if( wList == NULL )
        return true;
    else
        return false;
}

bool List_isFull2( Node *wList ){
    Node *ptr;
    ptr = (Node *)malloc(sizeof(Node));
    if( ptr == NULL )
        return true;
    else{
        return false;
    }
    free(ptr);
}

static void Copy_toNode( Position position, Node *node ){
    node->position = position;
}
