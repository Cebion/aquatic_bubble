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

#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "int_gettext.h"

/*!
 * \brief destructor
 */
menu :: ~menu()
{
	for (int i=0; i < lim_opciones; i++)
		delete opciones[i];
}


/*!
 * \brief vincula el menu al mundo
 *
 * \return 1 en caso de error
 */
int menu :: iniciar(class mundo *mundo, SDL_Surface *screen, SDL_Surface *fondo)
{
	this->mundo = mundo;
	this->screen = screen;
	this->fondo = fondo;
	
	lim_opciones = 0;	
	lim_ant = 0;

	mundo->libgrafico.ima_menu.imprimir(0, fondo, NULL, 0, 0, 1);

	logo[0].iniciar(&mundo->libgrafico.ima_logos, 2, ALEFT, 160, 60);
	logo[1].iniciar(&mundo->libgrafico.ima_logos, 3, ARIGHT, 470, 60);
	
	mundo->reiniciar_reloj();
	ultima_tecla=ESCAPE;
	cambiar_estado(MPRINCIPAL);
	return 0;
}


/*!
 * \brief actualización lógica
 */
void menu :: actualizar(void)
{
	for (int i=0; i<lim_opciones; i++)
		opciones[i]->actualizar();
	
	logo[0].actualizar();
	logo[1].actualizar();
	
	// gestiona estados
	switch (estado)
	{
		case MCODIGO:
			if (longitud_codigo > 4)
				fin_ingresar_codigo();
			else
				ingresar_codigo();
			
			break;
			
		case MCONF1:
		case MCONF2:
			cambiar_teclas();
			break;

		case MCONF1GRAB:
		case MCONF2GRAB:
			confirmar_cambios();
			break;
			
		default:
			mover_cursor();
			break;
	}
	
	// verifica y acciona cada opción
	selecciona();	
}


/*!
 * \brief gestina el movimiento del cursor de opciones
 */
void menu :: mover_cursor(void)
{
	if (ultima_tecla != MDOWN && get_tecla(MDOWN))
		avanza_opcion();

	if (ultima_tecla != MUP && get_tecla(MUP))
		retrocede_opcion();

	if (ultima_tecla != PAUSA && get_tecla(PAUSA))
	{
		selecciona_opcion();
		mundo->audio.play(STIC);
		ultima_tecla = PAUSA;
	}

	if (ultima_tecla != 0)
	{
		if (!get_tecla(MUP) \
				&& !get_tecla(MDOWN) \
				&& !get_tecla(PAUSA) \
				&& !get_tecla(MDOWN))
			ultima_tecla=0;
	}
}

/*!
 * \brief actualización grafica
 */
void menu :: imprimir(void)
{
	int i;
	
	lim_actual = 0;
	
	logo[0].imprimir(screen, rect_actual, lim_actual);
	logo[1].imprimir(screen, rect_actual, lim_actual);
	
	for (i=0; i<lim_opciones; i++)
		opciones[i]->imprimir(screen, rect_actual, lim_actual);
		
	lim_todos = 0;

	for (i=0; i<lim_actual; i++, lim_todos++)
		todos[lim_todos] = rect_actual[i];

	for (i=0; i<lim_ant; i++, lim_todos++)
		todos[lim_todos] = rect_ant[i];

	SDL_UpdateRects(screen, lim_todos, todos);

	for (i=0; i<lim_actual; i++)
		SDL_BlitSurface(fondo, &(rect_actual[i]), screen, &(rect_actual[i]));
	
	for (i=0; i<lim_actual; i++)
		rect_ant[i] = rect_actual[i];

	lim_ant = lim_actual;
}


/*!
 * \brief es llamada cuando se altera la resolución de video
 */
void menu :: reiniciar_video(SDL_Surface *screen, SDL_Surface *fondo)
{
	this->screen = screen;
	this->fondo = fondo;
	lim_ant=0;

	limpiar_pantalla();
	mundo->reiniciar_reloj();
}


/*!
 * \brief pinta toda la pantalla
 */
void menu :: limpiar_pantalla(void)
{
	mundo->libgrafico.ima_menu.imprimir(0, fondo, NULL, 0, 0, 1);
	SDL_BlitSurface(fondo, NULL, screen, NULL);
	SDL_Flip(screen);
}


/*!
 * \brief aplica el cambio de estados y genera las opciones
 */
