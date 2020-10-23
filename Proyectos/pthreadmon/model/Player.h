#ifndef PLAYER_H
#define PLAYER_H
#include <pthread.h>
#include "Pokemon.h"

//------------------------------------------------
//Constantes
#define POKEMONS_PER_PLAYER 3

//------------------------------------------------
//Estructuras
typedef struct player{

	char* name;
	size_t num_player;
	size_t actual_Pokemon;
	pokemon_t* player_pokemons[POKEMONS_PER_PLAYER];
	pthread_cond_t team_cond;	
	pthread_mutex_t team_mutex;	    
}player_t;

//-----------------------------------------------------------------------------------------
//Mètodos
player_t* player_create(size_t num_player,char nombreDeJugador[]);
void player_destroy(player_t* player);
void ask_information_player();
void show_information_player(player_t* player);
int assign_pokemon_interfaz(player_t* player,char pokemonName1[],char pokemonName2[], char pokemonName3[]);

#endif
