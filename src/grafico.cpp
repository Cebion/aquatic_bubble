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

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "grafico.h"
#include "int_gettext.h"

/*!
 * \brief carga una biblioteca de graficos
 * 
 * \return 1 en caso de error
 */
int grafico ::  iniciar (char * _ruta, int f, int c, enum ancla ancla, \
		enum resolucion res, int alpha)
{
	SDL_Surface *tmp;
	char ruta[200] = DATA_DIR "/ima/";

	fil=0;
	col=0;
	w=0;
	h=0;
	px=0;
	py=0;
	reducido=0;
	
	strcat(ruta,_ruta);

	tmp = IMG_Load(ruta);

	if (tmp == NULL)
	{
		printf(_("- Can't open %s file\n"), ruta);
		return 1;
	}

	w=tmp->w/c;
	h=tmp->h/f;
	
	definir_ancla(ancla);
	
	if (res == BAJA)
	{
		tmp = reescalar_mitad(tmp);

		if (tmp == NULL)
		{
			printf(_("- Can't scale %s image file\n"), ruta );
			return 1;
		}
	
		reducido=1;
	}
	else
		reducido=0;


	ima = SDL_DisplayFormat(tmp);
	if (ima == NULL)
	{
		printf("- error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_FreeSurface(tmp);


	SDL_SetColorKey(ima, SDL_SRCCOLORKEY, \
			SDL_MapRGB( ima->format, 255, 0, 255));

	if (alpha != 255)
		SDL_SetAlpha(ima, SDL_SRCALPHA, alpha);
	
	w=ima->w/c;
	h=ima->h/f;
	fil=f;
	col=c;

	return 0;
}


void grafico :: imprimir(int indice, SDL_Surface *destino)
{
	if (indice < 0 || indice > (col*fil) )
	{
		printf(_("in function %s, invalid graphic number\n"), \
				"grafico :: imprimir");
		return;
	}

	// recorte del grafico a imprimir
	if (reducido)
	{
		captura.w=w-1;
		captura.h=h-1;
		captura.y=(indice/col)*h +1;
		captura.x=(indice%col)*w +1;
	}
	else
	{
		captura.w=w-2;
		captura.h=h-2;
		captura.y=(indice/col)*h +2;
		captura.x=(indice%col)*w +2;
	}

	SDL_BlitSurface(ima, &captura, destino, NULL);
}


/*!
 * \brief imprime un grafico de la biblioteca sobre 'destino'
 */
void grafico :: imprimir(int indice, SDL_Surface *destino, SDL_Rect *rect, int x, int y, int flip)
{

	if (indice < 0 || indice > (col*fil) )
	{
		
		if (rect != NULL)
		{
			rect->x=0;
			rect->y=0;
			rect->w=1;
			rect->h=1;
		}
		
		printf(_("Can't show graphic number %d, out of range [0,%d]\n")\
				, indice, col*fil);
		return;
	}

	// recorte del grafico a imprimir
	if (reducido)
	{
		captura.w=w-1;
		captura.h=h-1;
		captura.y=(indice/col)*h +1;
		captura.x=(indice%col)*w +1;
	}
	else
	{
		captura.w=w-2;
		captura.h=h-2;
		captura.y=(indice/col)*h +2;
		captura.x=(indice%col)*w +2;
	}

	tmp.y = y-py;
	tmp.x = x-px;
	
	if (destino->w == 320)
	{
		tmp.x /= 2;
		tmp.y /= 2;
	}

	if (flip==1)
	{
		SDL_BlitSurface(ima, &captura, destino, &tmp);
	}
	else
	{
		src_rect.x = captura.x;
		src_rect.y = captura.y;
		src_rect.w = 1;
		src_rect.h = h-2;

		dest_rect.x = tmp.x + w -3;
		dest_rect.y = tmp.y;
		
		for (i=0; i< w-2; i++)
		{
			if (dest_rect.x >= 0 && dest_rect.x < destino->w)
				SDL_BlitSurface(ima, &src_rect, destino, &dest_rect);

			dest_rect.x --;
			src_rect.x ++;
			dest_rect.y = tmp.y;			
		}

		tmp.w = w+1;
		tmp.h = h;
	}


	if (rect != NULL)
	{
		rect->x = tmp.x;
		rect->y = tmp.y;
		rect->w = tmp.w;
		rect->h = tmp.h;
			
		recortar_rectangulo(rect, destino->w, destino->h);
	}

//	imprimir_rectangulo(rect, destino);
}


/*!
 * \brief define la coordenada eje o punto de control de la imagen
 */
void grafico :: definir_ancla(enum ancla ancla)
{
	switch (ancla)
	{
		case UP_LEFT:
			px=0;
			py=0;
			break;

		case UP:
			px=w/2;
			py=0;
			break;

		case UP_RIGHT:
			px=w;
			py=0;
			break;
			
		case LEFT:
			px=0;
			py=h/2;
			break;

		case CENTER:
			px=w/2;
			py=h/2;
			break;

		case RIGHT:
			px=w;
			py=h/2;
			break;

		case DOWN_LEFT:
			px=0;
			py=h;
			break;

		case DOWN:
			px=w/2;
			py=h;
			break;

		case DOWN_RIGHT:
			px=w;
			py=h;
			break;

		default:
			printf(_("invalid %s value in function %s\n"),"ancla",\
						"grafico :: definir_ancla");
	}

}



/*!
 * \brief recorta el rectangulo para que no salga de la pantalla
 */
void grafico :: recortar_rectangulo(SDL_Rect *rect, int w, int h)
{
	if (rect->x >= w || rect->y >= h || rect->x + rect->w < 0 || rect->y + rect->h < 0)
	{
		rect->x=0;
		rect->y=0;
		rect->w=0;
		rect->h=0;
	}

	if (rect->y < 0)
	{
		rect->h += rect->y;
		rect->y = 0;
	}
	
	if (rect->x < 0)
	{
		rect->w += rect->x;
		rect->x = 0;
	}

	if (rect->x + rect->w >= w)
		rect->w = w - rect->x;

	if (rect->y + rect->h >= h)
		rect->h = h - rect->y;
}

/*!
 * \brief descarga la imagen de memoria
 */
void grafico :: terminar(void)
{
	SDL_FreeSurface(ima);
}


/*!
 * \brief imprime un rectangulo de color
 */
void grafico :: imprimir_rectangulo(SDL_Rect *rect, SDL_Surface *destino)
{
	SDL_Rect r;

	r.x=rect->x;
	r.y=rect->y;
	r.h=rect->h;
	r.w=1;
	SDL_FillRect(destino , &r, 255);

	r.x=rect->x+rect->w-1;
	SDL_FillRect(destino, &r, 255);

	r.x=rect->x;
	r.y=rect->y;
	r.h=1;
	r.w=rect->w;
	SDL_FillRect(destino, &r, 255);

	r.y=rect->y+rect->h-1;
	SDL_FillRect(destino, &r, 255);
}


/*!
 * \brief obtiene un punto
 */
Uint32 grafico :: get_pixel(SDL_Surface *_ima, int x, int y)
{
	int bpp = _ima->format->BytesPerPixel;
	Uint8 *p= (Uint8 *) _ima->pixels + y*_ima->pitch + x*bpp;

	switch (bpp)
	{
		case 1:
			return *p;
			break;
			
		case 2:
			return *(Uint16 *)p;
			break;
			
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			
			break;
			
		case 4:
			return *(Uint32 *)p;
			break;
	}

	return 0;
}
  
/*!
 * \brief imprime un pixel
 */
void grafico :: put_pixel(SDL_Surface *_ima, int x, int y, Uint32 pixel)
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
 * \brief obtiene los componentes rojo, verde, azul y alpha de un pixel
 */
void grafico :: obtener_componentes(SDL_Surface *ima, SDL_Color &color, int x, int y)
{
	Uint8 *buffer = (Uint8*) ima->pixels + ima->pitch*y + x*ima->format->BytesPerPixel;
	Uint32 *p;
//	Uint32 pixel;

	p = (Uint32*) buffer;
	
//	pixel = (Uint32) *buffer;
	
	SDL_GetRGBA(*p, ima->format, &color.r, &color.g, &color.b, &color.unused);
}



/*!
 * \brief reduce una imagen a la mitad de su tamaño
 *
 * \return imagen reducida
 */
SDL_Surface* grafico :: reescalar_mitad(SDL_Surface *ima)
{
	SDL_Surface *ima2;
	SDL_Color color;
	Uint32 r_aux, g_aux, b_aux, a_aux;
	int pixeles;
	int paso;

	ima2 = SDL_CreateRGBSurface(SDL_SWSURFACE, ima->w/2, \
			ima->h/2, ima->format->BitsPerPixel, \
			ima->format->Rmask, ima->format->Gmask, \
			ima->format->Bmask, ima->format->Amask);

	if (ima2 == NULL)
	{
		printf(_("- error in function %s, can't copy image\n"), \
				"grafico :: reescalar_mitad");
		
		return NULL;
	}

	SDL_FillRect(ima2, NULL, SDL_MapRGB(ima2->format, 255, 0, 255));
	
	SDL_LockSurface(ima);
	SDL_LockSurface(ima2);
	
	for (int i=0; i<ima2->w; i++)
	{
		for (int j=0; j<ima2->h; j++)
		{
			r_aux = 0;
			g_aux = 0;
			b_aux = 0;
			a_aux = 0;
			pixeles = 0;

			for (paso=0; paso<4; paso++)
			{
				int posx[] = {i*2, i*2+1, i*2+1, i*2};
				int posy[] = {j*2, j*2+1, j*2,   j*2+1};

				obtener_componentes(ima, color, posx[paso], posy[paso]);

				if (!(color.r == 255 && color.g == 0 && color.b == 255))
				{
					r_aux += color.r;
					g_aux += color.g;
					b_aux += color.b;
					a_aux += color.unused;
					pixeles++;
				}
				
				if (pixeles > 0)
				{
					color.r = (Uint8) (r_aux/pixeles);
					color.g = (Uint8) (g_aux/pixeles);
					color.b = (Uint8) (b_aux/pixeles);
					color.unused = (Uint8) (a_aux/pixeles);

					put_pixel(ima2, i, j, SDL_MapRGBA(ima->format, color.r, color.g, color.b, color.unused));
				}
			}
			
		}
	}
	
	SDL_UnlockSurface(ima);
	SDL_UnlockSurface(ima2);

	SDL_FreeSurface(ima);	

	return ima2;
}
