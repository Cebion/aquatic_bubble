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

#include "creditos.h"

/*!
 * \brief destructor
 */
creditos :: ~creditos()
{
}

/*!
 * \brief vincula la escena al juego
 */
int creditos :: iniciar(class mundo *mundo, SDL_Surface *screen, SDL_Surface *fondo)
{
	this->mundo = mundo;
	this->screen = screen;
	this->fondo = fondo;

	delay = 0;	
	lim_ant = 0;

	
	mundo->libgrafico.ima_menu.imprimir(0, fondo, NULL, 0, 0, 1);
	mundo->libgrafico.ima_logos.imprimir(0, fondo, NULL, 320, 50, 1);
	mundo->reiniciar_reloj();
	texto.crear(&mundo->libgrafico.ima_fuente_grande);
	
	return 0;
}


/*!
 * \brief actualización lógica
 */
void creditos :: actualizar(void)
{
	if (mundo->perifericos.get_tecla(ESCAPE) || \
			mundo->perifericos.get_tecla(PAUSA))
		mundo->cambiar_escena(MENU);


	if (mundo->perifericos.get_tecla(MDOWN))
	{
		texto.actualizar_invertido();
		texto.actualizar_invertido();
		delay=1;
	}

	if (mundo->perifericos.get_tecla(MUP))
	{
		texto.actualizar();
		texto.actualizar();
		delay=1;
	}

	
	if (delay == 0)
	{
		texto.actualizar();
		delay=1;
	}
	else
		delay--;
}


/*!
 * \brief actualización grafica
 */
void creditos :: imprimir(void)
{
	int i;
	
	lim_actual = 0;
	
	texto.imprimir(screen, rect_actual, lim_actual);

	lim_todos = 0;

	for (i=0; i<lim_actual; i++, lim_todos++)
		todos[lim_todos] = rect_actual[i];

	for (i=0; i<lim_ant; i++, lim_todos++)
		todos[lim_todos] = rect_ant[i];

	SDL_UpdateRects(screen, lim_todos, todos);

	for (i=0; i<lim_actual; i++)
		SDL_BlitSurface(fondo, &(rect_actual[i]), screen, &(rect_actual[i]));
	
	for (i=0; i<lim_actual; i++)
		rect_ant[i] = rect_actual[i];

	lim_ant = lim_actual;

}


/*!
 * \brief es llamada cuando se altera la resolución de video
 */
void creditos :: reiniciar_video(SDL_Surface *screen, SDL_Surface *fondo)
{
	this->screen = screen;
	this->fondo = fondo;
	lim_ant=0;

	mundo->libgrafico.ima_menu.imprimir(0, fondo, NULL, 0, 0, 1);
	mundo->libgrafico.ima_logos.imprimir(0, fondo, NULL, 320, 50, 1);
	SDL_BlitSurface(fondo, NULL, screen, NULL);
	SDL_Flip(screen);

	mundo->reiniciar_reloj();
}



/*!
 * \brief obtiene una imagen de la escena para realizar la transicion
 */
void creditos :: capturar_pantalla(SDL_Surface *pantalla)
{
	lim_actual=0;
	
	mundo->libgrafico.ima_menu.imprimir(0, pantalla, NULL, 0, 0, 1);
	mundo->libgrafico.ima_logos.imprimir(0, pantalla, NULL, 320, 50, 1);
	texto.imprimir(pantalla, rect_actual, lim_actual);

	lim_actual=0;
}
