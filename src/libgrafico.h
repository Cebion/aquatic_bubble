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

#ifndef _LIBGRAFICO_H
#define _LIBGRAFICO_H

#include "grafico.h"
#include "enum.h"
#include "dialogo.h"

/*!
 * \brief gestiona un conjunto de graficos
 */
class libgrafico
{
	public:
		int iniciar(class dialogo *dialogo, SDL_Surface *screen, enum resolucion res);
		void terminar(void);
		int cambiar_modo_video(void);
		int termino(void);

		class grafico ima_silvio;
		class grafico ima_paco;
		class grafico ima_nivel;
		class grafico ima_burbuja;
		class grafico ima_fuente_grande;
		class grafico ima_fuente_chica;
		class grafico ima_pez;
		class grafico ima_menu;
		class grafico ima_items;
		class grafico ima_logos;
		class grafico ima_particulas;
	
	private:
		int cargar_graficos(enum resolucion res);

		enum resolucion res_actual;
		class dialogo *dialogo;
		SDL_Surface *screen;
		bool cargando;
};


#endif