void menu :: cambiar_estado(enum menu_estado nuevo)
{
	estado = nuevo;

	for (int i=0; i < lim_opciones; i++)
		delete opciones[i];

	lim_opciones=0;

	switch (nuevo)
	{
		case MCODIGO:
			longitud_codigo = 0;
			crear_titulo(_("ENTER PASSWORD:"));
			crear_titulo("-----");
			break;
			
		case MPRINCIPAL:
			crear_titulo(_("NEW GAME"));
			crear_titulo(_("OPTIONS"));
			crear_titulo(_("CREDITS"));
			crear_titulo(_("RECORDS"));
			crear_titulo(_("QUIT"));
			break;

		case MOPCIONES:
			crear_titulo(_("AUDIO"));
			crear_titulo(_("VIDEO"));
			crear_titulo(_("CONTROLS"));
			crear_titulo(_("RETURN"));
			break;

		case MJUEGO:
			crear_titulo(_("ONE PLAYER"));
			crear_titulo(_("TWO PLAYERS"));
			crear_titulo(_("ENTER PASSWORD"));
			crear_titulo(_("RETURN"));
			break;

		case MCONTROLES:
			crear_titulo(_("CHANGE PL1 KEYS"));
			crear_titulo(_("CHANGE PL2 KEYS"));
			crear_titulo(_("RETURN"));
			break;

		case MAUDIO:
			crear_titulo(_("SOUND >"));
			crear_titulo(_("MUSIC >"));
			crear_titulo(_("RETURN"));

			if (mundo->audio.get_sonido())
				opciones[0]->tildar();
			else
				opciones[0]->destildar();

			if (mundo->audio.get_musica())
				opciones[1]->tildar();
			else
				opciones[1]->destildar();
			
			break;

		case MVIDEO:
			crear_titulo(_("FULL SCREEN >"));
			crear_titulo(_("REDUCED MODE >"));
			crear_titulo(_("RETURN"));

			if (mundo->get_fullscreen())
				opciones[0]->tildar();
			else
				opciones[0]->destildar();

			if (mundo->get_res() == BAJA)
				opciones[1]->tildar();
			else
				opciones[1]->destildar();
			
			break;

		case MCONF1:
		case MCONF2:
			mundo->perifericos.reiniciar();
			crear_titulo(_("LEFT : ------"));
			crear_titulo(_("RIGHT: ------"));
			crear_titulo(_("JUMP : ------"));
			crear_titulo(_("FIRE : ------"));
			break;

		case MCONF1GRAB:
		case MCONF2GRAB:
			break;
	}

	opcion = 0;
	opciones[0]->activar();
}


/*!
 * \brief ejecuta la accion seleccionada
 */
void menu :: selecciona_opcion(void)
{
	switch (estado)
	{
		case MPRINCIPAL:
			selecciona_en_principal();
			break;

		case MJUEGO:
			selecciona_en_juego();
			break;

		case MOPCIONES:
			selecciona_en_opciones();
			break;

		case MVIDEO:
			selecciona_en_video();
			break;

		case MAUDIO:
			selecciona_en_audio();
			break;

		case MCONTROLES:
			selecciona_en_controles();
			break;

		default:
			printf(_("invalid option in function %s\n"), \
						"menu :: selecciona_opcion");
			break;
	}
}


/*!
 * \brief se seleeciona una opcion del menu principal
 */
void menu :: selecciona_en_principal(void)
{
	switch (opcion)
	{
		case 0:
			cambiar_estado(MJUEGO);
			break;

		case 1:
			cambiar_estado(MOPCIONES);
			break;
	
		case 2:
			mundo->cambiar_escena(CREDITOS);
			break;
	
		case 3:
			mundo->cambiar_escena(RECORDS);
			break;
			
		case 4:
			mundo->terminar();
			break;
	}
}


/*!
 * \brief se seleeciona una opcion del menu de opciones
 */
void menu :: selecciona_en_opciones(void)
{
	switch (opcion)
	{
		case 0:
			cambiar_estado(MAUDIO);
			break;

		case 1:
			cambiar_estado(MVIDEO);
			break;

		case 2:
			cambiar_estado(MCONTROLES);
			break;

		case 3:
			cambiar_estado(MPRINCIPAL);
			break;
			
	}
}

/*!
 * \brief selecciona una opcion dentro del menu 'nuevo juego'
 */
void menu :: selecciona_en_juego(void)
{
	switch (opcion)
	{
		case 0:
			mundo->cambiar_escena(JUEGO);
			mundo->set_juego(1, 1, 0);
			break;
			
		case 1:
			mundo->cambiar_escena(JUEGO);
			mundo->set_juego(2, 1, 0);
			break;
		
		case 2:
			cambiar_estado(MCODIGO);
			break;
			
		case 3:
			cambiar_estado(MPRINCIPAL);
			break;
	}
}


/*!
 * \brief selecciona una nueva opcion dentro del menu 'video'
 */
