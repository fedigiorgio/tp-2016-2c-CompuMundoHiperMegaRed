/*
 * Mapa.h
 *
 *  Created on: 31/8/2016
 *      Author: utnso
 */

#ifndef MAPA_H_
#define MAPA_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "sockets.h"
#include "commons/log.h"
#include "metadata.h"
#include <stdlib.h>
#include <curses.h>
#include <commons/collections/list.h>
#include <dirent.h>
#include <errno.h>
#include <tad_items.h>
#include <nivel.h>
#include <curses.h>

t_log* logMapa;
t_metadataMapa metadataMapa;
DIR *dipPokenest;
struct dirent *ditPokenest;
DIR *dipPokemones;
struct dirent *ditPokemones;
t_list* listaDePokenest;
int semaforo_wait;
t_list* items;
t_list* listaDeEntrenadores;

// Estructuras
typedef struct {
	int socketServer;
	int socketClient;
} t_serverData;

typedef struct {
	int* pokemon;
	t_metadataPokenest metadata;
} t_pokenest;

typedef struct {
	char simbolo;
	int pos_x;
	int pos_y;
	int posD_x; //posicion deseada (a la que quiere ir)
	int posD_y;
} t_entrenador;

// Funciones de conexion
void startServerProg();
void newClients(int *socketServer, fd_set *master, int *fdmax);
void handShake(void *parameter);
void processMessageReceived (void *parameter);

// Funciones
int recorrerdirDePokenest(char* rutaDirPokenest); //Se encarga de recorrer las carpetas que esta dentro de la pokenest (pikachu,bulbasaur,charmander,etc...)
int recorrerCadaPokenest(char* rutaDeUnaPokenest); //Se encarga de recorrer lo que esta ADENTRO de las carpetas pokenest (pikachu001,pikachu002,metadata.dat,etc..)
t_metadataPokenest crearArchivoMetadataPokenest(char* rutaMetadataPokenest);
int levantarNivelDelPokemon(char* rutaDelPokemon);
void dibujarMapa();
void crearEntrenadorYDibujar(char simbolo);

#endif /* MAPA_H_ */
