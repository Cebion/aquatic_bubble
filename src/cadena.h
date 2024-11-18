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

#ifndef _CADENA_H
#define _CADENA_H

#include <SDL/SDL.h>
#include "grafico.h"
#include "enum.h"

/// una letra de la cadena
struct letra
{
	/// nro de grafico
	int grafico;
	/// x actual
	int x;
	/// y actual
	int y;
	/// x que debe alcanzar
	int xdest;
	/// y que debe alcanzar 
	int ydest;
};


/*!
 * \brief Texto con animación
 */
class cadena
{
	public:
		cadena();
		~cadena();
		void iniciar(class grafico *ima, char *cadena, enum tipo_anim anim, int x=320, int y=240, int w=30, int h=30, enum ancla ancla=CENTER);
		void reiniciar(char *cadena);
		void reiniciar(char *cadena, enum tipo_anim anim);
		void actualizar(void);
		void actualizar_invertido(void);
		void cambiar_texto(char *cadena);
		void cambiar_texto(int numero);
		void cambiar_guiones(char *cadena);
		void agregar_letra(char tecla);
		void imprimir(SDL_Surface *screen, SDL_Rect *rect, int &lim);
		void activar(void);
		void desactivar(void);
		void tildar(void);
		void destildar(void);
		bool get_visible(void) {return visible;};
		bool get_detenido(void) {return detenido;};
		void get_texto(char *cadena);

	private:
		class grafico *ima;
		struct letra *letras;
		int animacion;
		int activado;
		int cant_letras;
		int x;
		int y;
		int w;
		int h;
		int paso;
		bool visible;
		bool detenido;
		enum ancla ancla;
		
		void crear_texto(char *cadena);
		void asignar_grafico(int &grafico, const char letra);
		int get_cant_letras(const char *cadena);

};
#endif
