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
#include "perifericos.h"
#include <ctype.h>
#include <string.h>

/*!
 * \brief carga las teclas por defecto
 */
void perifericos :: iniciar()
{
	int i;
	SDLKey vector[16]={SDLK_ESCAPE,SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_RCTRL,SDLK_RETURN,SDLK_h,SDLK_n,SDLK_b,SDLK_m,SDLK_LCTRL};

	ultima_tecla=0;
	
	for(i=0;i<16;i++)
		set_tecla(i,vector[i]);
}


/*!
 * \brief verifica cualquier cambio en los controles
 */
void perifericos :: actualizar(void)
{
	tecla = SDL_GetKeyState(NULL);
}


/*!
 * \brief informa si la tecla fué pulsada
 */
bool perifericos :: get_tecla(int codigo_tecla)
{
	if(tecla[vec_teclas[codigo_tecla]])
			 return true;

	return false;
}


/*!
 * \brief altera una tecla
 */
void perifericos :: set_tecla(int codigo_tecla, SDLKey nueva)
{
	vec_teclas[codigo_tecla]=nueva;
}

/*!
 * \brief obtiene el numero que se ha pulsado en ese momento
 * 
 * \return 0 si no se pulsa ninguna tecla
 */
SDLKey perifericos :: get_SDLK(char *nombre)
{
	int i;


	for (i=SDLK_a; i<= SDLK_z; i++)
	{
		if (tecla[i])
		{
			nombre[0] = toupper(i);
			nombre[1] = '\0';
			return (SDLKey) i;
		}
	}

	for (i=SDLK_0; i<= SDLK_9; i++)
	{
		if (tecla[i])
		{
			nombre[0] = i;
			nombre[1] = '\0';
			return (SDLKey) i;
		}
	}

	for (i=SDLK_KP0; i<= SDLK_KP9; i++)
	{
		if (tecla[i])
		{
			nombre[0] = 'K';
			nombre[1] = i - SDLK_KP0 + '0';
			nombre[2] = '\0';
			return (SDLKey) i;
		}
	}
	
	if (tecla[SDLK_SPACE])
	{
		strcpy(nombre, "SPACE");
		return SDLK_SPACE;
	}

	if (tecla[SDLK_UP])
	{
		strcpy(nombre, "UP");
		return SDLK_UP;
	}

	if (tecla[SDLK_DOWN])
	{
		strcpy(nombre, "DOWN");
		return SDLK_DOWN;
	}

	if (tecla[SDLK_LEFT])
	{
		strcpy(nombre, "LEFT");
		return SDLK_LEFT;
	}

	if (tecla[SDLK_RIGHT])
	{
		strcpy(nombre, "RIGHT");
		return SDLK_RIGHT;
	}

	if (tecla[SDLK_LSHIFT])
	{
		strcpy(nombre, "LSHIFT");
		return SDLK_LSHIFT;
	}

	if (tecla[SDLK_RSHIFT])
	{
		strcpy(nombre, "RSHIFT");
		return SDLK_RSHIFT;
	}

	if (tecla[SDLK_LALT])
	{
		strcpy(nombre, "LALT");
		return SDLK_LALT;
	}

	if (tecla[SDLK_RALT])
	{
		strcpy(nombre, "RALT");
		return SDLK_RALT;
	}

	if (tecla[SDLK_LCTRL])
	{
		strcpy(nombre, "LCTRL");
		return SDLK_LCTRL;
	}

	if (tecla[SDLK_RCTRL])
	{
		strcpy(nombre, "RCTRL");
		return SDLK_RCTRL;
	}

	if (tecla[SDLK_TAB])
	{
		strcpy(nombre, "TAB");
		return SDLK_TAB;
	}

	if (tecla[SDLK_END])
	{
		strcpy(nombre, "END");
		return SDLK_END;
	}

	if (tecla[SDLK_INSERT])
	{
		strcpy(nombre, "INS");
		return SDLK_INSERT;
	}

	if (tecla[SDLK_HOME])
	{
		strcpy(nombre, "HOME");
		return SDLK_HOME;
	}

	if (tecla[SDLK_PAGEUP])
	{
		strcpy(nombre, "PUP");
		return SDLK_PAGEUP;
	}

	if (tecla[SDLK_PAGEDOWN])
	{
		strcpy(nombre, "PDOWN");
		return SDLK_PAGEDOWN;
	}

	if (tecla[SDLK_DELETE])
	{
		strcpy(nombre, "DEL");
		return SDLK_DELETE;
	}

	
	return SDLK_UNKNOWN;
}

/*!
 * \brief selecciona alguna tecla de aceptación (s, y)
 */
bool perifericos :: acepta(void)
{
	if (tecla[SDLK_s] || tecla[SDLK_y])
		return true;
	else
		return false;
}


bool perifericos :: rechaza(void)
{
	if (tecla[SDLK_n])
		return true;
	else
		return false;
}	
