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

#include "dialogo.h"
#include "int_gettext.h"

/*!
 * \brief genera los componentes del dialogo
 */
void dialogo :: iniciar(SDL_Surface *screen)
{
	reiniciar(screen);
}

/*!
 * \brief limpia la pantalla
 */
void dialogo :: reiniciar(SDL_Surface *screen)
{
	progreso=0;
	maxprogreso=10;
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,187,168,149));
	SDL_Flip(screen);
}

/*!
 * \brief muestra el dialogo
 */
void dialogo :: imprimir_titulo(SDL_Surface *screen, char *titulo)
{
	imprimir_texto(screen, titulo, 190, 70);
}

/*!
 * \brief imprime la barra de progreso
 */
void dialogo :: imprimir_barra(SDL_Surface *screen, int suma_progreso)
{
	SDL_Rect rect = {50, 100, 540, 20};
	SDL_Rect rect2 = {50, 100, 540, 20};
	SDL_Rect rectmayor;
	
	progreso+=suma_progreso;

	rect.w = (540*progreso)/maxprogreso;

	if (screen->w == 320)
	{
		rect.x /= 2;
		rect.y /= 2;
		rect.w /= 2;
		rect.h /= 2;

		rect2.x /= 2;
		rect2.y /= 2;
		rect2.w /= 2;
		rect2.h /= 2;
	}

	rectmayor.x = rect.x -1;
	rectmayor.y = rect.y -1;
	rectmayor.w = rect2.w +2;
	rectmayor.h = rect.h +2;

	rect.x++;
	rect.y++;
	rect.w-=2;
	rect.h-=2;
	
	SDL_FillRect(screen, &rectmayor, SDL_MapRGB(screen->format, 110, 110, 110));
	SDL_FillRect(screen, &rect2, SDL_MapRGB(screen->format, 180, 180, 180));
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 45, 132, 48));

	SDL_UpdateRect(screen, rectmayor.x, rectmayor.y, rectmayor.w, rectmayor.h);
}


/*!
 * \brief imprime un punto de color (tomada de doc/SDL)
 */
void dialogo :: put_pixel(SDL_Surface *_ima, int x, int y, Uint32 pixel)
{
	int bpp = _ima->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)_ima->pixels + y * _ima->pitch + x*bpp;

	switch (bpp)
	{
		case 1:
			*p = pixel;
			break;
			
		case 2:
			*(Uint16 *)p = pixel;
			break;
			
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0]=(pixel >> 16) & 0xff;
				p[1]=(pixel >> 8) & 0xff;
				p[2]=pixel & 0xff;
			}
			else
			{
				p[0]=pixel & 0xff;
				p[1]=(pixel >> 8) & 0xff;
				p[2]=(pixel >> 16) & 0xff;
			}
			break;
			
		case 4:
			*(Uint32 *) p = pixel;
			break;
	}
}

/*!
 * \brief define el maximo de la barra
 */
void dialogo :: reiniciar_barra(int limite)
{
	maxprogreso = limite;
}



/*!
 * \brief informa que el error termina el programa
 */
void dialogo :: imprimir_error(SDL_Surface *screen, char *cadena)
{
	SDL_Event event;
	
	imprimir_texto(screen, _("Can't open file:"), 50, 200);
	imprimir_texto(screen, cadena, 50, 240);
	imprimir_texto(screen, _("Press any key to quit"), 50, 400);

	
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					return;
					break;

				case SDL_QUIT:
					return;
					break;
			}
		}
	}
}



/*!
 * \brief imprime un texto sin utilizar fuentes graficas
 */
void dialogo :: imprimir_texto(SDL_Surface *screen, char *cadena, int _x, int _y)
{
	char letras[6][300]={\
	    {"AAAA BBBB CCCC DDDD EEEE FFFF GGGG HHHH I JJJJ KKKK LLLL MMMMM NNNNN OOOO PPPP QQQQQ RRRR SSSSS TTT UUUU VVVVV WWWWW XXXX YYYYY ZZZZ . : aaaa bbbb ccc dddd eeeee fff gggg hhhh i jjjj kkkk ll mmmmmmm nnnn oooo pppp qqqqq rrrr ssss ttt uuuu vvvv wwwww xxx yyyy zzzz //// '"},\
    	    {" oo  ooo   ooo ooo  oooo oooo  ooo o  o o  ooo o  o o    o   o o   o oooo ooo   ooo  ooo   ooo  ooo o  o o   o o   o o  o o   o oooo      oo  o           o  ooo   oo  ooo o    o    o o    o                          ooo        oo   o                      o  o           o"},\
	    {"o  o o  o o    o  o o    o    o    o  o o    o o o  o    oo oo oo  o o  o o  o o   o o  o o      o  o  o o   o o   o o  o o   o    o   o    o o     oo  ooo o   o o   o  o o           o  o o  ooo oo  ooo   oo  ooo  o  o  o oo o    ooo o  o o  o o   o     o  o oooo    o o"},\
	    {"oooo ooo  o    o  o oo   ooo  o oo oooo o    o oo   o    o o o o o o o  o ooo  o o o oooo  ooo   o  o  o o   o o   o  oo   o o    o       ooo ooo  o   o  o ooooo oo   ooo ooo  o    o ooo  o  o  o  o o  o o  o o  o  ooo  oo    oo   o  o  o o  o o o o o o  ooo   o    o   "},\
	    {"o  o o  o o    o  o o    o    o  o o  o o o  o o o  o    o   o o  oo o  o o     ooo  o  o     o  o  o  o  o o  o o o o  o   o    o     o o  o o  o o   o  o o     o      o o  o o o  o o  o o  o  o  o o  o o  o ooo     o  o       o  o  o  o o  o o o o  o     o  o    o    "},\
	    {"o  o ooo   ooo ooo  oooo o     ooo o  o o  oo  o  o oooo o   o o   o oooo o       o  o  o oooo   o  oooo   o    o o  o  o  o    oooo o    ooo ooo   oo  ooo  ooo  o    oo  o  o o  ooo o  o  o o  o  o o  o  oo  o     oooo o    ooo    o oooo  oo   o o  o o  ooo oooo o     "}};
	int i;
	int cmatriz;
	int x = _x;
	int y = _y;

	if (screen->w == 320)
	{
		x/=2;
		y/=2;
	
		for (i=0; cadena[i] != '\0'; i++)
		{
			for (cmatriz=0; letras[0][cmatriz] != cadena[i]; cmatriz++)
				;

			for (; letras[0][cmatriz] == cadena[i]; cmatriz++)
			{

				for (int f=1; f<6; f++)
				{
					if (letras[f][cmatriz] != ' ')
					put_pixel(screen, x, y, 0);
					y++;
				}
				x++;
				y=_y/2;
			}
			x+=3;
		}
	}
	else
	{
		for (i=0; cadena[i] != '\0'; i++)
		{

			for (cmatriz=0; letras[0][cmatriz] != cadena[i]; cmatriz++)
				;

			for (; letras[0][cmatriz] == cadena[i]; cmatriz++)
			{

				for (int f=1; f<6; f++)
				{
					if (letras[f][cmatriz] != ' ')
					{
						put_pixel(screen, x, y, 0);
						put_pixel(screen, x+1, y, 0);
						put_pixel(screen, x+1, y+1, 0);
						put_pixel(screen, x, y+1, 0);
					}

					y+=3;
				}

				x+=3;
				y=_y;
			}
			x+=5;
		}
	}

	SDL_Flip(screen);
}
