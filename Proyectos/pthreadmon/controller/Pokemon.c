#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../model/Pokemon.h"

pokemon_t* pokemon_create(int threadID, int pokemonID){

	//Pedimos memoria para el pokemon
	pokemon_t* pokemon = calloc(1,sizeof(pokemon_t));

	//Recuperamos valores
	//--------------------------------------------------
	pokemon->threadID = threadID;
	pokemon->health = HEALTH;
	pokemon->pokemonID = pokemonID;
	pokemon->speciesName = get_pokemon_species_name(pokemonID);
	pokemon->fastMoveID = get_pokemon_fast_move_id(pokemonID);
	pokemon->chargedMoveID= get_pokemon_charged_move_id(pokemonID);
	pokemon->typeID = get_pokemon_type_id(pokemonID);
	pokemon->fastMoveName = get_move_name(pokemon->fastMoveID);
	pokemon->typeName = get_type_name(pokemon->typeID);
	pokemon->energy = 0;

	return pokemon;
}

int dead_pokemon_next_pokemon(int pokemon_actual){
	pokemon_actual++;
	return pokemon_actual;
}

int calculate_damage(int attack_move_id, int target_pokemonID, int attacking_pokemonID){

	//----------------------------------------------------------------------------
	//Efectividad
	double efective = 0;
	if (weaknesses_matrix[get_pokemon_type_id(target_pokemonID)][get_pokemon_type_id(attacking_pokemonID)]) {
    	efective = 1.6;
	} else if (resistances_matrix[get_pokemon_type_id(target_pokemonID)][get_pokemon_type_id(attacking_pokemonID)]) {
    	efective = 0.625;
	} else if ( immunities_matrix[get_pokemon_type_id(target_pokemonID)][get_pokemon_type_id(attacking_pokemonID)]) {
    	efective = 0.390625;
	} else { // ninguno de los anteriores
    	efective = 1;
	}
	//----------------------------------------------------------------------------
	return floor(get_move_power(attack_move_id)*efective*2.3)+1;
}


void pokemon_destroy(pokemon_t* pokemon){
	free(pokemon);
}


