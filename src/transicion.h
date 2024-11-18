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

#ifndef _TRANSICION_H
#define _TRANSICION_H

#include <SDL/SDL.h>
#include "enum.h"


/*!
 * \brief Mezcla 2 imagenes
 */
class transicion
{
	public:
		transicion();
		~transicion();
		int crear_superficies(SDL_Surface *screen);
		int reiniciar(enum tipo_transicion tt);
		void define_actual(SDL_Surface *ima1);
		void define_anterior(SDL_Surface *ima2);
		void actualizar(void);
		int termino(void);
		void imprimir(void);
		
	private:
		SDL_Surface *screen;
		SDL_Surface *ima1;
		SDL_Surface *ima2;
		int trans;
		enum tipo_transicion tt;
		bool imprimio_ultimo;
};

#endif
