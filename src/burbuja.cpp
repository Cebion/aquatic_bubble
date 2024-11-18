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

#include "burbuja.h"

/*!
 *\brief inicializa la burbuja.
 */
void burbuja :: iniciar(class juego *juego,class grafico *grafico,int x,int y, int flip)
{
	ima=grafico;
	this->juego=juego;
	this->x=x;
	this->y=y;
	this->flip=flip;
	paso=0;
	estado=0;
	cont_delay=0;

	cargar_animacion(animaciones[0],"0,2,4,6,8,10,12,13");
	
}

/*!
 *\brief actualiza el estado de la burbuja.
 */ 
int burbuja :: actualizar(void)
{
		  
	if(flip==1)
		x+= 2;
	else
		x-= 2;
	
	if(avanzar_animacion())
			  return 1;
return 0;
}

/*!
 *\brief  
 */ 
int burbuja :: terminar(void)
{
	return 0;
}
