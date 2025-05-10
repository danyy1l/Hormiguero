/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Danyyil Shykerynets
 * @version 22
 * @date 24-04-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief Estructura para implementar al TAD Graphic_engine. 
 * Definida en graphic_engine.c
 **/
 /*START [Graphic_engine]*/
typedef struct _Graphic_engine Graphic_engine;
/*END [Graphic_engine]*/

/**
 * @brief Crea el motor gráfico reservando su memoria
 * @author Danyyil Shykerynets
 * @return Devuelve un nuevo motor gráfico creado
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Crea el motor gráfico de inicio
 * @author Danyyil Shykerynets
 * @return Devuelve un nuevo motor gráfico creado
 */
Graphic_engine *graphic_engine_start();

/**
 * @brief Destruye el motor gráfico liberando su memoria 
 * @author Danyyil Shykerynets
 * @param ge Un puntero a Graphic_engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Dibuja el motor gráfico
 * @author Danyyil Shykerynets
 * @param ge Un puntero a Graphic_engine 
 * @param game Un puntero a Game
 * @param command Puntero al ultimo comando
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Command* command);

/**
 * @brief Dibuja un game over
 * @author Danyyil Shykerynets
 * @param ge Un puntero a Graphic_engine 
 * @param game Un puntero a Game
 */
void graphic_engine_paint_game_over(Graphic_engine* ge, Game *game);

/**
 * @brief Dibuja la pantalla inicial
 * @author Danyyil Shykerynets
 * @param ge Un puntero a Graphic_engine 
 * @param game Un puntero a Game
 */
void graphic_engine_paint_start(Graphic_engine* ge, Game* game);

/**
 * @brief Destruye el motor gráfico de inicio
 * @author Danyyil Shykerynets
 * @param ge Un puntero a Graphic_engine
 */
void graphic_engine_destroy_start(Graphic_engine *ge);

#endif
