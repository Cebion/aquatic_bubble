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

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "cadena.h"
#include "int_gettext.h"
#include "enum.h"

cadena :: cadena()
{
	letras = NULL;
	detenido = false;
}

/*!
 * \brief destructor
 */
cadena :: ~cadena()
{
	delete [] letras;
}

/*!
 * \brief genera el mensaje de cadena y vincula el objeto
 */
void cadena :: iniciar(class grafico *ima, char *cadena, enum tipo_anim animacion, int x, int y, int w, int h, enum ancla ancla)
{
	this->ima = ima;
	this->animacion = animacion;
	
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->ancla = ancla;
	
	paso=0;
	visible = true;
	detenido = false;
	
	activado = 0;
	crear_texto(cadena);
}


/*!
 * \brief regenera la cadena con un nuevo texto
 */
void cadena :: reiniciar(char *cadena)
{
	delete [] letras;

	paso=0;
	detenido = false;
	visible = true;
	
	activado = 0;
	crear_texto(cadena);
}


/*!
 * \brief regenera la cadena con un nuevo texto
 */
void cadena :: reiniciar(char *cadena, enum tipo_anim anim)
{
	delete [] letras;

	paso=0;
	detenido = false;
	visible = true;
	
	activado = 0;
	
	this->animacion = anim;
	crear_texto(cadena);
}


/*!
 * \brief realiza la animación
 */
void cadena :: actualizar_invertido(void)
{
	int incx;
	int incy;
	int letras_en_movimiento=0;

	if (!visible)
		return;
	
	for (int i=0; i<cant_letras; i++)
	{
		incx = (letras[i].xdest - letras[i].x) /8;
		incy = (letras[i].ydest - letras[i].y) /8;

		if (incx == 0 && letras[i].xdest != letras[i].x)
			letras[i].xdest > letras[i].x? incx=1: incx=-1;

		if (incy == 0 && letras[i].ydest != letras[i].y)
			letras[i].ydest > letras[i].y? incy=1: incy=-1;
		
		if (incx != 0 || incy != 0)
		{
			letras[i].x -= incx;
			letras[i].y -= incy;
			letras_en_movimiento++;
		}
	}

	if (letras_en_movimiento == 0)
	{
		detenido = true;
	}
	else
		detenido = false;
		

	if (animacion == ASALIDA || animacion == AQUITAR)
	{
		if (paso == 100)
		{
			for (int i=0; i<cant_letras; i++)
				letras[i].xdest = 740 +30*i;

		}
		else
		{
			if (paso == 130)
				visible = false;
		}
		
		paso++;
	}

	if (animacion == ASUBE)
	{
		for (int i=0; i<cant_letras; i++)
		{
			letras[i].y ++;
			letras[i].ydest ++;
		}
	}
}




/*!
 * \brief realiza la animación
 */
void cadena :: actualizar(void)
{
	int incx;
	int incy;
	int letras_en_movimiento=0;

	if (!visible)
		return;
	
	for (int i=0; i<cant_letras; i++)
	{
		incx = (letras[i].xdest - letras[i].x) /8;
		incy = (letras[i].ydest - letras[i].y) /8;

		if (incx == 0 && letras[i].xdest != letras[i].x)
			letras[i].xdest > letras[i].x? incx=1: incx=-1;

		if (incy == 0 && letras[i].ydest != letras[i].y)
			letras[i].ydest > letras[i].y? incy=1: incy=-1;
		
		if (incx != 0 || incy != 0)
		{
			letras[i].x += incx;
			letras[i].y += incy;
			letras_en_movimiento++;
		}
	}

	if (letras_en_movimiento == 0)
	{
		detenido = true;
	}
	else
		detenido = false;
		

	if (animacion == ASALIDA || animacion == AQUITAR)
	{
		if (paso == 100)
		{
			for (int i=0; i<cant_letras; i++)
				letras[i].xdest = 740 +30*i;

		}
		else
		{
			if (paso == 130)
				visible = false;
		}
		
		paso++;
	}

	if (animacion == ASUBE)
	{
		for (int i=0; i<cant_letras; i++)
		{
			letras[i].y --;
			letras[i].ydest --;
		}
	}
}


/*!
 * \brief cambia la cadena de cadena actual por otra
 */
