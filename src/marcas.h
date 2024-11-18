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

#ifndef _MARCAS_H
#define _MARCAS_H

#include <SDL/SDL.h>
#include "enum.h"


struct record
{
	char nombre[20];
	int puntos;
};

/*!
 * \brief Gestiona las mejores puntuaciones
 */
class marcas
{
	public:
		void iniciar(void);
		void guardar_cambios(void);
		void imprimir(void);
		void get_marca(char *cadena, int pos);
		int get_mayor_marca(void) { return todos[0].puntos;};
		
	private:
		int cargar_archivo(void);
		void cargar_por_defecto(void);
		void get_nombre(char *nombre, int pos);
		void get_puntos(char *puntos, int pos);

		struct record todos[5];
};

#endif
