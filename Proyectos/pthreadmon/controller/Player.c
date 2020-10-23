#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "../model/Player.h"

player_t* player_create(size_t num_player, char nombreDeJugador[25]){

  	//Pedimos memoria para el pokemon
  	player_t* player = calloc(1,sizeof(player_t));

    //--------------------------------------------------
  	//Recuperamos valores de la entrada del usuario
    player->name = nombreDeJugador;

  	//--------------------------------------------------
  	//Esto para que nosotros le asignemos su numero respectivo al jugador
  	player->num_player = num_player;
  	player->actual_Pokemon = 0;
  	pthread_cond_init(&player->team_cond, NULL);
  	pthread_mutex_init(&player->team_mutex, NULL);

  	return player;
}

int assign_pokemon_interfaz(player_t* player,char pokemonName1[],char pokemonName2[], char pokemonName3[]){ 

    size_t chosen_pokemons = 0;
    char *pokemon_name;
    size_t agregar = 1;
    size_t seguir = 1;

    while (chosen_pokemons < 3 && seguir == 1){
        if(chosen_pokemons == 0){
          pokemon_name = pokemonName1;
        }
        else{
          if(chosen_pokemons == 1){
            pokemon_name = pokemonName2;
          }
          else{
            if(chosen_pokemons == 2){
              pokemon_name = pokemonName3;
            }
          }
        }

        if(strlen(pokemon_name) < 15 && strlen(pokemon_name) >= 3){

            for(int i = 0; i < 50; i++){
                
                if( strcmp(pokemon_name, get_pokemon_species_name(i)) == 0){
                    for(int j = 0; j < chosen_pokemons; j++){
                        if(strcmp(pokemon_name,player->player_pokemons[j]->speciesName) == 0){
                            seguir = 0;
                            //printf("Pokemon ya seleccionado, elija uno nuevo\n");
                            agregar = 0;

                            for( int h = 0; h < chosen_pokemons; h++){ //Borra los pokemones creados hasta el momento en caso de ingresar nombres invalidos
                              pokemon_destroy(player->player_pokemons[h]);
                            }

                            return 0;
                        }
                        else{
                          agregar = 1;
                        }
                    }

                    if(agregar == 1){
                        player->player_pokemons[chosen_pokemons] = pokemon_create(chosen_pokemons, i);
                        chosen_pokemons++;
                    }
                    i = 49;
                      
                }
                else{
                    if(i == 49){
                      //printf("Ingrese un nuevo pokemon con nombre valido\n");
                      seguir = 0;
                      for( int h = 0; h < chosen_pokemons; h++){
                        pokemon_destroy(player->player_pokemons[h]);
                      }
                      return 0;
                    }
                }

            }

        }else{
           //printf("Ingrese un nombre valido\n");
           seguir = 0;
           for( int h = 0; h < chosen_pokemons; h++){
              pokemon_destroy(player->player_pokemons[h]);
           }
           return 0;
        }
    }  

  return 1;
}

void player_destroy(player_t* player){
	pthread_cond_destroy(&player->team_cond);
	pthread_mutex_destroy(&player->team_mutex);
	free(player);
}


