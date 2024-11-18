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
#include "juego.h"
#include "int_gettext.h"

/*!
 * \brief vincula juego al mundo
 */
int juego :: iniciar(class mundo *mundo,SDL_Surface *screen,SDL_Surface *fondo)
{
	
	this->screen=screen;
	this->fondo=fondo;
	this->mundo=mundo;

	transicion.crear_superficies(screen);

	barra.iniciar(this, &mundo->libgrafico.ima_fuente_chica,\
			&mundo->libgrafico.ima_items);
	procesos.iniciar(this);

	procesos.crear_silvio(&mundo->libgrafico.ima_silvio, -30, 440);

	if (mundo->get_juego_players()==2)
		procesos.crear_paco(&mundo->libgrafico.ima_paco, 670, 440);

///	mundo->get_juego_cheat());

	procesos.crear_enemigo(&mundo->libgrafico.ima_pez,400,100);
	
	nivel.iniciar(&mundo->libgrafico.ima_nivel);
	nivel.saltar_nivel( mundo->get_juego_nivel() );
	
	lim_actual=0;
	lim_ant=0;
	lim_todos=0;

	nivel.imprimir(fondo);
	
	cadena.iniciar(&mundo->libgrafico.ima_fuente_grande, "", ASALIDA);
	imprimir_numero_nivel();

	cambiar_estado(J_INICIANDO);
	return 0;
}


/*!
 * \brief actualización lógica
 */
void juego :: actualizar(void)
{
	switch (estado)
	{
		case J_INICIANDO:
			cadena.actualizar();
//			procesos.actualizar();
			
			if (!cadena.get_visible())
				cambiar_estado(J_JUGANDO);
			break;
			
		case J_JUGANDO:
			procesos.actualizar();
			procesos.avisar_colisiones();

			if (mundo->perifericos.get_tecla(ESCAPE))
				game_over();
		
			if (mundo->perifericos.get_tecla(PAUSA))
			{
				cadena.reiniciar(_("PAUSE"), AUPLEFT);
				cambiar_estado(J_PAUSA);
			}
				
			barra.actualizar();
			break;

		case J_JUEGO_PERDIDO:
			cadena.actualizar();

			if (cadena.get_detenido())
			{
				if (mundo->perifericos.get_tecla(PAUSA) || \
					mundo->perifericos.get_tecla(ESCAPE)||\
					delay == 0)
					mundo->cambiar_escena(MENU);
				else
					delay--;
			}

			break;
			
		case J_CAMBIANDO_NIVEL:
			if (transicion.termino())
				cambiar_estado(J_INICIANDO);
			else
				transicion.actualizar();
			
			break;

		case J_PAUSA:
			if (!cadena.get_detenido())
				cadena.actualizar();
			else
			{
				if (mundo->perifericos.get_tecla(PAUSA) || \
					mundo->perifericos.get_tecla(ESCAPE))
				{
					cambiar_estado(J_PAUSA_SALE);
					cadena.reiniciar(_("PAUSA"), AQUITAR);
				}
			}
			
			break;

		case J_PAUSA_SALE:
		
			if (!cadena.get_visible())
				cambiar_estado(J_JUGANDO);
			else
				cadena.actualizar();
			
			break;

		case J_NIVEL_COMPLETADO:
			if (!cadena.get_detenido())
				cadena.actualizar();
			else
			{
				if (delay == 0 || mundo->perifericos.get_tecla(PAUSA))
					pasar_nivel();
				else
					delay--;
			}

			break;
			
		default:
			printf(_("Invalid state in function %s\n"), \
					"juego :: actualizar");
			break;
	}
}


/*!
 * \brief Realiza la impresion en pantalla
 */
void juego :: imprimir(void)
{
	int i;

	if (estado == J_CAMBIANDO_NIVEL)
	{
		transicion.imprimir();
		return;
	}
	
	lim_actual=0;

	procesos.imprimir(screen, rect_actual, lim_actual);
	barra.imprimir(screen, rect_actual, lim_actual);
	cadena.imprimir(screen, rect_actual, lim_actual);

	lim_todos=0;

	for (i=0; i<lim_actual; i++)
	{
		todos[i] = rect_actual[i];
		lim_todos++;
	}
	
	for (i=0; i<lim_ant; i++)
	{
		todos[lim_todos] = rect_ant[i];
		lim_todos++;
	}
	
	SDL_UpdateRects(screen, lim_todos, todos);

	// restaura el fondo
	for (i=0; i<lim_actual; i++)
	{
		SDL_BlitSurface(fondo, &(rect_actual[i]), screen, \
				&(rect_actual[i]));
	}

	// pasa los 'actuales' como 'anteriores'
	lim_ant=0;
	
	for (i=0; i<lim_actual; i++)
	{
		rect_ant[i] = rect_actual[i];
		lim_ant++;
	}
}

