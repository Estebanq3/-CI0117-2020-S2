#ifndef INTERFAZ
#define INTERFAZ

#include <pthread.h>
#include "../model/GameMaster.h"

char *getPokemonName(int i);
char *getPlayerName(int i);

void setFinalStatsPokemon(char *pokemon_name, double pokemon_time, int health, int num_pokemon);
void setFinalTime(double total_time);
void setResult(char *resultado, int num_player, char *name_player);
void showFinalStats();
void setActualAttack(char *pokemon_name, char *pokemon_attack_name, int num_player);
void setPlayersNames(char* name1, char* name2);
void setPokemonNames(char* name, char* estado, int pokemon_in_arena);
void setActivePokemon(char* name, int num_player);
void setPokemonHealth(int health, int num_player);
void setPokemonEnergy(int energy, int num_player);
void ultimatePower(int ultimate_energy, int num_player);

#endif
