#include <stdlib.h>
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


void Show_film( Position position );
char * Load_data( char *z, int num );

int main(){
    
    //List films;         // List films-> Node * films -> strucy node * films, wskaźnik do listy
    Position temp_pos;
    Node *films;
    List_init2(&films);
    if( List_isFull2(films) ){
        fprintf( stderr, "brak pamieci" );
        exit(1);
    }
    puts( "Podaj pierwszy tytul filmu: ");
    while( Load_data(temp_pos.title, FILM_NAME_MAX_LEN) != NULL && temp_pos.title[0] != '\0' ){
        puts( "Podaj Ocene <0-10>:" );
        scanf( "%hhu", &temp_pos.note);
        while( getchar() != '\n' )
            continue;
        if( List_AddPosition2( temp_pos, &films ) == false ){
            fprintf( stderr, "blad alokacji pamieci");
            break;
        }
        if( List_isFull2(films) ){
            puts("Lista pelna");
            break;
        }
        puts("podaj nastepny tytul filmu: (pusty wiersz konczy wpisywanie)");
    }
    if( List_isEmpty2(films) )
        printf("nie wpisano zadnych danych");
    else{
        printf("oto utworzona lista: \n");
        List_move2( films, Show_film );
    }
    printf("\n lista zawiera %u pozycji \n", List_PositionNumber2(films));

    List_clear2(films);
    printf("bye!\n");

    getchar();
    
	/*
    while( true ){
	uint32_t led_num = 30;
	float bright = 0;
	const float MIN_SPEED = 0.2f;
	const float MAX_SPEED = 1.0f;
	const float STEP = 1;
	const float SIZE = 20;
	const float BRIGHT_STEP = 1.0f/(SIZE);
	static float pos = 0;


	for(uint16_t i = 0; i < 30; i++){
		if ( i == (led_num - (int32_t)pos) ){	//max brigtness
			uint8_t r = 250;
		}else if( i < (led_num - (int32_t)pos) ){ //set dark in front of comet
			uint8_t r = 250;
		}else if( i > (led_num - (int32_t)pos) ){ //set tail of the commet
			bright += BRIGHT_STEP;
			if(bright <= 1){
				uint8_t r = 250 * (1-bright);
			}else{
                uint8_t r = 250;
			}
		}
	}
	pos+=STEP;
	if( pos >= (led_num + SIZE))
		pos = 0;
    }
	*/
    return 0;
}

char *Load_data( char *z, int num ){
    char *wynik;
    char *tutaj;
    wynik = fgets(z, num, stdin);
    if(wynik){
        tutaj = strchr( z, '\n' );
        if( tutaj )
            *tutaj = '\0';
        else
        {
            while( getchar() != '\n' )
                continue;
        }
        
    }
    return wynik;
}

void Show_film( Position position ){
    printf( "Film: %s Ocena: %d\n", position.title, position.note);
}