/*!
 * \brief llamada si se cambió el modo de video
 */
void juego :: reiniciar_video(SDL_Surface *screen, SDL_Surface *fondo)
{
	this->screen = screen;
	this->fondo = fondo;
	lim_actual=0;
	lim_ant=0;
	lim_todos=0;
	nivel.imprimir(fondo);
	SDL_BlitSurface(fondo, NULL, screen, NULL);
	SDL_Flip(screen);
}


/*!
 * \brief obtiene una imagen de la escena para realizar la transicion
 */
void juego :: capturar_pantalla(SDL_Surface *pantalla)
{
	lim_actual=0;
	nivel.imprimir(pantalla);
	procesos.imprimir(pantalla, rect_actual, lim_actual);
	lim_actual=0;
}


/*!
 * \brief se eliminaron todos los enemigos
 */
void juego :: pasar_nivel(void)
{
	capturar_pantalla(fondo);
	transicion.define_anterior(fondo);
	
	if (nivel.avanzar_nivel(&procesos))
	{
		printf(_("Can't pass to next level\n"));
		// ir a la escena final
	}
	else
	{
		imprimir_numero_nivel();

		nivel.imprimir(fondo);
		SDL_BlitSurface(fondo, NULL, screen, NULL);
		procesos.imprimir(screen, rect_actual, lim_actual);
		
		transicion.define_actual(screen);
		transicion.reiniciar(DESDEARRIBA);
		mundo->reiniciar_reloj();

		procesos.crear_enemigo(&mundo->libgrafico.ima_pez,400,100);
		cambiar_estado(J_CAMBIANDO_NIVEL);

	}
}


/*!
 * \brief altera el estado actual del juego
 */
void juego :: cambiar_estado(enum juego_estado nuevo)
{
	estado = nuevo;
}


/*!
 * \brief termina el juego, ambos personajes perdieron
 */
void juego :: game_over(void)
{
	cadena.reiniciar(_("GAME OVER"), AUPLEFT);
	delay = 200;
	cambiar_estado(J_JUEGO_PERDIDO);
}


/*!
 * \brief uno de los personajes perdio todas sus vidas
 */
void juego :: mensaje(int jugador, enum mensajes mensaje)
{
	switch (mensaje)
	{
		case MSIN_CREDITOS:

			if (procesos.get_cant_protagonistas() == 0)
			{
				barra.mensaje_game_over(jugador);
				game_over();
				printf("tmp-juego: termino el juego (perdieron todos)\n");
			}
			else
			{
				barra.mensaje_game_over(jugador);
				printf("tmp-juego: perdió un jugador\n");
			}
			break;


		case MPUEDE_CONTINUAR:
			barra.mensaje_continuar(jugador);
			printf("tmp-juego: perdió el jugador %d, le quedan creditos\n" , jugador);
			break;
	}
}


/*!
 * \brief imprimir el texto "nivel ##" con movimiento
 */
void juego :: imprimir_numero_nivel()
{
	char texto_nivel[30];
	char cadena_nivel[3];

	cadena_nivel[0] = '0' + nivel.get_nivel_actual()/10;
	cadena_nivel[1] = '0' + nivel.get_nivel_actual()%10;
	cadena_nivel[2] = '\0';

	strcpy(texto_nivel, _("LEVEL "));
	strcat(texto_nivel, cadena_nivel);

	cadena.reiniciar(texto_nivel, ASALIDA);
}



/*!
 * \brief imprime el mensaje de nivel completado
 */
void juego :: nivel_completado (void)
{
	cadena.reiniciar(_("LEVEL COMPLETE"), AUPLEFT);
	delay = 200;
	cambiar_estado(J_NIVEL_COMPLETADO);
}
