/*
 * osada.c
 *
 *  Created on: 9/9/2016
 *      Author: utnso
 */

#include "osada.h"
#include <stdlib.h>
#include <stdio.h>

void inicializarOSADA(){

}


osada_header *leerArchivoParaHeader(char *ruta){
	osada_header *osadaHeaderFile = malloc(sizeof(osada_header));
	FILE * archivo= fopen(ruta, "rb");

	if (archivo != NULL) {
		fread(osadaHeaderFile, sizeof(osada_header), 1, archivo);
		fclose(archivo);
	}
	return osadaHeaderFile;
}



unsigned char devolverMagicNumbre(osada_header *osadaHeader){
	return osadaHeader->magic_number[7];
}

uint8_t devolverVersion(osada_header *osadaHeader){
	return osadaHeader->version;
}

int devolverFSBloques(osada_header *osadaHeader){
	return osadaHeader->fs_blocks;
}

uint32_t devolverBitMapBlocks(osada_header *osadaHeader){
	return osadaHeader->bitmap_blocks; // bitmap size in blocks
}

uint32_t devolverAllocations_table_offset(osada_header *osadaHeader){
	return  osadaHeader->allocations_table_offset; // allocations table's first block number

}

uint32_t devolverDataBlocks(osada_header *osadaHeader){
	return osadaHeader->data_blocks; // amount of data blocks
}


unsigned char devolverPadding(osada_header *osadaHeader){
	return	osadaHeader->padding[40]; // useless bytes just to complete the block size
}



/*FILE SYSTEM */
osada_file *leerArchivoParaOsadaFile(char *ruta){
	osada_file *osadaFile = malloc(sizeof(osada_file));
	FILE * archivo= fopen(ruta, "rb");

	if (archivo != NULL) {
		fread(osadaFile, sizeof(osada_file), 1, archivo);
		fclose(archivo);
	}
	return osadaFile;
}

int devolverTamanio(osada_file *osadaFile){
	return osadaFile->file_size;
}

osada_file_state devolverEstado(osada_file *osadaFile){
	return osadaFile->state;
}

unsigned char devolverNombreDelArchivo(osada_file *osadaFile){
	return osadaFile->fname[OSADA_FILENAME_LENGTH];
}

uint16_t devolverDirectorioPadre(osada_file *osadaFile){
	return osadaFile->parent_directory;
}

uint32_t devolverUltimaMod(osada_file *osadaFile){
	return osadaFile->lastmod;
}

osada_block_pointer devolverPrimerBloque(osada_file *osadaFile){
	return osadaFile->first_block;
}