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

#ifndef _MENU_H
#define _MENU_H

#include <SDL/SDL.h>
#include "mundo.h"
#include "escena.h"
#include "cadena.h"
#include "simple.h"

/*!
 * \brief Un estado del juego: menu
 */
class menu : public escena
{
	public:
		~menu();
		int iniciar(class mundo *mundo, SDL_Surface *screen,\
				SDL_Surface *fondo);
		void actualizar(void);
		void imprimir(void);
		void reiniciar_video(SDL_Surface *screen, SDL_Surface *fondo);
		void capturar_pantalla(SDL_Surface *pantalla);
		void iniciar_juego_desde_codigo();
		
	private:
		enum menu_estado estado;
		class cadena *opciones[10];
		class simple logo[2];
		int lim_opciones;
		int opcion;
		int ultima_tecla;
		char c_ultima_tecla[8];
		short int longitud_codigo;
		SDLKey teclas_cambiadas[4];
		
		void limpiar_pantalla(void);
		void cambiar_estado(enum menu_estado nuevo_estado);
	
		void ingresar_codigo(void);
		void mover_cursor(void);
		void selecciona(void);
		void selecciona_opcion(void);
		void selecciona_en_principal(void);
		void selecciona_en_opciones(void);
		void selecciona_en_juego(void);
		void selecciona_en_audio(void);
		void selecciona_en_video(void);
		void selecciona_en_controles(void);

		void retrocede_opcion(void);
		void avanza_opcion(void);

		void cambiar_idioma(void);
		void crear_titulo(char *titulo);
		int get_tecla(int tecla);

		void cambiar_teclas(void);
		void confirmar_cambios(void);

		void fin_ingresar_codigo(void);
		int verificar_codigo(void);
};

#endif
