#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "interfaz.h"
#include "../model/GameMaster.h"
#include "../model/mapper.h"

#define ENTRADA 25
#define MAX_ENTRY 25

//Los cuadros para recibir datos, de entrada
GtkWidget *player1;
GtkWidget *player2;

GtkWidget *Pokemon1P1;
GtkWidget *Pokemon2P1;
GtkWidget *Pokemon3P1;

GtkWidget *Pokemon1P2;
GtkWidget *Pokemon2P2;
GtkWidget *Pokemon3P2;

//Muestra datos-------------------------------------
GtkWidget *label_ganadorBattle;
GtkWidget *label_ganador;

//Variables de la ventana y labels, boton
GtkWidget *ventana;
GtkWidget *ventana2;
GtkWidget *ventana3;
GtkWidget *descripcion[35]; //labels que llevan descripciones
GtkWidget *grid;
GtkWidget *grid2;
GtkWidget *grid3;
GtkWidget *boton;
GtkWidget *showFightButton;

//--------------------------------------------------------------------------------------
//vectores de char utilizados para controlar los datos de la interfaz 
char name_player1[25];
char name_player2[25];
char name_pokemon1P1[25];
char name_pokemon2P1[25];
char name_pokemon3P1[25];
char name_pokemon1P2[25];
char name_pokemon2P2[25];
char name_pokemon3P2[25];

//---------------------------------------------------------------------------------------
//vectores para controlar los resultados finales
char finall_player1[25];
char finall_player2[25];
char pokemon1[200];
char pokemon2[200];
char pokemon3[200];
char pokemon4[200];
char pokemon5[200];
char pokemon6[200];
char pokemon1_actual[200];
char pokemon2_actual[200];
char pokemon1_health[200];
char pokemon2_health[200];
char pokemon1_energy[200];
char pokemon2_energy[200];

//---------------------------------------------------------------------------------------
//vectores para controlar los set
char pokemon[200];
char pokemon1_ultimate_energy[200];
char pokemon2_ultimate_energy[200];
char actual_attack[200];
char result_player[200];
char duracion_total_pelea[200];
char final_pokemon[200];


//Metodos set y get
void setPokemonNames(char* name, char* estado, int pokemon_in_arena){
	sprintf(pokemon, "%s\n(%s)", name, estado);
	gtk_label_set_text (GTK_LABEL(descripcion[pokemon_in_arena]),pokemon);
}

void setPlayersNames(char* name1, char* name2){
	gtk_label_set_text (GTK_LABEL(descripcion[25]),(const gchar*)name1);
	gtk_label_set_text (GTK_LABEL(descripcion[26]),(const gchar*)name2);	
}


char *getPokemonName(int i){

	if(i==1){
		return name_pokemon1P1;
	}
	else if(i==2){
		return name_pokemon2P1;
	}
	else if(i==3){
		return name_pokemon3P1;
	}
	else if(i==4){
		return name_pokemon1P2;
	}
	else if(i==5){
		return name_pokemon2P2;
	}
	else if(i==6){
		return name_pokemon3P2;
	}

	return NULL;
}

char *getPlayerName(int i){

	if(i==1){
		return name_player1;
	}
	else if(i==2){
		return name_player2;
	}

	return NULL;
}
 
//En estos metodos set guarda en un "string" los valores a almacenar en los labels correspondientes

void setActivePokemon(char* name, int num_player){
	if(num_player == 1){
		sprintf(pokemon1_actual, "Pokemon activo:  %s", name);
		gtk_label_set_text (GTK_LABEL(descripcion[8]),pokemon1_actual);
	}
	else{
		sprintf(pokemon2_actual, "Pokemon activo:  %s", name);
		gtk_label_set_text (GTK_LABEL(descripcion[12]),pokemon2_actual);
	}
}

