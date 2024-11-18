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

#ifndef _PROTAGONISTAS_H
#define _PROTAGONISTAS_H

//#include "grafico.h"
#include "actor.h"

/*!
 * \brief Protagonista silvio
 */
class protagonistas : public actor
{
	public:
		virtual int actualizar(void)=0;
		virtual int iniciar(class juego *juego, grafico *_grafico, int x, int y)=0;
		void imprimir(SDL_Surface *screen, SDL_Rect *rect);
		int get_visibilidad(void){return hab_intermitente;}
		int get_puntos(void){return puntos;}
		void colision_con_enemigo(void);
		void set_velocidad(void){velocidad=-20;}
		void sumar_puntos(int suma){puntos+=suma;}
		void set_x_inicial(void){x=x_inicial;}
		void set_y_inicial(void){y=y_inicial;}
		
	protected:
		int puede_disparar;
		int x_inicial,y_inicial;
		int hab_intermitente,intermitente;
		int puntos,jugador;
		int vidas,continuar,esperando;
		
		int terminar(void);
		bool es_par(void);
		bool enemigo_cerca(int avanze,int jugador);
		bool pide_tecla(int codigo);
		void actualizar_tecla();
};
#endif
