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

#ifndef _SIMPLE_H
#define _SIMPLE_H

#include <SDL/SDL.h>
#include "grafico.h"

/*!
 * \brief Sprite simple con movimiento
 */
class simple
{
	public:
		void iniciar(class grafico *ima, int indice, \
				enum tipo_anim anim, int x=320, int y=240);
		void actualizar(void);
		void imprimir(SDL_Surface *screen, SDL_Rect *rect, int &lim);

	private:
		class grafico *ima;
		enum tipo_anim animacion;
		
		int x;
		int y;
		int x_destino;
		int y_destino;
		int indice;
};
#endif