void setPokemonHealth(int health, int num_player){
	
	if(num_player == 1){
		sprintf(pokemon1_health, "Vida:  %d", health);
		gtk_label_set_text (GTK_LABEL(descripcion[9]),pokemon1_health);
	}
	else{
		sprintf(pokemon2_health, "Vida:  %d", health);
		gtk_label_set_text (GTK_LABEL(descripcion[13]),pokemon2_health);
	}

}

void setPokemonEnergy(int energy, int num_player){

	if(num_player == 1){
		sprintf(pokemon1_energy, "Energia acumulada:  %d", energy);
		gtk_label_set_text (GTK_LABEL(descripcion[10]),pokemon1_energy);
	}
	else{
		sprintf(pokemon2_energy, "Energia acumulada:  %d", energy);
		gtk_label_set_text (GTK_LABEL(descripcion[14]),pokemon2_energy);
	}

}

void ultimatePower(int ultimate_energy, int num_player){

	if(num_player == 1){
		sprintf(pokemon1_ultimate_energy, "Ultimate_energy:  %d", ultimate_energy);
		gtk_label_set_text (GTK_LABEL(descripcion[11]),pokemon1_ultimate_energy);
	}
	else{
		sprintf(pokemon2_ultimate_energy, "Ultimate_energy:  %d", ultimate_energy);
		gtk_label_set_text (GTK_LABEL(descripcion[15]),pokemon2_ultimate_energy);
	}
}

void setActualAttack(char *pokemon_name, char *pokemon_attack_name, int num_player){
	sprintf(actual_attack, "Ataque actual \n Player: %d\n %s \n %s", num_player, pokemon_name, pokemon_attack_name);
	gtk_label_set_text (GTK_LABEL(descripcion[16]),actual_attack);
}


void setFinalStatsPokemon(char *pokemon_name, double pokemon_time, int health, int num_pokemon){
	
	/*Se hace un switch para controlar con cual pokemon se està trabajando donde estan ordenados de 1 a 6 por comodidad en donde los pokemones del
	1-3 corresponden a los del primer jugador y del 4 al 6 al segundo jugador*/
	switch (num_pokemon){
    case 1:
    	sprintf(pokemon1, "Pokemonx: %s\nVida: %d\nTiempo luchado: %f ", pokemon_name, health, pokemon_time);
      break;
    case 2:
    	sprintf(pokemon2, "Pokemon: %s\nVida: %d\nTiempo luchado: %f ", pokemon_name, health, pokemon_time);
      break;
    case 3:
    	sprintf(pokemon3, "Pokemon: %s\nVida: %d\nTiempo luchado: %f ", pokemon_name, health, pokemon_time);
      break;
    case 4:
    	sprintf(pokemon4, "Pokemon: %s\nVida: %d\nTiempo luchado: %f ", pokemon_name, health, pokemon_time);
      break;
    case 5:
    	sprintf(pokemon5, "Pokemon: %s\nVida: %d\nTiempo luchado: %f ", pokemon_name, health, pokemon_time);
      break;
    case 6:
    	sprintf(pokemon6, "Pokemon: %s\nVida: %d\nTiempo luchado: %f ", pokemon_name, health, pokemon_time);
      break;
	}
		
}

void setFinalTime(double total_time){
	sprintf(duracion_total_pelea, "Tiempo total: %f", total_time);
}

void setResult(char *resultado, int num_player, char *name_player){
	
	if(num_player == 1){ 
		sprintf(finall_player1, "%s\n Player %d\n %s",resultado, num_player, name_player); //En caso de que sea el jugador 1
	}else{
		sprintf(finall_player2, "%s\n Player %d\n %s",resultado, num_player, name_player); //En caso de que sea el jugador 2
	}
}

