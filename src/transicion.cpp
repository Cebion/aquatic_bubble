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

#include "transicion.h"
#include "int_gettext.h"

transicion :: transicion()
{
	screen=NULL;
	ima1=NULL;
	ima2=NULL;
}

transicion :: ~transicion()
{
	if (ima1)
		SDL_FreeSurface(ima1);

	if (ima2)
		SDL_FreeSurface(ima2);
}

/*!
 * \brief genera las superficies a mezclar
 *
 * \return 1 en caso de error, 0 en otro caso
 */
int transicion :: crear_superficies(SDL_Surface *screen)
{
	this->screen = screen;
	
	if (ima1)
		SDL_FreeSurface(ima1);

	if (ima2)
		SDL_FreeSurface(ima2);

	ima1 = SDL_DisplayFormat(screen);
	ima2 = SDL_DisplayFormat(screen);

	if (ima1 && ima2)
	{
		return 0;
	}
	else
	{
		printf(_("Can't create images for transition\n"));
		return 1;
	}
}


/*!
 * \brief genera o reutiliza los valores iniciales para generar una transicion
 */
int transicion :: reiniciar(enum tipo_transicion tt)
{
	this->tt = tt;
	imprimio_ultimo = false;
	trans=0;
	return 0;
}


/*!
 * \brief determina la imagen a mezclar
 */
void transicion :: define_actual(SDL_Surface *ima1)
{
#ifndef NOTRANS
	SDL_BlitSurface(ima1, NULL, this->ima1, NULL);
#else
	SDL_BlitSurface(ima1, NULL, this->ima1, NULL);
#endif
}

/*!
 * \brief determina la imagen a mezclar
 */
void transicion :: define_anterior(SDL_Surface *ima2)
{
#ifndef NOTRANS
	SDL_BlitSurface(ima2, NULL, this->ima2, NULL);
#endif
}

/*!
 * \brief actualización lógica
 */
void transicion :: actualizar(void)
{
#ifdef NOTRANS
	return;
#endif
	if (trans < screen->h)
	{
		if (screen->h == 480)
			trans+= (screen->h-trans) / 15 +2;
		else
			trans+= (screen->h-trans) / 15 +2;
	}
}


/*!
 * \brief informa si la animacion de transicion terminó
 */
int transicion :: termino(void)
{
	if (imprimio_ultimo)
		return 1;
	else
		return 0;
}


/*!
 * \brief imprime las imagenes mientras se mezclan
 */
void transicion :: imprimir(void)
{
#ifdef NOTRANS
	imprimio_ultimo = true;
	SDL_BlitSurface(ima1, NULL, screen, NULL);
	SDL_Flip(screen);
	return;
#endif
	SDL_Rect rect  = {0, 0, screen->w, screen->h};
	SDL_Rect rect2 = {0, 0, screen->w, screen->h};

	switch (tt)
	{
		case DESDEARRIBA:
			rect.y = trans - screen->h;
			rect2.y = trans;
			
			if (trans >= screen->h)
			{
				SDL_BlitSurface(ima1, NULL, screen, NULL);
				imprimio_ultimo = true;
			}
			else
			{
				SDL_BlitSurface(ima1, NULL, screen, &rect);
				SDL_BlitSurface(ima2, NULL, screen, &rect2);
			}
			break;

		case DESDEABAJO:
			rect.y = screen->h -trans;
			rect2.y = -trans;
			
			if (trans >= screen->h)
			{
				SDL_BlitSurface(ima1, NULL, screen, NULL);
				imprimio_ultimo = true;
			}
			else
			{
				SDL_BlitSurface(ima1, NULL, screen, &rect);
				SDL_BlitSurface(ima2, NULL, screen, &rect2);
			}

			break;

		default:
			printf("tmp: transicion::imprimir, No implementado\n");
			break;
	}

	SDL_Flip(screen);
}
