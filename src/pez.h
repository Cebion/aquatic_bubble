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

#ifndef _PEZ_H
#define _PEZ_H

//#include "grafico.h"
#include "enemigos.h"

/*!
 * \brief Enemigo pez
 */
class pez : public enemigos
{
	public:
		int iniciar(class juego *juego, grafico *_grafico, int x, int y);
		int actualizar(void);
		int terminar(void);
		
	private:
		
		void normal(void);
		void caminar(void);
		void correr(void);
		void saltar(void);
		void encerrado(void);
		void colision(void);
		void buscar_piso(void);
		int morir(void);
		
};

#endif