void showFinalStats(){

	//Muestra la ventana y sus widgets
	gtk_widget_show(ventana3);
	gtk_widget_show_all(ventana3);

	//Asigna a los labels los valores correspondientes
	gtk_label_set_text (GTK_LABEL(descripcion[34]),finall_player1);
	gtk_label_set_text (GTK_LABEL(descripcion[35]),finall_player2);
	gtk_label_set_text (GTK_LABEL(descripcion[27]),pokemon1);
	gtk_label_set_text (GTK_LABEL(descripcion[28]),pokemon2);
	gtk_label_set_text (GTK_LABEL(descripcion[29]),pokemon3);
	gtk_label_set_text (GTK_LABEL(descripcion[30]),pokemon4);
	gtk_label_set_text (GTK_LABEL(descripcion[31]),pokemon5);
	gtk_label_set_text (GTK_LABEL(descripcion[32]),pokemon6);
	gtk_label_set_text (GTK_LABEL(descripcion[33]),duracion_total_pelea);
}

//-----------------------------------------------------------------------------------------
//Async
static void start_async(GTask *task, gpointer source_object,gpointer task_data, GCancellable *cancellable){
    iniciar_Juego();
}

static void my_callback(GObject *source_object, GAsyncResult *res,gpointer user_data){}

//----------------------------------------------------------------------------------------
//Action Button
static void accion_boton()
{
	sscanf(gtk_entry_get_text(GTK_ENTRY(player1)), "%s", name_player1);
	sscanf(gtk_entry_get_text(GTK_ENTRY(player2)), "%s", name_player2);

	//POkemones Player 1-------------------------------------------------------
	sscanf(gtk_entry_get_text(GTK_ENTRY(Pokemon1P1)), "%s", name_pokemon1P1);
	sscanf(gtk_entry_get_text(GTK_ENTRY(Pokemon2P1)), "%s", name_pokemon2P1);
	sscanf(gtk_entry_get_text(GTK_ENTRY(Pokemon3P1)), "%s", name_pokemon3P1);
	
	//POkemones Player 2-------------------------------------------------------
	sscanf(gtk_entry_get_text(GTK_ENTRY(Pokemon1P2)), "%s", name_pokemon1P2);
	sscanf(gtk_entry_get_text(GTK_ENTRY(Pokemon2P2)), "%s", name_pokemon2P2);
	sscanf(gtk_entry_get_text(GTK_ENTRY(Pokemon3P2)), "%s", name_pokemon3P2);
	
	gtk_widget_hide(ventana);
	gtk_widget_show(ventana2);
	gtk_widget_show_all(ventana2);

    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
}

static void show_hiden_window(){
	gtk_widget_show(ventana);

	gtk_label_set_text(GTK_LABEL(descripcion[8]), "PokemonActivoP1");
	gtk_label_set_text(GTK_LABEL(descripcion[9]), "Vida:");
	gtk_label_set_text(GTK_LABEL(descripcion[10]), "Energia:");
	gtk_label_set_text(GTK_LABEL(descripcion[11]), "EnergiaUltimate:");

	gtk_label_set_text(GTK_LABEL(descripcion[12]), "PokemonActivoP2");
	gtk_label_set_text(GTK_LABEL(descripcion[13]), "Vida:");
	gtk_label_set_text(GTK_LABEL(descripcion[14]), "Energia:");
	gtk_label_set_text(GTK_LABEL(descripcion[15]), "EnergiaUltimate:");

	gtk_label_set_text(GTK_LABEL(descripcion[16]), "AtaqueActual:");

	sprintf(duracion_total_pelea,"DuracionTotalPelea");
	sprintf(finall_player1,"Player1");
	sprintf(finall_player2,"Player2");
	sprintf(pokemon1,"Pokemon1P1");
	sprintf(pokemon2,"Pokemon2P1");
	sprintf(pokemon3,"Pokemon3P1");
	sprintf(pokemon4,"Pokemon1P2");
	sprintf(pokemon5,"Pokemon2P2");
	sprintf(pokemon6,"Pokemon3P2");
	
	gtk_widget_hide(ventana3);
	gtk_widget_hide(ventana2);
}

//---------------------------------------------------------------------------------
//FOndo de pantalla

