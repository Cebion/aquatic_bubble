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

#ifndef _ESCENA_H
#define _ESCENA_H

#include <SDL/SDL.h>
#include "cadena.h"
#include "grafico.h"
#include "enum.h"

/*!
 * \brief Base para cada estado
 */
class escena
{
	public:
		virtual ~escena() {;};
		virtual int iniciar(class mundo *mundo,SDL_Surface *screen,SDL_Surface *fondo) = 0 ;
		virtual void actualizar(void) = 0;
		virtual void imprimir(void) = 0;
		virtual void reiniciar_video(SDL_Surface *screen, SDL_Surface *fondo) = 0;
		virtual void capturar_pantalla(SDL_Surface *pantalla) = 0;
		class mundo *mundo;
		
	protected:
		SDL_Surface *screen;
		SDL_Surface *fondo;

		SDL_Rect rect_actual[1024];
		int lim_actual;
		SDL_Rect rect_ant[1024];
		int lim_ant;
		SDL_Rect todos[1024];
		int lim_todos;
		
		void crear_texto(class grafico *ima, class cadena *textos[], \
				int &lim, char *nombre, int max_textos,\
				enum tipo_anim anim);
};

#endif
