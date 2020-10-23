#ifndef GAMEMASTER_H
#define GAMEMASTER_H
#include <pthread.h>
#include <semaphore.h>
#include "Pokemon.h"
#include "mapper.h"
#include "Player.h"
#include "../view/interfaz.h"

typedef struct pokemon_shared_data{
    double battle_duration;
    size_t charged_attack_on;
    size_t continue_battle;
    pthread_barrier_t waiting_area;
    pthread_cond_t cond_charged_attack;
    pthread_mutex_t fight_area;
    pthread_mutex_t charged_attack_area;

}pokemon_shared_data_t;

typedef struct timespec walltime_t;

typedef struct pokemon_data{
      
      size_t pokemon_in_arena;
      double time_pokemon_battle;
      player_t * player;
      player_t * enemy_player;
      pokemon_t * pokemon;
      walltime_t* walltime;
      pokemon_shared_data_t * pokemon_shared_data;

}pokemon_data_t;


int iniciar_Juego();
void walltime_start(walltime_t* start);
double walltime_elapsed(const walltime_t* start);
void * add_Pokemon(int id);
void * star_battle();
void * initiate();
void * show_results();

#endif
