#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../model/GameMaster.h"


void *mortal_combat(void *args){

	size_t sleep_time;

    //----------------------------------------------------------------
    //Recuperacion de pokemon_shared_data y data de cada pokemon
    pokemon_data_t* data = (pokemon_data_t*)args;
    pokemon_shared_data_t* shared_data = data->pokemon_shared_data;

    //----------------------------------------------------------------
    //Espera a que todos los hilos esten en esta zona para iniciar con los combates
 	printf("Ha llegado: %s\n", data->pokemon->speciesName);
    pthread_barrier_wait(&shared_data->waiting_area);
    
    pthread_mutex_lock(&data->player->team_mutex);

    while(data->pokemon->threadID != data->player->actual_Pokemon){ //Verifica si es el turno de pelear del pokemon y si no es su turno lo pone a dormir
         pthread_cond_wait(&data->player->team_cond, &data->player->team_mutex);
    }

    //-----------------------------------------------------------------------------------------------------------------
    //inicio de peleas
    walltime_start(data->walltime);

    if(shared_data->continue_battle == 1){
        setActivePokemon(get_pokemon_species_name(data->pokemon->pokemonID), data->player->num_player);
        ultimatePower(get_move_energy(get_pokemon_charged_move_id(data->pokemon->pokemonID)), data->player->num_player);
    }

    while (data->pokemon->health > 0 && shared_data->continue_battle != 0 ) {

    	if (data->pokemon->energy >= get_move_energy(get_pokemon_charged_move_id(data->pokemon->pokemonID))) {
            	
            	pthread_mutex_lock(&shared_data->charged_attack_area); //Bloquea la zona para que mientras se realice un ataque cargado no se pueda llevar a cabo otro a la vez         

                //Comprueba que el pokemon y su enemigo aun tengan vida para ver si es posible llevar a cabo el ataque
	            if(data->enemy_player->player_pokemons[data->enemy_player->actual_Pokemon]->health > 0 && data->player->player_pokemons[data->player->actual_Pokemon]->health > 0){

	            	shared_data->charged_attack_on = 1; //condicional para que mientras se realice un ataque cargado no se pueda llevar a cabo un ataque rapido
                		
	                printf("***************** Atque cargado %s de: %s *****************\n", get_move_name(get_pokemon_charged_move_id(data->pokemon->pokemonID)), data->pokemon->speciesName);

                    data->enemy_player->player_pokemons[data->enemy_player->actual_Pokemon]->health -= calculate_damage(get_pokemon_charged_move_id(data->pokemon->pokemonID),data->enemy_player->player_pokemons[data->enemy_player->actual_Pokemon]->pokemonID,data->pokemon->pokemonID) ;
                    
                    setActualAttack(get_pokemon_species_name(data->pokemon->pokemonID),get_move_name(get_pokemon_charged_move_id(data->pokemon->pokemonID)), data->player->num_player);
                    setPokemonHealth(data->pokemon->health , data->player->num_player); //Muestra la vida en la interfaz
                    
                    pthread_mutex_unlock(&shared_data->charged_attack_area);
	                shared_data->charged_attack_on = 0;
	                pthread_cond_broadcast(&shared_data->cond_charged_attack);
	                data->pokemon->energy -= get_move_energy(get_pokemon_charged_move_id(data->pokemon->pokemonID));
	                setPokemonEnergy(data->pokemon->energy , data->player->num_player);
                    printf("Pokemon: %s, Energia actual: %ld, Energia a ganar: %d vida: %d\n ", data->pokemon->speciesName, data->pokemon->energy,get_move_energy_gain(get_pokemon_charged_move_id(data->pokemon->pokemonID)), data->pokemon->health);
	                sleep_time = get_move_cooldown(get_pokemon_charged_move_id(data->pokemon->pokemonID));
	                usleep(sleep_time*1000);
	            }
	            else{

	            	pthread_mutex_unlock(&shared_data->charged_attack_area);
	            }
        }
        else{
                pthread_mutex_lock(&shared_data->fight_area);
        		while(shared_data->charged_attack_on == 1){ //Duerme los hilos que lleguen si se esta llevando a cabo un ataque cargado
        			pthread_cond_wait(&shared_data->cond_charged_attack, &shared_data->fight_area);
        		}
                pthread_mutex_unlock(&shared_data->fight_area);

                if(data->enemy_player->player_pokemons[data->enemy_player->actual_Pokemon]->health > 0 && data->player->player_pokemons[data->player->actual_Pokemon]->health > 0){
                    
                    printf("----------------- Ataque ràpido %s de: %s -----------------\n", get_move_name(get_pokemon_fast_move_id(data->pokemon->pokemonID)), data->pokemon->speciesName);
                    data->enemy_player->player_pokemons[data->enemy_player->actual_Pokemon]->health -= calculate_damage(get_pokemon_fast_move_id(data->pokemon->pokemonID),data->enemy_player->player_pokemons[data->enemy_player->actual_Pokemon]->pokemonID,data->pokemon->pokemonID);
                    
                    setActualAttack(get_pokemon_species_name(data->pokemon->pokemonID),get_move_name(get_pokemon_fast_move_id(data->pokemon->pokemonID)), data->player->num_player);
                    setPokemonHealth(data->pokemon->health , data->player->num_player);
                    
                    data->pokemon->energy += get_move_energy_gain(get_pokemon_fast_move_id(data->pokemon->pokemonID));
                    setPokemonEnergy(data->pokemon->energy , data->player->num_player);
                    printf("Pokemon: %s, Energia: %ld, Energia a ganar: %d vida: %d\n ", data->pokemon->speciesName, data->pokemon->energy, get_move_energy_gain(get_pokemon_fast_move_id(data->pokemon->pokemonID)), data->pokemon->health);
                    sleep_time = get_move_cooldown(get_pokemon_fast_move_id(data->pokemon->pokemonID));
					usleep(sleep_time*1000);
                }
                
        }

        if(data->pokemon->health <= 0){
            setPokemonHealth(0, data->player->num_player); //Los pokemones con vida menor a 0 para el area de la simulacion pokemon en la interfaz se les presenta con vida 0
            setPokemonNames(getPokemonName(data->pokemon_in_arena),"Debilitado", data->pokemon_in_arena); // Si su vida es menor o igual a 0 lo muestra como un pokemon debilitado
        }


    }
    printf("+++++++++++++++++ Se ha debilitado: %s +++++++++++++++++\n", data->pokemon->speciesName);

    if(shared_data->continue_battle == 0){
        setResult("Ganador", data->player->num_player, data->player->name); //Si ya la batalla termino se establece un ganador
    }

    if((data->player->actual_Pokemon+1) == 3){
            shared_data->continue_battle = 0; //si ya es el ultimo pokemon entonces detiene la batalla
            if(data->pokemon->health <= 0){
                setResult("Perdedor", data->player->num_player, data->player->name); //si es el ultimo pokemon de un jugador y no tiene vida es porque ese jugador es el perdedor
            }
    }else{
        data->player->actual_Pokemon++; //mientras no sea el ultimo pokemon del jugador hace que salga a luchar el siguiente
    }

    pthread_mutex_unlock(&data->player->team_mutex);
    pthread_cond_broadcast(&data->player->team_cond); //Se libera el siguiente pokemon a luchar
 
    printf("Pokemon: %s, Vida: %d, energia: %ld, PokemonActual: %ld \n", data->pokemon->speciesName, data->pokemon->health, data->pokemon->energy, data->player->actual_Pokemon-1);

    data->time_pokemon_battle = walltime_elapsed(data->walltime);
    setFinalStatsPokemon(get_pokemon_species_name(data->pokemon->pokemonID), data->time_pokemon_battle, data->pokemon->health, data->pokemon_in_arena);

    printf("++++++++++++++++++++++++++++++++++ TIEMPO BATALLADO por %s: %f ++++++++++++++++++++++++++++++++++\n",data->pokemon->speciesName, data->time_pokemon_battle);

    return NULL;
}


