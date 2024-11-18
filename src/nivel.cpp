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

#include "nivel.h"
#include "int_gettext.h"


nivel :: nivel()
{
	for (int i=0; i<30; i++) 
	{
		for (int j=0; j<40; j++) 
			tiles[i][j] = 0;
	}

}

/*!
 * \brief inicia el objeto nivel
 */
int nivel :: iniciar(class grafico *ima)
{
	this->ima = ima;
	
	nivel_actual=1;
	cargar_nivel(nivel_actual);

	return 0;
}


/*!
 * \brief imprime todo el escenario
 */
void nivel :: imprimir(SDL_Surface *destino)
{
	int i,j;
	SDL_Rect rect;
	SDL_Surface *imagen;

	imagen = IMG_Load(DATA_DIR "/ima/otro.jpg");
	
	if (imagen == NULL)
	{
		printf(_("Can't load background image: %s\n"), SDL_GetError());
		return;
	}
	

	SDL_BlitSurface(imagen,0,destino,0);
	
	for (i=0; i<30; i++)
	{
		for (j=0; j<40; j++)
		{
			if (tiles[i][j] != 5)
			    ima->imprimir(tiles[i][j], destino, &rect, j*16,i*16, 1) ;
		}
	}
	SDL_FreeSurface(imagen);	
}

/*!
 * \brief obtiene distancia al suelo
 * 
 * \return distancia al suelo o rango si no encontró el suelo
 */
int nivel ::get_dist_suelo(int x, int y, int rango)
{
	int i,colision;
	
	for(i=0;i<rango;i++)
	{
		colision = get_colision(x,y+i-7);
		
		if(colision)
			return i;
	}
	
	return i;
}

/*!
 * \brief informa si un sector del nivel es solido
 *
 * \return 1 es solido, 0 en caso contrario
 */
int nivel :: get_colision(int x,int y)
{
	int bloque;

	bloque = tiles[y/16][x/16];

	switch (bloque)
	{
		case 5:
			return 0;
		
		case 1:
		case 6:
			if(y%16 < 3)
				return 1;
			break;
			
		case 3:
			x= x%16;
			y= y%16;
				
			if(y >= (-x +15))
				return 1;
						 
			break;
				
		case 2:
			x= x%16;
			y= y%16;

			if(x<=y)
				return 1;
						 
			break;
	}
	
	return 0;
}


/*!
 * \brief obtiene la distancia al una pared
 *
 * \return distancia al suelo o rango si no encontró el suelo
 */
int nivel :: get_dist_pared(int x, int y, int rango)
{
	int i;
	int dir;
	int bloque;

	if (rango > 0)
		dir=1;
	else
		dir=-1;

	rango = abs(rango);

	// busca una pared desplazando x sobre el punto (x,y)
	for (i=0; i<rango ; i++)
	{
		bloque = tiles[y/16][(x+(dir*i))/16];

		if (bloque == 0)
			return i*dir;
	}

	return rango*dir;
}


/*!
 * \brief carga el siguiente nivel y todos sus personajes
 *
 * \return -1 si se terminaron todos los niveles
 */
int nivel :: avanzar_nivel(class procesos *procesos)
{
	nivel_actual++;
	
	if (cargar_nivel(nivel_actual))
	{
		printf("tmp: no hay mas niveles en nivel :: avanzar_nivel\n");
		return 1;
	}
	else
		return 0;
}


/*!
 * \brief carga los bloques del nivel
 *
 * \return 1 si se terminaron todos los niveles
 */
int nivel :: cargar_nivel(int numero)
{
	int mapa[30][40]=\
	{
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,3,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,5,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,1,1,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
	{0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0},
	};

	
	for (int i=0; i<30; i++) 
	{
		for (int j=0; j<40; j++) 
			tiles[i][j]=mapa[i][j];
	}

	if (numero > 1)
	{
		for (int j=0; j<40; j++)
			tiles[10][j]= (numero + j)%3;
	}

	return 0;
}

/*!
 * \brief inicia el nivel indicado
 */
void nivel :: saltar_nivel(int numero)
{
	cargar_nivel(numero);
	nivel_actual = numero;
}
