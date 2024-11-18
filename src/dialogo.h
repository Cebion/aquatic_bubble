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

#ifndef _DIALOGO_H
#define _DIALOGO_H

#include <SDL/SDL.h>

/*!
 * \brief mensaje de espera que muestra como se cargan los recursos
 */
class dialogo
{
	public:
		void iniciar(SDL_Surface *screen);
		void reiniciar(SDL_Surface *screen);
		void reiniciar_barra(int limite);
		void imprimir_titulo(SDL_Surface *screen, char *titulo);
		void imprimir_barra(SDL_Surface *screem, int suma_progreso);
		void imprimir_error(SDL_Surface *screen, char *cadena);
		
	private:
		int progreso;
		int maxprogreso;
		
		void put_pixel(SDL_Surface *_ima, int x, int y, Uint32 pixel);
		void imprimir_texto(SDL_Surface *screen, char *cadena, int x, int y);
};

#endif
