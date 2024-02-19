#ifndef MAIN_H
#define MAIN_H

#include <time.h>

/**
 * Énumération des cardinaux (`Nord`, `Sud`, `Est` et `Ouest`).
*/
typedef enum	e_dir
{
				nord,
				sud,
				est,
				ouest,
} 				t_dir;

/**
 * Structure qui se réfère à la position du robot sur la carte.
 * Valeurs :
 * - `(clock_t) starter`: .
 * - `(int) i`: Position en abcisse.
 * - `(int) j`: Position en ordonnée.
 * - `(int) border`: .
 * - `(t_dir) next_move`: Direction du prochain déplacement.
*/
typedef struct	posmap
{
				clock_t	starter;
				int		i;
				int		j;
				int		border;
				t_dir	next_move;
}				posmap;

#endif