/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Anthony Eduardo Alvarado Carbajal
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "../scripts/game.h"
/**
 * @brief Estructura para implementar al TAD Graphic_engine. 
 * Definida en graphic_engine.c
 **/
 /*START [Graphic_engine]*/
typedef struct _Graphic_engine Graphic_engine;
/*END [Graphic_engine]*/

/**
 * @brief Crea el motor gráfico reservando su memoria
 * @author Anthony Eduardo Alvarado Carbajal
 * @return Devuelve un nuevo motor gráfico creado
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Destruye el motor gráfico liberando su memoria 
 * @author Anthony Eduardo Alvarado Carbajal
 * @param ge Un puntero a Graphic_engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Dibuja el motor gráfico
 * @author Anthony Eduardo Alvarado Carbajal
 * @param ge Un puntero a Graphic_engine 
 * @param game Un puntero a Game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