void menu :: selecciona_en_video(void)
{
	switch (opcion)
	{
		case 0:
			mundo->pantalla_completa();

			if (mundo->get_fullscreen())
				opciones[0]->tildar();
			else
				opciones[0]->destildar();
			break;

		case 1:
			mundo->cambiar_modo_video();
			
			if (mundo->get_res() == BAJA)
				opciones[1]->tildar();
			else
				opciones[1]->destildar();
			break;

			
		case 2:
			cambiar_estado(MOPCIONES);
			break;
	}
}


/*!
 * \brief selecciona una nueva opcion dentro del menu 'audio'
 */
void menu :: selecciona_en_audio(void)
{
	switch (opcion)
	{
		case 0:
			mundo->audio.cambiar_sonido();
			
			if (mundo->audio.get_sonido())
				opciones[0]->tildar();
			else
				opciones[0]->destildar();
			
			break;
			
		case 1:
			mundo->audio.cambiar_musica();
		
			if (mundo->audio.get_musica())
				opciones[4]->tildar();
			else
				opciones[4]->destildar();
			break;
		
		case 2:
			cambiar_estado(MOPCIONES);
			break;
	}
}


/*!
 * \brief selecciona una nueva opcion dentro del menu 'controles'
 */
void menu :: selecciona_en_controles(void)
{
	switch (opcion)
	{
		case 0:
			cambiar_estado(MCONF1);
			break;
			
		case 1:
			cambiar_estado(MCONF2);
			break;
		
		case 2:
			cambiar_estado(MOPCIONES);
			break;
	}
}


/*!
 * \brief obtiene una imagen de la escena para realizar la transicion
 */
void menu :: capturar_pantalla(SDL_Surface *pantalla)
{
	lim_actual=0;

	mundo->libgrafico.ima_menu.imprimir(0, pantalla, NULL, 0, 0, 1);
	
	logo[0].imprimir(pantalla, rect_actual, lim_actual);
	logo[1].imprimir(pantalla, rect_actual, lim_actual);
	
	for (int i=0; i<lim_opciones; i++)
		opciones[i]->imprimir(pantalla, rect_actual, lim_actual);
	
	lim_actual=0;
}


/*!
 * \brief avanza hacia la siguiente opcion
 */
void menu :: avanza_opcion(void)
{
	opciones[opcion]->desactivar();

	if (opcion >= lim_opciones-1)
		opcion = 0;
	else
		opcion++;

	opciones[opcion]->activar();
	ultima_tecla = MDOWN;
	mundo->audio.play(STOC);
}


/*!
 * \brief retrocede a la opcion anterior
 */
void menu :: retrocede_opcion(void)
{
	opciones[opcion]->desactivar();

	if (opcion == 0)
		opcion = lim_opciones-1;
	else
		opcion--;

	opciones[opcion]->activar();
	ultima_tecla = MUP;
	mundo->audio.play(STOC);
}

/*!
 * \brief genera una opcion mas al menú
 *
 * \param titulo indice con el titulo de la opcion (ver obj idioma)
 * \param 1 la opcion tiene una marca, 0 sin marca
 */
void menu :: crear_titulo(char *titulo)
{
	class grafico *ima = &mundo->libgrafico.ima_fuente_grande;
	enum tipo_anim anim;

	if (lim_opciones%2 == 0)
		anim=AUPLEFT;
	else
		anim=AUPRIGHT;

	crear_texto(ima, opciones, lim_opciones, titulo, 5, anim);
}


/*!
 * \brief cambia el texto de todas las opciones para el nuevo idioma
 */
void menu :: cambiar_idioma(void)
{
	/*
	char tmp[50];

	mundo->idioma.obtener(tmp, 4);
	opciones[0]->cambiar_texto(tmp);

	mundo->idioma.obtener(tmp, 15);
	opciones[1]->cambiar_texto(tmp);

	mundo->idioma.obtener(tmp, 14);
	opciones[2]->cambiar_texto(tmp);

	mundo->idioma.obtener(tmp, 16);
	opciones[3]->cambiar_texto(tmp);

	mundo->idioma.obtener(tmp, 9);
	opciones[4]->cambiar_texto(tmp);
	*/
}


/*!
 * \brief informa cual fué la tecla pulsada
 */
int menu :: get_tecla(int tecla)
{
	return mundo->perifericos.get_tecla(tecla);
}


/*!
 * \brief almacena las teclas que debe cambiar
 */
