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

#ifndef _MUNDO_H
#define _MUNDO_H

#include <SDL/SDL.h>
#include "escena.h"
#include "libgrafico.h"
#include "dialogo.h"
#include "enum.h"
#include "transicion.h"
#include "audio.h"
#include "perifericos.h"
#include "marcas.h"

/*!
 * \brief Mantiene todos los objetos del juego e inicia el juego
 */
class mundo
{
	public:
		mundo();
		int iniciar(bool fs, bool musica, bool sonido,\
				enum resolucion res, int test);
		void correr(void);
		void terminar(void);
		void cambiar_escena(enum nro_escena nueva_escena);
		void set_juego(int players, int nivel, int cheat);
		void pantalla_completa(void);
		void cambiar_modo_video(void);
		void reiniciar_reloj(void);
		void terminar_todo(void);
		bool get_fullscreen(void) {return fullscreen;};
		enum resolucion get_res(void) {return res;};
		int get_juego_players(void) {return juego_players;};
		int get_juego_cheat(void) {return juego_cheat;};
		int get_juego_nivel(void) {return juego_nivel;};
		
		class libgrafico libgrafico;
		class dialogo dialogo;
		class audio audio;
		class perifericos perifericos;
		class marcas marcas;

	private:
		int iniciar_pantalla();
		int procesar_eventos(SDL_Event *evento);
		void definir_ventana(void);
		void aplicar_cambio_escena(void);
		void imprimir_transicion(void);
		
		class transicion transicion;
		SDL_Surface *screen;
		SDL_Surface *fondo;
		class escena *actual;
		int escena_actual;
		int escena_anterior;
		bool fullscreen;
		bool sonido;
		bool musica;
		enum resolucion res;
		int t;
		int tl;
		int tg;
		bool debe_terminar;

		int juego_nivel;
		int juego_cheat;
		int juego_players;
};

#endif
