/*
 * Aquatic Bubble
 * Copyright (c) 2004, 2005 Hugo Ruscitti, Gabriel Valentin
 * web site: http://www.loosersjuegos.com.ar
 * 
 * This file is part of Aquatic Bubble (aqbubble).
 *
 * Aquatic Bubble is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Aquatic Bubble is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */

#ifndef _BARRA_H
#define _BARRA_H

#include <SDL/SDL.h>
#include "cadena.h"

/*!
 * \brief Muestra vidas y puntos durante el juego
 */
class barra
{
	public:
		int iniciar(class juego *juego, class grafico *fuentes, class grafico *items);
		void actualizar(void);
		void imprimir(SDL_Surface *screen, SDL_Rect *rect, int &lim_rect);
		void set_puntos(int jugador, int puntos);
		void set_vidas(int jugador, int vidas);

		void mensaje_game_over(int jugador);
		void mensaje_continuar(int jugador);
		
	private:
		class grafico *ima_fuente;
		class grafico *ima_item;
		class juego *juego;
		
		class cadena cadena_record;
		class cadena cadena_puntos[2];
		class cadena cadena_mensaje[2];
		int vidas[2];
		int record_maximo;
};
		
#endif
