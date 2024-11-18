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

#ifndef _PERIFERICOS_H
#define _PERIFERICOS_H

#include <SDL/SDL.h>
#include "enum.h"

/*
 * escape
 * up
 * down
 * left
 * right
 *
 * p1left
 * p1right
 * p1up
 * p1down
 * p1fire
 *
 * pausa
 * 
 * p2left
 * p2right
 * p2up
 * p2down
 * p2fire
*/



/*!
 * \brief gestiona los controles (mouse, teclado)
 */
class perifericos
{
	public:
		void iniciar();
		bool get_tecla(int codigo_tecla);
		void reiniciar(void) {ultima_tecla=0;};
		void actualizar(void);
		void set_tecla(int codigo_tecla, SDLKey nueva); 
		SDLKey get_SDLK(char *cadena);
		bool acepta(void);
		bool rechaza(void);

	private:
		Uint8 *tecla;
		SDLKey vec_teclas[16];
		Uint8 ultima_tecla;
};

#endif
