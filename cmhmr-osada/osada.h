#include <stdint.h>

#define OSADA_BLOCK_SIZE 64
#define OSADA_FILENAME_LENGTH 17

typedef unsigned char osada_block[OSADA_BLOCK_SIZE];
typedef uint32_t osada_block_pointer;

// set __attribute__((packed)) for this whole section
// See http://stackoverflow.com/a/11772340/641451
#pragma pack(push, 1)

typedef struct {
	unsigned char magic_number[7]; // OSADAFS
	uint8_t version;
	uint32_t fs_blocks; // total amount of blocks
	uint32_t bitmap_blocks; // bitmap size in blocks
	uint32_t allocations_table_offset; // allocations table's first block number
	uint32_t data_blocks; // amount of data blocks
	unsigned char padding[40]; // useless bytes just to complete the block size
} osada_header;

_Static_assert( sizeof(osada_header) == sizeof(osada_block), "osada_header size does not match osada_block size");

typedef enum __attribute__((packed)) {
    DELETED = '\0',
    REGULAR = '\1',
    DIRECTORY = '\2',
} osada_file_state;

_Static_assert( sizeof(osada_file_state) == 1, "osada_file_state is not a char type");

typedef struct {
	osada_file_state state;
	unsigned char fname[OSADA_FILENAME_LENGTH];
	uint16_t parent_directory;
	uint32_t file_size;
	uint32_t lastmod;
	osada_block_pointer first_block;
} osada_file;

_Static_assert( sizeof(osada_file) == (sizeof(osada_block) / 2.0), "osada_file size does not half osada_block size");

#pragma pack(pop)

void inicializarOSADA();

osada_header *leerArchivoParaHeader(char *ruta);

unsigned char devolverMagicNumbre(osada_header *osadaHeader);

uint8_t devolverVersion(osada_header *osadaHeader);

int devolverFSBloques(osada_header *osadaHeader);

uint32_t devolverBitMapBlocks(osada_header *osadaHeader);

uint32_t devolverAllocations_table_offset(osada_header *osadaHeader);

uint32_t devolverDataBlocks(osada_header *osadaHeader);


unsigned char devolverPadding(osada_header *osadaHeader);



/*FILE SYSTEM */
osada_file *leerArchivoParaOsadaFile(char *ruta);

int devolverTamanio(osada_file *osadaFile);

osada_file_state devolverEstado(osada_file *osadaFile);

unsigned char devolverNombreDelArchivo(osada_file *osadaFile);

uint16_t devolverDirectorioPadre(osada_file *osadaFile);

uint32_t devolverUltimaMod(osada_file *osadaFile);

osada_block_pointer devolverPrimerBloque(osada_file *osadaFile);