//--------------------------------------------------------------------------------------
int main(int argc, char**argv){
	

//------------------------------------------------------------------------------------------------------------
// Init de GTK
	gtk_init(&argc, &argv); //inicializa Gtk, no damos parametros pero esta funcion nos exige estos parametros
	

//------------------------------------------------------------------------------------------------
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creamos ventana, como objeto
	g_signal_connect(ventana, "destroy",G_CALLBACK(gtk_main_quit),NULL); //ventana, emite señal
	gtk_window_set_title(GTK_WINDOW(ventana), "Informacion");
	gtk_container_set_border_width(GTK_CONTAINER(ventana),0); //Ancho de los bordes
	gtk_window_set_position (GTK_WINDOW(ventana),GTK_WIN_POS_CENTER);

//-------------------------------------------------------------------------------------------------
//Creacion de segunda Ventana Batalla de Pokemones escenario
	ventana2 = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creamos ventana, como objeto
	g_signal_connect(ventana2, "destroy",G_CALLBACK(gtk_main_quit),NULL); //ventana, emite señal
	gtk_window_set_title(GTK_WINDOW(ventana2), "Simulacion Pokemon");
	gtk_container_set_border_width(GTK_CONTAINER(ventana2),0); //Ancho de los bordes
	gtk_window_set_position (GTK_WINDOW(ventana2),GTK_WIN_POS_CENTER);
//-------------------------------------------------------------------------------------------------
	ventana3 = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creamos ventana, como objeto
	g_signal_connect(ventana3, "destroy",G_CALLBACK(gtk_main_quit),NULL); //ventana, emite señal
	gtk_window_set_title(GTK_WINDOW(ventana3), "Resultados");
	gtk_container_set_border_width(GTK_CONTAINER(ventana3),0); //Ancho de los bordes

//***************************************************************************************
	gtk_window_set_default_size(GTK_WINDOW(ventana),600,400);//tamaño ventana 
	gtk_window_set_default_size(GTK_WINDOW(ventana2),600,350);//tamaño ventana 
	gtk_window_set_default_size(GTK_WINDOW(ventana3),600,350);//tamaño ventana 
//***************************************************************************************
	//Apariencia de la ventana 1 GRID
	grid = gtk_grid_new();
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    /* COlocando el grid en la ventana */
    gtk_container_add(GTK_CONTAINER(ventana), grid);


 //---------------------------------------------------------------------------------------
//Apariencia de la ventana2 GRID
    grid2 = gtk_grid_new();
	gtk_grid_set_row_homogeneous(GTK_GRID(grid2), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid2), TRUE);
    gtk_container_add(GTK_CONTAINER(ventana2), grid2);
    
   
//-----------------------------------------------------------------------------------------------------------
////Apariencia de la ventana3 GRID
    grid3 = gtk_grid_new();
	gtk_grid_set_row_homogeneous(GTK_GRID(grid3), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid3), TRUE);
    gtk_container_add(GTK_CONTAINER(ventana3), grid3);
    
   
//-----------------------------------------------------------------------------------------------------------
	//Creacion de las descripciones dentro de la ventana
	
	descripcion[0] = gtk_label_new("Player1:");
	descripcion[18] = gtk_label_new("Player2:");

	descripcion[19] = gtk_label_new("P1Pokemon1:");
	descripcion[20] = gtk_label_new("P1Pokemon2:");
	descripcion[22] = gtk_label_new("P1Pokemon3:");
	
	
	descripcion[23] = gtk_label_new("P2Pokemon1:");
	descripcion[24] = gtk_label_new("P2Pokemon2:");
	descripcion[7] = gtk_label_new("P2Pokemon3:");

	descripcion[8]  = gtk_label_new("PokemonActivoP1");
	descripcion[9]  = gtk_label_new("Vida:");
	descripcion[10] = gtk_label_new("Energia:");
	descripcion[11] = gtk_label_new("EnergiaUltimate:");

	descripcion[12] = gtk_label_new("PokemonActivoP2");
	descripcion[13] = gtk_label_new("Vida:");
	descripcion[14] = gtk_label_new("Energia:");
	descripcion[15] = gtk_label_new("EnergiaUltimate:");

	descripcion[16] = gtk_label_new("AtaqueActual:");

	descripcion[17] = gtk_label_new("");
	descripcion[21] = gtk_label_new("");

	descripcion[25] = gtk_label_new("P1");
	descripcion[26] = gtk_label_new("P2");