void menu :: cambiar_teclas(void)
{
	SDLKey tecla;

	tecla = mundo->perifericos.get_SDLK(c_ultima_tecla);
	
	if (tecla)
	{
		// evita teclas duplicadas
		for (int j=0; j<opcion; j++)
		{
			if (teclas_cambiadas[j] == tecla)
				return;
		}

		teclas_cambiadas[opcion] = tecla;
		opciones[opcion]->cambiar_guiones(c_ultima_tecla);

		if (opcion == lim_opciones-1)
		{
			crear_titulo(_("THIS IS CORRECT ?"));
			avanza_opcion();

			if (estado == MCONF1)
				estado = MCONF1GRAB;
			else
				estado = MCONF2GRAB;
		}
		else
			avanza_opcion();
	}
}


/*!
 * \brief determina si se deben guardar o no los cambios de teclas
 */
void menu :: confirmar_cambios(void)
{
	if (mundo->perifericos.acepta())
	{

		if (estado == MCONF1GRAB)
		{
			mundo->perifericos.set_tecla(P1LEFT, \
					teclas_cambiadas[0]);
			mundo->perifericos.set_tecla(P1RIGHT, \
					teclas_cambiadas[1]);
			mundo->perifericos.set_tecla(P1UP, \
					teclas_cambiadas[2]);
			mundo->perifericos.set_tecla(P1FIRE, \
					teclas_cambiadas[3]);
		}
		else
		{
			mundo->perifericos.set_tecla(P2LEFT, \
					teclas_cambiadas[0]);
			mundo->perifericos.set_tecla(P2RIGHT, \
					teclas_cambiadas[1]);
			mundo->perifericos.set_tecla(P2UP, \
					teclas_cambiadas[2]);
			mundo->perifericos.set_tecla(P2FIRE, \
					teclas_cambiadas[3]);
		}

//		mundo->perifericos.set_tecla();

//		for (int i=0; i<4; i++)
//			printf("\t %d\n", teclas_cambiadas[i]);
	
		cambiar_estado(MCONTROLES);
	}

	if (mundo->perifericos.rechaza())
		cambiar_estado(MCONTROLES);
}


/*!
 * \brief verifica y/o acciona una opcion
 */
void menu :: selecciona(void)
{
	if (ultima_tecla != SDLK_ESCAPE && mundo->perifericos.get_tecla(ESCAPE))
	{
		switch (estado)
		{
			case MCONTROLES:
			case MAUDIO:
			case MVIDEO:
				cambiar_estado(MOPCIONES);
				break;
				
			case MPRINCIPAL:
				break;

			case MCONF1:
			case MCONF2:
			case MCONF1GRAB:
			case MCONF2GRAB:
				cambiar_estado(MCONTROLES);
				break;

			case MCODIGO:
				cambiar_estado(MJUEGO);
				break;
				
			default:
				cambiar_estado(MPRINCIPAL);
		}
		
		ultima_tecla = ESCAPE;
	}
}


/*!
 * \brief lee un codigo ingresado por el usuario
 */
void menu :: ingresar_codigo(void)
{
	Uint8 tecla;
	char cadena[10]="";
	
	if (opcion == 0)
		avanza_opcion();

	tecla = mundo->perifericos.get_SDLK(cadena);

	if (tecla != 0 && ultima_tecla != tecla)
	{
		ultima_tecla = tecla;
		
		if (tecla >= SDLK_a && tecla <= SDLK_z)
		{
			longitud_codigo ++;
			opciones[1]->agregar_letra(tecla + 'A' - 'a');
		}

		if (longitud_codigo > 4)
		{
			if (verificar_codigo())
				crear_titulo(_("OK, PRESS FIRE"));
			else
				crear_titulo(_("INVALID PASSWORD"));

			longitud_codigo = 5;
		}

	}
}


/*!
 * \brief espera a que el usuario acepte la respuesta del ingreso de password
 */
void menu :: fin_ingresar_codigo(void)
{
	if (mundo->perifericos.get_tecla(PAUSA))
	{
		ultima_tecla = PAUSA;
		
		if (verificar_codigo())
			iniciar_juego_desde_codigo();
		else
			cambiar_estado(MJUEGO);
	}
}


/*!
 * \brief determina si el password es correcto
 *
 * \brief return 1 si es correcto
 */
int menu :: verificar_codigo(void)
{
	char password[6];
	char codigos[][6] = {{"PASAR"}};
	int i;

	opciones[1]->get_texto(password);

	for (i = 0; i < 1; i++)
	{
		if (strcmp(password, codigos[i]) == 0)
			return 1;
	}
	
	return 0;
}


/*!
 * \brief decodifica el password o contraseña e inicia el juego
 */
void menu :: iniciar_juego_desde_codigo(void)
{
	mundo->cambiar_escena(JUEGO);
	mundo->set_juego(2, 10, 0);
}
