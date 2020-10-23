#ifndef POKEMON_H
#define POKEMON_H
#include "mapper.h"
#include <math.h>

//------------------------------------------------
//Constantes
static const int HEALTH = 1500;
static const double BONUS = 2.3;

//------------------------------------------------
//Estructuras
typedef struct pokemon{

	int threadID;
	int health;
	int pokemonID;
	char *speciesName;
	size_t energy;

	//-----------------
	//type
	int typeID;
	char* typeName;

	//-----------------
	//Moves
	int fastMoveID;
	char* fastMoveName;
	int chargedMoveID;
	char* chargedMoveName;
	
}pokemon_t;

//------------------------------------------------
//Mètodos
pokemon_t* pokemon_create(int threadID, int pokemonID);
int dead_pokemon_next_pokemon(int pokemon_actual);

void*run(void* args);

void pokemon_destroy(pokemon_t* pokemon);
int calculate_damage(int attack_move_id, int target_pokemonID, int attacking_pokemonID);


#endif
