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

#include "actor.h"
#include "juego.h"

actor :: ~actor(void)
{
}

/*!
 *\brief carga las animaciones de personajes, items, etc.
 */
void actor :: cargar_animacion(int *vec, char *cuadros)
{
	char *p=NULL;
	char buffer[100];
	int i=0;
	strcpy(buffer, cuadros);
	
	p=strtok(buffer, ",");

	while (p)
	{
		vec[i] = atoi(p);
		p=strtok(NULL, ",");
		i++;
	}

	vec[i] = -1;
}

/*!
 * \brief gestiona la animaciona de personajes, items, etc
 *
 * \return 1 si termina la animación 
 */
int actor :: avanzar_animacion(void)
{
	if (cont_delay>6)
	{
		if (animaciones[estado][paso+1] == -1)
		{
			paso=0;
			cont_delay=0;
			return 1;
		}
		else
			paso++;
		
		cont_delay=0;
	}
	else
		cont_delay++;
	
	return 0;
}

/*!
 *\brief reinicia la animacion despues de un cambio de estado.
 */
void actor :: reiniciar_animacion(void)
{
	paso=0;
	cont_delay=0;
}

/*!
 *\brief verifica si se encuentra encuentra suelo.
 *\return 0 si no encontro, 1 si encontro.
 */
int actor :: pisa_suelo(void)
{
	if(juego->nivel.get_dist_suelo(x,y,8) > 7)
		return 0;
	else
		return 1;
}

/*!
 * \brief logra que el actor no avanze.
 */
void actor:: no_avanzar(void)
{
		  
	if(flip==1)
		x-=2;
	else
		x+=2;
}

/*!
 * \brief logra que el actor avanze.
 */
void actor :: avanzar(void)
{

	if(flip==1)
		x+=2;
	else
		x-=2;	
}

