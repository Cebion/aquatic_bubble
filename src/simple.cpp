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

#include "simple.h"
#include "int_gettext.h"


/*!
 * \brief genera y vincula el objeto
 */
void simple :: iniciar(class grafico *ima, int indice, enum tipo_anim animacion, int x, int y)
{
	this->ima = ima;
	this->animacion = animacion;

	this->x_destino = x;
	this->y_destino = y;

	this->indice = indice;

	switch (animacion)
	{
		case ALEFT:
			this->x = -150;
			this->y = y_destino;
			break;

		case ARIGHT:
			this->x = 640 + 150;
			this->y = y_destino;
			break;

		default:
			printf(_("invalid animation number in %s\n"), \
					"simple :: iniciar");
			break;
	}
}


/*!
 * \brief realiza la animación
 */
void simple :: actualizar(void)
{
	int incx;
	int incy;

	incx = (x_destino - x) / 8;
	incy = (y_destino - y) / 8;

	if (incx == 0 && x_destino != x)
		x_destino > x? incx=1: incx=-1;

	if (incy == 0 && y_destino != y)
		y_destino > y? incy=1: incy=-1;
		
	x += incx;
	y += incy;
}


/*!
 * \brief imprime el objeto
 */
void simple :: imprimir(SDL_Surface *screen, SDL_Rect *rect, int &lim)
{
	ima->imprimir(indice, screen, &(rect[lim]), x, y, 1);
	lim++;
}