//----------------------------------------------------------------------------------------------------------
//Campo especial
	//Pokemones player 1
	descripcion[1] = gtk_label_new("");
	descripcion[2] = gtk_label_new("");
	descripcion[3] = gtk_label_new("");
	
	//Pokemones player 2
	descripcion[4] = gtk_label_new("");
	descripcion[5] = gtk_label_new("");
	descripcion[6] = gtk_label_new("");
//-----------------------------------------------------------------------------------------------------------
//Creacion de campos de ingreso
	player1  = gtk_entry_new();
	Pokemon1P1 = gtk_entry_new();
	Pokemon2P1 = gtk_entry_new();
	Pokemon3P1 = gtk_entry_new();
	
	player2  = gtk_entry_new();
	Pokemon1P2 = gtk_entry_new();
	Pokemon2P2 = gtk_entry_new();
	Pokemon3P2 = gtk_entry_new();
	
//----------------------------------------------------------------------
	//Labels de Estadìsticas Finales

	descripcion[27] = gtk_label_new("Pokemon1P1:");
	descripcion[28] = gtk_label_new("Pokemon2P1:");
	descripcion[29] = gtk_label_new("Pokemon3P1:");
	descripcion[30] = gtk_label_new("Pokemon1P2");
	descripcion[31] = gtk_label_new("Pokemon2P2");
	descripcion[32] = gtk_label_new("Pokemon3P2");
	descripcion[33] = gtk_label_new("DuracionTotalPelea:");
	descripcion[34] = gtk_label_new("Player1:");
	descripcion[35] = gtk_label_new("Player2:");
	
//-------------------------------------------------------------------------
	//Formato de nuestros campos de ingreso
	gtk_entry_set_max_length(GTK_ENTRY(player1),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(player2),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(Pokemon1P1),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(Pokemon2P1),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(Pokemon3P1),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(Pokemon1P2),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(Pokemon2P2),ENTRADA);
	gtk_entry_set_max_length(GTK_ENTRY(Pokemon3P2),ENTRADA);
	
//------------------------------------------------------------------------
	//Tamaño de campo de texto
	gtk_entry_set_width_chars(GTK_ENTRY(player1),25);
	gtk_entry_set_width_chars(GTK_ENTRY(player2),25);
	gtk_entry_set_width_chars(GTK_ENTRY(Pokemon1P1),11);
	gtk_entry_set_width_chars(GTK_ENTRY(Pokemon2P1),11);
	gtk_entry_set_width_chars(GTK_ENTRY(Pokemon3P1),11);

	gtk_entry_set_width_chars(GTK_ENTRY(Pokemon1P2),11);
	gtk_entry_set_width_chars(GTK_ENTRY(Pokemon2P2),11);
	gtk_entry_set_width_chars(GTK_ENTRY(Pokemon3P2),11);
	
	
	//----------------------------------------------------------------------
	//Creacion de boton con etiqueta que activa la funciòn
	boton = gtk_button_new_with_label("IniciarBatalla");
	g_signal_connect(boton,"clicked",G_CALLBACK(accion_boton),NULL); //accion boton es la funcion que va a realizar el boton, null es de que no se pasan parametros
	
	//Boton 2
	showFightButton = gtk_button_new_with_label("IniciarNuevamente");
	g_signal_connect(showFightButton,"clicked",G_CALLBACK(show_hiden_window),NULL);
//-------------------------------------------------------------------------------
	//primero mueve lados, segundo arriba, abajo
