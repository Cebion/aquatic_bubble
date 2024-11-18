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

#ifndef _ACTOR_H
#define _ACTOR_H

#include "grafico.h"
//#include "juego.h"

/*!
 * \brief Es la base para todos los personajes y objetos
 */
class actor
{
	public:
		virtual ~actor(void);
		virtual int actualizar(void) = 0;
		virtual int terminar(void) = 0;
		virtual void imprimir(SDL_Surface *screen, SDL_Rect *rect) = 0;
		SDL_Rect rect;
		
		int get_estado(void){return estado;}
		int get_flip(void){return flip;}
		int get_x(void){return x;}
		int get_y(void){return y;}
		int get_w(void){return w;}
		int get_h(void){return h;}
		void set_flip(int f){flip=f;}	
		void cambiar_flip(void){flip=(flip*-1);}
		void avanzar(void);
		void no_avanzar(void);
		void set_estado(int e){estado=e;}
		
	protected:
		class grafico *ima;
		class juego *juego;
		int animaciones[15][20];
		int paso;
		int cont_delay;
		int velocidad;
		int x,y,w,h;
		int flip;
		int estado;
		
		void cargar_animacion(int *vec_anim, char *cuadros);
		int avanzar_animacion(void);
		void reiniciar_animacion(void);
		int pisa_suelo(void);
		
};

#endif