//---------------------------------------------------------------------------------
//Tiempo 
void walltime_start(walltime_t* start){
    clock_gettime(CLOCK_MONOTONIC,start);
}
double walltime_elapsed(const walltime_t* start){
    walltime_t finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsed = (finish.tv_sec - start->tv_sec);
    elapsed += (finish.tv_nsec - start->tv_nsec) / 1000000000.0;
    return elapsed;
}

//---------------------------------------------------------------------------------
//Main
int iniciar_Juego(){

    //Para controlar el tiempo que tarda cada pokemon en pelea
    walltime_t* walltime1 = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_t* walltime2 = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_t* walltime3 = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_t* walltime4 = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_t* walltime5 = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_t* walltime6 = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_t* walltime7 = (walltime_t*)calloc(1, sizeof (walltime_t));

/*------------------------------------------------------------------------------------------------------------
Inicializacion*/

    initialize_data();

//------------------------------------------------------------------------------------------------------------
    //Inicializando jugadores
    player_t* player_one = player_create(1, getPlayerName(1));
    int continuar1 = assign_pokemon_interfaz(player_one,getPokemonName(1),getPokemonName(2),getPokemonName(3));

    if (continuar1 == 1 && player_one->num_player !=-1){ //si los pokemones y el jugador era valido entonces pide los datos del jugador 2
        
        player_t* player_two = player_create(2,getPlayerName(2));
        int continuar2 = assign_pokemon_interfaz(player_two,getPokemonName(4),getPokemonName(5),getPokemonName(6));

     //---------------------------------------------------------------------------------------------------------------
        if(continuar2 == 1 && player_two->num_player !=-1){ //si los pokemones y el jugador era valido entonces prepara todo para la batalla pokemon
                
                setPlayersNames(getPlayerName(1),getPlayerName(2));
                
                for(int i = 1; i < 7; i++){ //Pone todos los pokemones en habilitado ya que estan full vida
                    setPokemonNames(getPokemonName(i),"Habilitado",i);
                }

                //Solicitud de espacio
                pokemon_shared_data_t *pokemon_shared_data = (pokemon_shared_data_t *)malloc(sizeof(pokemon_shared_data_t));
                pokemon_data_t *pokemon_data = (pokemon_data_t *) malloc(POKEMONS_PER_PLAYER* sizeof(pokemon_data_t));
                pokemon_data_t *pokemon_data2 = (pokemon_data_t *) malloc(POKEMONS_PER_PLAYER* sizeof(pokemon_data_t));

            //---------------------------------------------------------------------------------------------------------------
                //Inicializacion de pokemon_shared_data
                pokemon_shared_data->continue_battle = 1;

            //Inicializando Metodos de sincronizaciòn
                pthread_mutex_init(&pokemon_shared_data->charged_attack_area, NULL);
                pthread_mutex_init(&pokemon_shared_data->fight_area, NULL);
                pthread_cond_init(&pokemon_shared_data->cond_charged_attack, NULL);
                pthread_barrier_init(&pokemon_shared_data->waiting_area,NULL,(POKEMONS_PER_PLAYER*2));

            //--------------------------------------------------------------------------------------------------------------
                //Creacion de hilos y asignaciòn
                //Threads/Pokemon de cada player 0-2
                pthread_t* pokemon_threadsP1 = malloc(POKEMONS_PER_PLAYER * sizeof(pthread_t));
                pthread_t* pokemon_threadsP2 = malloc(POKEMONS_PER_PLAYER * sizeof(pthread_t));

                walltime_start(walltime1);//Inicia a contar el tiempo que tarda la batalla

                //-------------------------------------------------------------------------------
                //Jugador1
                pokemon_data[0].walltime = walltime2;
                pokemon_data[1].walltime = walltime3;
                pokemon_data[2].walltime = walltime4;

              
                for(int i = 0; i < POKEMONS_PER_PLAYER; i++){
                    pokemon_data[i].pokemon_in_arena = i+1;
                    pokemon_data[i].player = player_one;
            	    pokemon_data[i].enemy_player = player_two;
                    printf("Nombre 1: %s\n", pokemon_data[i].player->name);
                    pokemon_data[i].pokemon = player_one->player_pokemons[i];
                    printf("Pokemones 1: %s\n",pokemon_data[i].pokemon->speciesName);
                    pokemon_data[i].pokemon_shared_data = pokemon_shared_data;
                    pthread_create(&pokemon_threadsP1[i],NULL,mortal_combat,(void*)&pokemon_data[i]);
                }
            //-------------------------------------------------------------------------------
                //Jugador 2
                
                pokemon_data2[0].walltime = walltime5;
                pokemon_data2[1].walltime = walltime6;
                pokemon_data2[2].walltime = walltime7;


                for(int i = 0; i < POKEMONS_PER_PLAYER; i++){
                    pokemon_data2[i].pokemon_in_arena = POKEMONS_PER_PLAYER+(i+1);
                    pokemon_data2[i].player = player_two;
            	    pokemon_data2[i].enemy_player = player_one;
                    printf("Nombre 2: %s\n", pokemon_data2[i].player->name);
                    pokemon_data2[i].pokemon = player_two->player_pokemons[i];
                    printf("Pokemones 2: %s\n",pokemon_data2[i].pokemon->speciesName);
                    pokemon_data2[i].pokemon_shared_data = pokemon_shared_data;
                    pthread_create(&pokemon_threadsP2[i],NULL,mortal_combat,(void*)&pokemon_data2[i]);
                }


            //-------------------------------------------------------------------------------
                //Join
                for(int i = 0; i < POKEMONS_PER_PLAYER; i++){
                    pthread_join(pokemon_threadsP1[i],NULL);
                }
                for(int i = 0; i < POKEMONS_PER_PLAYER; i++){
                    pthread_join(pokemon_threadsP2[i],NULL);
                }

                double time = walltime_elapsed(walltime1);
                pokemon_shared_data->battle_duration = time;
                printf("++++++++++++++++++++++++++++++++++++++++++++++ TIEMPO TOTAL DE LA BATALLA: %f ++++++++++++++++++++++++++++++++++++++++++++++\n", pokemon_shared_data->battle_duration);
                setFinalTime(pokemon_shared_data->battle_duration); //Asigna el tiempo que duro ltoda a batalla pokemon
            //--------------------------------------------------------------------------------------------------------------
                //Destruccion para liberar memoria
                pthread_mutex_destroy(&pokemon_shared_data->charged_attack_area);
                pthread_mutex_destroy(&pokemon_shared_data->fight_area);
                pthread_cond_destroy(&pokemon_shared_data->cond_charged_attack);
                pthread_barrier_destroy(&pokemon_shared_data->waiting_area);
                free(pokemon_shared_data);
                free(pokemon_data);
                free(pokemon_data2);

                for(int i = 0; i < 3; i++){ 
                    pokemon_destroy(player_two->player_pokemons[i]);
                }
        }
        player_destroy(player_two);

        for(int i = 0; i < 3; i++){ 
            pokemon_destroy(player_one->player_pokemons[i]);
        }
    }

    showFinalStats();

    free(walltime1);
    free(walltime2);
    free(walltime3);
    free(walltime4);
    free(walltime5);
    free(walltime6);
    free(walltime7);
    player_destroy(player_one);
    
    return 0;

}
