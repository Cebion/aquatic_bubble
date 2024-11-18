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

#ifndef _NIVEL_H
#define _NIVEL_H

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "grafico.h"
#include "procesos.h"

class nivel
{
	public:
		nivel();
		int iniciar(class grafico *ima);
		void imprimir(SDL_Surface *destino);
		int get_dist_suelo(int x, int y, int rango);		
		int get_dist_pared(int x,int y,int rango);
		int avanzar_nivel(class procesos *procesos);
		int get_nivel_actual(void) {return nivel_actual;};
		void saltar_nivel(int numero);

	private:
		class grafico *ima;
		int tiles[30][40];
		int nivel_actual;

		int cargar_nivel(int numero);
		int get_colision(int x, int y); 
};

#endif
