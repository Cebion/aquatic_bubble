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

#include <SDL/SDL.h>
#include "barra.h"
#include "juego.h"
#include "int_gettext.h"

/*!
 * \brief vincula la barra al juego
 */
int barra :: iniciar(class juego *juego, class grafico *fuente, class grafico *items)
{
	this->juego = juego;
	ima_fuente = fuente;
	ima_item = items;

	record_maximo = juego->mundo->marcas.get_mayor_marca();
	vidas[0] = 0;
	vidas[1] = 0;

	cadena_record.iniciar(ima_fuente, "0", ALEFT, 320, 30, 16, 28);

	cadena_puntos[0].iniciar(ima_fuente, "0", ALEFT, 60, 30, 16, 28);
	cadena_puntos[1].iniciar(ima_fuente, "0", ARIGHT, 580, 30, 16, 28);

	cadena_mensaje[0].iniciar(ima_fuente, "", ANONE, 30, 50, 16, 28, LEFT);
	cadena_mensaje[1].iniciar(ima_fuente, "", ANONE, 610, 50, 16, 28,RIGHT);
	
	cadena_puntos[0].cambiar_texto(0);
	cadena_puntos[1].cambiar_texto(0);
	cadena_record.cambiar_texto(record_maximo);

	return 0;
}


/*!
 * \brief actualizacion lógica
 */
void barra :: actualizar(void)
{
	cadena_record.actualizar();
	cadena_puntos[0].actualizar();
	cadena_puntos[1].actualizar();
}


/*!
 * \brief imprime puntos, vidas y record
 */
void barra :: imprimir(SDL_Surface *screen, SDL_Rect *rect, int &lim_rect)
{
	cadena_record.imprimir(screen, rect, lim_rect);
	cadena_puntos[0].imprimir(screen, rect, lim_rect);
	cadena_puntos[1].imprimir(screen, rect, lim_rect);

	cadena_mensaje[0].imprimir(screen, rect, lim_rect);
	cadena_mensaje[1].imprimir(screen, rect, lim_rect);

	for (int i=0; i<vidas[0]; i++)
	{
		ima_item->imprimir(0, screen, rect + lim_rect, 30+i*16, 50, 1);
		lim_rect++;
	}

	for (int i=0; i<vidas[1]; i++)
	{
		ima_item->imprimir(1, screen, rect + lim_rect, 610 - i*16, 50, 1);
		lim_rect++;
	}
}

/*!
 * \brief define el puntaje de un jugador
 */
void barra :: set_puntos(int jugador, int puntos)
{
	cadena_puntos[jugador].cambiar_texto(puntos);
	
	if (puntos > record_maximo)
	{
		record_maximo = puntos;
		cadena_record.cambiar_texto(record_maximo);
	}
}

/*!
 * \brief define la cantidad de vidas
 */
void barra :: set_vidas(int jugador, int puntos)
{
	vidas[jugador] = puntos;
	cadena_mensaje[jugador].cambiar_texto("");
}


/*!
 * \brief imprime game over
 */
void barra :: mensaje_game_over(int jugador)
{
	printf("barra, el jugador %d perdió todos sus creditos\n");
	cadena_mensaje[jugador].cambiar_texto(_("GAME OVER"));
}

/*!
 * \brief imprime 'quiere continuar'
 */
void barra :: mensaje_continuar(int jugador)
{
	printf("barra, el jugador %d perdió un credito\n");
	cadena_mensaje[jugador].cambiar_texto(_("CONTINUE?"));
}
