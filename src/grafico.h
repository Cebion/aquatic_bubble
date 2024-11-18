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

#ifndef _GRAFICO_H
#define _GRAFICO_H

#include <SDL/SDL.h>
#include "enum.h"

/*!
 * \brief Maneja una plancha de graficos para imprimir
 */
class grafico
{
	public:
		int iniciar(char *ruta, int f, int c, enum ancla ancla, \
				enum resolucion res, int alpha=255);
		void imprimir(int i, SDL_Surface *destino, SDL_Rect *rect, int x, int y, int flip);
		void imprimir(int i, SDL_Surface *destino);
		void terminar(void);
		int get_w(void) {return w;};
		int get_h(void) {return h;};
	
	private:
		void definir_ancla(enum ancla ancla);
		void imprimir_rectangulo(SDL_Rect *rect, SDL_Surface *destino);
		Uint32 get_pixel(SDL_Surface *_ima, int x, int y);
		void put_pixel(SDL_Surface *_ima, int x, int y, Uint32 pixel);
		void obtener_componentes(SDL_Surface *ima, SDL_Color &color, int x, int y);
		SDL_Surface *reescalar_mitad(SDL_Surface *ima);
		void recortar_rectangulo(SDL_Rect *rect, int w, int h);

		SDL_Surface *ima;
		int fil;
		int col;
		int w;
		int h;
		int px;
		int py;
		int reducido;

		SDL_Rect captura;
		SDL_Rect src_rect;
		SDL_Rect dest_rect;
		SDL_Rect tmp;
		int i;
};

#endif