void cadena :: cambiar_texto(char *cadena)
{
	int x;
	int y;
	int longitud; // incluye espacios
	
	visible=true;
	
	longitud = strlen(cadena);
	cant_letras = get_cant_letras(cadena);

	// posicion final de la primer letra
	y = this->y;

	switch (ancla)
	{
		case LEFT:
			x = this->x;
			break;

		case RIGHT:
			x = this->x - longitud*(w-2);
			break;

		case CENTER:
			x = this->x - ((w*(longitud-1))/2);
			break;
			
		default:
			printf(_("In cadena.cpp (line %d): invalid %s value\n"), __LINE__, "'ancla'");
			x = this->x - ((w*(longitud-1))/2);
			break;
	}

	delete [] letras;

	letras = new struct letra[cant_letras];

	for (int i=0,j=0; i < longitud; i++)
	{
		if (cadena[i] != ' ')
		{
			letras[j].xdest = x+i*w;
			letras[j].ydest = y;

			letras[j].x = letras[j].xdest;
			letras[j].y = y;

			
			asignar_grafico(letras[j].grafico, cadena[i]); 
			j++;
		}
	}
}


/*!
 * \brief cambia la cadena de cadena actual por un numero
 */
void cadena :: cambiar_texto(int numero)
{
	char cadena[50];
	int x;
	int y;
	int longitud; // incluye espacios

	visible = true;

	cadena[0] = '0' + (numero/10000)%10;
	cadena[1] = '0' + (numero/1000)%10;
	cadena[2] = '0' + (numero/100)%10;
	cadena[3] = '0' + (numero/10)%10;
	cadena[4] = '0' + (numero/1)%10;
	cadena[5] = '\0';
	
	delete [] letras;
	
	longitud = strlen(cadena);
	cant_letras = get_cant_letras(cadena);

	// posicion final de la primer letra
	x = this->x - ((w*(longitud-1))/2);
	y = this->y;

	letras = new struct letra[cant_letras];

	for (int i=0,j=0; i < longitud; i++)
	{
		if (cadena[i] != ' ')
		{
			letras[j].xdest = x+i*w;
			letras[j].ydest = y;

			letras[j].x = letras[j].xdest;
			letras[j].y = y;

			
			asignar_grafico(letras[j].grafico, cadena[i]); 
			j++;
		}
	}
}



/*!
 * \brief imprime el cadena sobre screen
 */
void cadena :: imprimir(SDL_Surface *screen, SDL_Rect *rect, int &lim)
{
	struct letra l;

	if (!visible)
		return;


	for (int i=0; i<cant_letras; i++)
	{
		l = letras[i];
		ima->imprimir(l.grafico+activado*52, screen, &(rect[lim]), l.x, l.y, 1);
		lim++;
	}
}

/*!
 * \brief genera todas las letras del cadena
 */
void cadena :: crear_texto(char *cadena)
{
	int x;
	int y;
	int longitud; // incluye espacios

	longitud = strlen(cadena);
	cant_letras = get_cant_letras(cadena);
	
	// posicion final de la primer letra
	x = this->x - ((w*(longitud-1))/2);
	y = this->y;

	letras = new struct letra[cant_letras];

	for (int i=0,j=0; i < longitud; i++)
	{
		if (cadena[i] != ' ')
		{
			letras[j].xdest = x+i*w;
			letras[j].ydest = y;

			switch (animacion)
			{
				case ANONE:
					letras[j].x = letras[j].xdest;
					letras[j].y = letras[j].ydest;
					break;

				case ASUBE:
					letras[j].x = letras[j].xdest;
					letras[j].y = letras[j].ydest+100;
					break;

					
				case AUPLEFT:
					letras[j].x = -10 -30*i;
					letras[j].y = -10 -30*i;
					break;

				case AUPRIGHT:
					letras[j].x = 650 +30*i;
					letras[j].y = -10 -30*i;
					break;

				case ALEFT:
					letras[j].x = -10 -30*i;
					letras[j].y = letras[j].ydest;
					break;

				case ARIGHT:
					letras[j].x = 650 +30*i;
					letras[j].y = letras[j].ydest;
					break;

				case ASALIDA:
					letras[j].x = -10 -30*longitud +30*i;
					letras[j].y = letras[j].ydest;
					break;

				case AQUITAR:
					paso = 100;
					break;
				
				default:
					printf(_("in source code (%s), animation not expected\n"), "cadena :: crear_texto" );
					break;
			}
			
			asignar_grafico(letras[j].grafico, cadena[i]); 
			j++;
		}
	}
}


