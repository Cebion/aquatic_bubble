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
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mundo.h"
#include "juego.h"
#include "menu.h"
#include "creditos.h"
#include "records.h"
#include "transicion.h"
#include "int_gettext.h"

mundo :: mundo()
{
	actual = NULL;
	debe_terminar = false;

	set_juego(0, 1, 0);
}

/*!
 * \brief inicializa la biblioteca y los recursos básicos
 *
 * \return 1 en caso de error
 */
int mundo :: iniciar (bool fullscreen, bool musica, bool sonido, enum resolucion res, int test)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("- error: %s\n", SDL_GetError());
		return 1;
	}

	this->fullscreen = fullscreen;
	this->res = res;

	if (audio.iniciar(musica, sonido))
		return 1;
	
	if (iniciar_pantalla())
		return 1;
	
	definir_ventana();
	
	dialogo.iniciar(screen);

	if (libgrafico.iniciar(&dialogo, screen, res))
		return 1;

	escena_anterior = -1;
	escena_actual = 0;

	perifericos.iniciar();
	transicion.crear_superficies(screen);

	marcas.iniciar();

	if (test)
		cambiar_escena(JUEGO);
	else
		cambiar_escena(MENU);
	
	return 0;
}


/*!
 * \brief mantiene la velocidad constante del juego
 */
void mundo :: correr (void)
{
	SDL_Event evento;
	int fps=0;
	int tframe = -100; // tick del último fps actualizado
	int rep, i;
	
	#define TICK_POR_LOGICO (1000/100)
	#define TICK_POR_FRAME (1000/100)

	reiniciar_reloj();

	while (procesar_eventos(&evento))
	{
		if (debe_terminar)
			return;
		
		if (escena_anterior != escena_actual)
			aplicar_cambio_escena();

		perifericos.actualizar();
		t = SDL_GetTicks();
		
		
		// cuadros por segundo
		if (t - tframe > 1000)
		{
//			printf("fps = %d\n", fps);
			tframe = t;
			fps=0;
		}

		// lógica
		if (t - tl > TICK_POR_LOGICO)		
		{
			rep = (t - tl) / TICK_POR_LOGICO;

			if (rep>0)
			{
				for (i=0; i < rep; i++)
				{
					if (transicion.termino())
						actual->actualizar();
					else
						transicion.actualizar();

					perifericos.actualizar();
				}

				tl += TICK_POR_LOGICO*rep;
			}

			// grafica
			if (t - tg > TICK_POR_FRAME)		
			{
				if (transicion.termino())
					actual->imprimir();
				else
					transicion.imprimir();

				fps++;
				tg += TICK_POR_FRAME;
			}
		}
		else
			SDL_Delay(TICK_POR_LOGICO - (t -tl));



	}

}


/*!
 * \brief atiende los eventos de la ventana
 * 
 * \return 1 si la aplicacion debe seguir en ejecución
 */
int mundo :: procesar_eventos(SDL_Event *evento)
{
	
	while (SDL_PollEvent(evento))
	{
		switch (evento->type)
		{
			case SDL_QUIT:
				return 0;
				break;

			case SDL_KEYDOWN:
				switch (evento->key.keysym.sym)
				{
					case SDLK_F1:
						audio.cambiar_sonido();
						break;

					case SDLK_F2:
						audio.cambiar_musica();
						break;

					case SDLK_F3:
						if (transicion.termino() && libgrafico.termino())
						cambiar_modo_video();
						break;

					case SDLK_F4:
						pantalla_completa();
						break;

					case SDLK_F10:
						return 0;
						break;
						
	
					default:
						break;
				}
				break;
				
			default:
				break;
		}
	}
	
	return 1;
}


/*!
 * \brief informa que se debe terminar el programa, terminar_todo aplica el pedido
 */
void mundo :: terminar(void)
{
	debe_terminar=true;
}


/*!
 * \brief informa que se tiene que cambiar la escena ('correr' detecta el cambio)
 */
void mundo :: cambiar_escena(enum nro_escena nueva_escena)
{
	escena_actual = nueva_escena;
}


/*!
 * \brief aplica el cambio de escena informado por la funcion cambiar_escena
 */