//****PARTE DE ENSAMBLAJE DE OBJETOS CREADOS, incluimos objetos a la ventana que hemos creado
	gtk_grid_attach(GTK_GRID(grid), descripcion[0],2,1,1,1);	 // colocar objetos que hemos creado en la ventana
	gtk_grid_attach(GTK_GRID(grid), player1,2,2,1,1);	 // colocar objetos que hemos creado en la ventana
	
	//LABELS DE: Primer jugador, y sus pokemones 
	gtk_grid_attach(GTK_GRID(grid), descripcion[19],2,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), Pokemon1P1,2,4,1,1);

	gtk_grid_attach(GTK_GRID(grid), descripcion[20],2,5,1,1);
	gtk_grid_attach(GTK_GRID(grid), Pokemon2P1,2,6,1,1);

	gtk_grid_attach(GTK_GRID(grid), descripcion[22],2,7,1,1);
	gtk_grid_attach(GTK_GRID(grid), Pokemon3P1,2,8,1,1);

	//LABELS DE: Segundo jugador, y sus pokemones 
	gtk_grid_attach(GTK_GRID(grid), descripcion[18],6,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), player2,6,2,1,1);

	gtk_grid_attach(GTK_GRID(grid), descripcion[23],6,3,1,1);
	gtk_grid_attach(GTK_GRID(grid), Pokemon1P2,6,4,1,1);

	gtk_grid_attach(GTK_GRID(grid), descripcion[24],6,5,1,1);
	gtk_grid_attach(GTK_GRID(grid), Pokemon2P2,6,6,1,1);

	gtk_grid_attach(GTK_GRID(grid), descripcion[7],6,7,1,1);
	gtk_grid_attach(GTK_GRID(grid), Pokemon3P2,6,8,1,1);
//-----------------------------------------------------------------
	//zona de pelea
//Pokemon 1 campo de batalla
	gtk_grid_attach(GTK_GRID(grid2), descripcion[25],1,10,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[8],2,11,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[9],2,12,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[10],2,13,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[11],2,14,1,1);
	

//Pokemon 2 campo de batalla
	gtk_grid_attach(GTK_GRID(grid2), descripcion[26],7,10,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[12],6,11,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[13],6,12,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[14],6,13,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[15],6,14,1,1);
	
	
//Ataque
	gtk_grid_attach(GTK_GRID(grid2), descripcion[16],4,10,1,1);
 
 //Pokemones activos P1
	gtk_grid_attach(GTK_GRID(grid2), descripcion[21],2,17,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[4],7,11,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[5],7,12,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[6],7,13,1,1);
	

//Pokemones activos P2	
	gtk_grid_attach(GTK_GRID(grid2), descripcion[17],6,17,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[1],1,11,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[2],1,12,1,1);
	gtk_grid_attach(GTK_GRID(grid2), descripcion[3],1,13,1,1);


 
//------------------------------------------------------------------------------
	//Attach al grid3 de los labels de estaisticas finales

	//nombre y Pokemones player3
	gtk_grid_attach(GTK_GRID(grid3), descripcion[34],1,3,1,1);	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[27],1,4,1,1);	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[28],1,5,1,1);	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[29],1,6,1,1);
	//nombre y Pokemones player 2
	gtk_grid_attach(GTK_GRID(grid3), descripcion[35],3,3,1,1);	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[30],3,4,1,1);	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[31],3,5,1,1);	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[32],3,6,1,1);
	//Tiempo global	
	gtk_grid_attach(GTK_GRID(grid3), descripcion[33],2,10,1,1);

//----------------------------------------------------------------------------
//Attach de los botones
	gtk_grid_attach(GTK_GRID(grid),boton,4,9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid3),showFightButton,2,11, 1, 1);

//---------------------------------------------------------------------------
	//Hacer visible la ventana:
	gtk_widget_show_all(ventana);
		
	//Cancela flujos de señales
	gtk_main();

	

	return 0;

}
