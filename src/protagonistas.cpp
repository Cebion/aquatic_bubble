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

#include "protagonistas.h"
#include "juego.h"
#include "enum.h"

enum {PARADO, CAMINA, CORRE, DISPARA, DISPARA_CORRIENDO, SALTA, DISPARA_SALTANDO, MUERE,INICIANDO,ESPERA};


/*!
 * \brief imprime a silvio.
 */
void protagonistas :: imprimir(SDL_Surface *screen, SDL_Rect *rect)
{
	if(hab_intermitente == 0)
	{
		ima->imprimir(animaciones[estado][paso], screen, rect, x, y, flip);
		return;
	}
	else
	{
		if(es_par())
		ima->imprimir(animaciones[estado][paso], screen, rect, x, y, flip);
	}
}

/*!
 * \brief le avisa para que cambie su estado a muerto.
 */
void protagonistas :: colision_con_enemigo()
{
	if (estado == MUERE)
		return;
	
	reiniciar_animacion();
	estado=MUERE;
	velocidad=-10;

	
}

/*!
 *\brief gestiona el estado muerto de silvio.
 */
int protagonistas :: terminar(void)
{	
	y+=velocidad >>3;

	no_avanzar();	
	velocidad++;

	if (y>640+150)
	{

		if (vidas > 0)
		{
			vidas--;
			juego->barra.set_vidas(jugador, vidas);

			x=x_inicial;
			y=y_inicial;
			set_velocidad();	
			hab_intermitente=1;
			intermitente=600;
			estado=INICIANDO;
			
			reiniciar_animacion();
		}
		else
		{
			//juego->mundo->cambiar_escena(MENU);
			if(continuar > 0)
			{
				estado=ESPERA;
				juego->mensaje(jugador, MPUEDE_CONTINUAR);
				return 0;
			}
			else		  
			{
				juego->mensaje(jugador, MSIN_CREDITOS);
				return 1;
			}
			// pierde todo
		}
	}

	avanzar_animacion();
	return 0;
}

bool protagonistas :: es_par(void)
{
	if(((intermitente >> 4) %2 ) == 0)	  
		return true;
	else
		return false;
}

bool protagonistas :: enemigo_cerca(int avanze,int jugador)
{
	if(juego->procesos.hay_enemigo_cerca(avanze,jugador))
		return true;
	else
		return false;
}

bool protagonistas :: pide_tecla(int codigo)
{
	if((juego->mundo->perifericos.get_tecla(codigo)))
			  return true;
	return false;
}
		
void protagonistas :: actualizar_tecla()
{
	juego->mundo->perifericos.actualizar();
}
		
