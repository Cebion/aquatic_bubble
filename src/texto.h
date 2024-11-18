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

#ifndef _TEXTO_H
#define _TEXTO_H

#include "cadena.h"
#include "grafico.h"

/*!
 * \brief texto de varios parrafos utilizado en la escena creditos
 */
class texto
{
	public:
		texto();
		~texto();
		void crear (class grafico *letras);
		void actualizar (void);
		void actualizar_invertido (void);
		void imprimir (SDL_Surface *dst, SDL_Rect *rect, int &lim);
		
	private:
		class grafico *ima;
		class cadena *cadena[100];
		int lim_cadena;

		void mensaje (char *mensaje);
};

#endif
