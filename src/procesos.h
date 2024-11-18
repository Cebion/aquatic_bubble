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

#ifndef _PROCESOS_H
#define _PROCESOS_H

#include "protagonistas.h"
#include "enemigos.h"
#include "items.h"
#include "silvio.h"
#include "paco.h"
#include "burbuja.h"
#include "pez.h"
#include <list>
#include <algorithm>

using namespace std;

typedef struct n_protagonistas
{
	class protagonistas * obj;
	int jugador;
}n_protagonistas;

typedef struct n_enemigos
{
	class enemigos * obj;
	int jugador;
}n_enemigos;

typedef struct n_items
{
	class items * obj;
	int jugador;
}n_items;

/*!
 * \brief mantiene una lista de actores
 */
class procesos
{
	public:
		procesos();
		~procesos();

		void iniciar(class juego *juego);
		void crear_silvio(class grafico *grafico, int x, int y);
		void crear_paco(class grafico *grafico, int x, int y);
		void crear_burbuja(int x, int y ,int flip,int jugador);
		void crear_enemigo(class grafico *grafico, int x, int y);
		void actualizar();
		void imprimir(SDL_Surface *screen, SDL_Rect *modificados, int &lim_modificados);
		void avisar_colisiones(void);	
		int hay_enemigo_cerca(int avanze,int jugador);
		void suma_puntos(int puntos,int jugador);
		int get_puntos(int jugador);
		int get_cant_protagonistas(void);

	private:
		class juego *juego;
		int puntos[2];
		
		list <n_protagonistas> lista_protagonistas;	
		list <n_items> lista_burbuja;
		list <n_enemigos> lista_enemigos;
		
		template <class S> void actualizar_listas(list<S> &list_ref);
		template <class S> void imprimir_listas(SDL_Surface *screen, SDL_Rect *modificados,int &lim,list<S> &list_ref);
		float distancia(int x1,int y1,int x2,int y2);
		list<n_protagonistas>::iterator busca_protagonista(int jugador);
		void colision_enemigo_enemigo(void);
		void colision_enemigo_burbuja(void);
		void colision_enemigo_personaje(void);
		void reiniciar_protagonistas(list<n_protagonistas> lista);
		void actualizar_puntos_protagonista(list<n_protagonistas>lista);	  
		
		
};

#endif
