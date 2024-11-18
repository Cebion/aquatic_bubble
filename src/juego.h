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

#ifndef _JUEGO_H
#define _JUEGO_H

#include <SDL/SDL.h>
#include "barra.h"
#include "mundo.h"
#include "escena.h"
#include "procesos.h"
#include "nivel.h"
#include "cadena.h"
#include "transicion.h"
#include "enum.h"

/*!
 * \brief Un estado del juego: juego
 */
class juego : public escena
{
	public:
		~juego() {;};
		int iniciar(class mundo *mundo, SDL_Surface *screen,SDL_Surface *fondo);
		void actualizar(void);
		void imprimir(void);
		void reiniciar_video(SDL_Surface *screen, SDL_Surface *fondo);
		void capturar_pantalla(SDL_Surface *pantalla);
		void pasar_nivel(void);
		void game_over(void);
		void mensaje(int jugador, enum mensajes mensaje);
		void nivel_completado(void);
		
		class procesos procesos;
		class nivel nivel;
		class barra barra;

	private:
		class cadena cadena;
		class transicion transicion;
		enum juego_estado estado;
		int delay;
		
		void cambiar_estado(enum juego_estado nuevo);
		void imprimir_numero_nivel(void);
};
		
#endif