/*!
 * \brief Define el numero de grafico para un caracter
 */
void cadena :: asignar_grafico(int &grafico, const char letra)
{
	grafico = 0;

	if (letra >= 'A' && letra <= 'Z')
	{
		grafico = letra - 'A';
		return;
	}

	if (isdigit(letra))
	{
		grafico = letra - '0' + 40;
		return;
	}

	switch (letra)
	{
		case '>':
			grafico = 51;
			return;

		case '<':
			grafico = 50;
			return;

		case ':':
			grafico = 26;
			return;

		case '/':
			grafico = 27;
			return;

		case ',':
			grafico = 28;
			return;
			
		case '.':	
			grafico = 29;
			return;

		case '-':
			grafico = 30;
			return;

		case '_':
			grafico = 31;
			return;
			
		case '(':
			grafico = 32;
			return;

		case ')':
			grafico = 33;
			return;

		case '@':
			grafico = 34;
			return;

		case '"':
			grafico = 35;
			return;
			
		case '?':
			grafico = 36;
			return;

		case '¿':
			grafico = 37;
			return;

		case '!':
			grafico = 38;
			return;

		case '¡':
			grafico = 39;
			return;
			
		default:
			printf(_("in source code (%s), not found graphic for '%c'\n"), "cadena :: asignar_grafico", letra);
	}

}

/*!
 * \brief obtiene la longitud de la cadena sin contar los espacios en blanco
 */
int cadena :: get_cant_letras(const char *cadena)
{
	int ret=0;
	
	for (int i=0; cadena[i] != '\0'; i++)
	{
		if (cadena[i] != ' ')
			ret++;
	}

	return ret;
}


/*!
 * \brief resalta el cadena
 */
void cadena :: activar(void)
{
	activado = 1;
}


/*!
 * \brief restaura el mensaje
 */
void cadena :: desactivar(void)
{
	activado = 0;
}


/*!
 * \brief marca la opcion
 */
void cadena :: tildar(void)
{
	bool encuentra = false;
	
	for (int i=0; i<cant_letras; i++)
	{
		if (letras[i].grafico == 50 || letras[i].grafico == 51)
		{
			encuentra = true;
			letras[i].grafico = 51;
		}
	}

	if (!encuentra)
		printf(_("Can't select option, marc not found (function %s)\n"), "cadena :: tildar");
}


/*!
 * \brief desmarca la opcion
 */
void cadena :: destildar(void)
{
	bool encuentra = false;
	
	for (int i=0; i<cant_letras; i++)
	{
		if (letras[i].grafico == 50 || letras[i].grafico == 51)
		{
			encuentra = true;
			letras[i].grafico = 50;
			return;
		}
	}

	if (!encuentra)
		printf(_("Can't ??? option, marc not found (function %s)\n"), "cadena :: tildar");
}


/*!
 * \brief altera los guiones en el cadena
 */
void cadena :: agregar_letra(char tecla)
{
	bool encuentra = false;
	
	for (int i=0; i<cant_letras; i++)
	{
		if (letras[i].grafico == 30)
		{
			encuentra = true;
			asignar_grafico(letras[i].grafico, tecla);
			break;
		}
	}
	
	if (!encuentra)
		printf(_("Can't found crosses (function %s)\n"),\
				"cadena :: cambiar_guiones");
}


/*!
 * \brief altera los guiones en el cadena
 */
void cadena :: cambiar_guiones(char *cambio)
{
	bool encuentra = false;
	int j=0;
	
	for (int i=0; i<cant_letras && cambio[j] != '\0'; i++)
	{
		if (letras[i].grafico == 30)
		{
			encuentra = true;
			asignar_grafico(letras[i].grafico, cambio[j]);
			j++;
		}
	}
	
	if (!encuentra)
		printf(_("Can't found crosses (function %s)\n"),\
				"cadena :: cambiar_guiones");
}


/*!
 * \brief obtiene el texto de la opcion
 */
void cadena :: get_texto(char *cadena)
{
	int i;

	for (i=0; i < cant_letras; i++)
		cadena[i] = letras[i].grafico + 'A';
	
	cadena[i] = '\0';
}