void mundo :: aplicar_cambio_escena(void)
{
	SDL_Surface *buffer = SDL_DisplayFormat(screen);
	
	if (actual)
	{
		if (buffer)
		{
			actual->capturar_pantalla(buffer);
			transicion.define_anterior(buffer);
		}
		
		delete actual;
	}

	switch (escena_actual)
	{
		case MENU:
			actual = new menu;
			transicion.reiniciar(DESDEABAJO);
			break;

		case JUEGO:
			actual = new juego;
			transicion.reiniciar(DESDEARRIBA);
			break;

		case CREDITOS:
			actual = new creditos;
			transicion.reiniciar(DESDEARRIBA);
			break;

		case RECORDS:
			actual = new records;
			transicion.reiniciar(DESDEARRIBA);
			break;
		

		default:
			printf(_("error, escene not found in function %s\n"), \
						"mundo::aplicar_cambio_escena");
			return;
			break;
			
	}

	if (actual->iniciar(this, screen, fondo))
	{
		printf(_("Can't change escene\n"));
		terminar();
	}

	if (buffer)
	{
		actual->capturar_pantalla(buffer);
		transicion.define_actual(buffer);

		SDL_FreeSurface(buffer);
	}
	
	escena_anterior = escena_actual;
	reiniciar_reloj();
}

/*!
 * \brief realiza un cambio entre 2 modos de video
 */
void mundo :: cambiar_modo_video(void)
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(fondo);

	if (res == ALTA)
		res=BAJA;
	else
		res=ALTA;
	
	if (iniciar_pantalla())
	{
		printf(_("Can't change video mode\n"));
		exit(-1);
	}
		
	if (libgrafico.cambiar_modo_video())
	{
		terminar();
		return;
	}
	
	actual->reiniciar_video(screen, fondo);
	transicion.crear_superficies(screen);
}


/*!
 * \brief asigna un espacio para la pantalla y su buffer
 *
 * \return 1 en caso de error
 */
int mundo :: iniciar_pantalla(void)
{
	int flags = SDL_HWSURFACE | SDL_DOUBLEBUF;

	if (fullscreen)
		flags |= SDL_FULLSCREEN;

	if (res == ALTA)
		screen = SDL_SetVideoMode(640, 480, 16, flags);
	else
		screen = SDL_SetVideoMode(320, 240, 16, flags);

	if (screen == NULL)
	{
		printf("- error: %s\n", SDL_GetError());
		return 1;
	}

	fondo = SDL_DisplayFormat(screen);
	
	if (fondo == NULL)
	{
		printf(_("couldn't copy screen: %s\n"), SDL_GetError());
		return 1;
	}

	return 0;
}


/*!
 * \brief asigna titulo e icono a la ventana de la aplicación
 */
void mundo :: definir_ventana(void)
{
	SDL_Surface *icono;

	icono = IMG_Load(DATA_DIR "ima/icono.png");
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption("Aquatic Bubble - ver " VER, NULL);

	if (icono)
	{
		SDL_WM_SetIcon(icono, NULL);
		SDL_FreeSurface(icono);
	}
}


/*!
 * \brief alterna entre ventana y pantalla completa
 */
void mundo :: pantalla_completa(void)
{
	SDL_WM_ToggleFullScreen(screen);
	
	if (fullscreen)
		fullscreen=false;
	else
		fullscreen=true;
}

/*!
 * \brief iguala los contadores de tiempo para evitar un 'salto' de velocidad
 */
void mundo :: reiniciar_reloj(void)
{
	t=tl=tg=SDL_GetTicks();
}

/*!
 * \brief aplica la terminación del juego informada por la función terminar
 */
void mundo :: terminar_todo(void)
{
	printf(_("\nThanks for play this game\n\n"));
	libgrafico.terminar();
	
	if (actual)
		delete actual;

	SDL_FreeSurface(fondo);
	SDL_FreeSurface(screen);
	SDL_Quit();
}


/*
 * \brief inicia la escena juego
 */
void mundo :: set_juego (int players, int nivel, int cheat)
{
	juego_nivel = nivel;
	juego_cheat = cheat;
	juego_players = players;
}
