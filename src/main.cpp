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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mundo.h"
#include "main.h"
#include "int_gettext.h"


#ifdef WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE x1, HINSTANCE x2, LPSTR x3, int x4)
#else
/*!
 * \brief funcion principal del programa
 */
int main(int argc, char *argv[])
#endif
{
//#ifdef HAVE_GETTEXT
	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
//#endif
	mundo aqbubble;
	bool fullscreen = false;
	bool sonido = true;
	bool musica = true;
	enum resolucion res = ALTA;
	int test=0;

	
	srand(time(NULL));
	
	imprimir_titulo();
	
	if (argc != 1)
		procesar_parametros(argc, argv, musica, sonido, fullscreen,\
				res, test);
	
	if (aqbubble.iniciar(fullscreen, musica, sonido, res, test))
		return 1;

	aqbubble.correr();
	aqbubble.terminar_todo();
	
	return 0;
}


/*!
 * \brief informa los parametros del programa
 */
void imprimir_ayuda(char *programa)
{
	printf(_("usage: %s [OPTIONS]\n"), programa);
	printf("\n");
	printf(_("Avariable [OPTIONS]:\n"));
	printf("\n");
	printf(_("  --help         show this message\n"));
	printf(_("  --ns           disable sound\n"));
	printf(_("  --nm           disable music\n"));
	printf(_("  --fullscreen   full screen\n"));
	printf(_("  --low          mode 320x240px\n"));
	printf(_("  --license      print license terms\n"));
	printf(_("  --test         init the game immediately\n"));
	printf(_("\n"));
}


/*!
 * \brief muestra el nombre del juego
 */
void imprimir_titulo(void)
{
	printf("\nAquatic Bubble version %s\n", VER);
	printf(_("  with '--help' display help and exit\n"));
	printf("\n");
}


/*!
 * \brief imprime los términos de uso
 */
void imprimir_licencia(void)
{
	
	printf("Copyright (C) 2003-2005 Hugo Ruscitti.\n");
	printf("\n");

	printf(_("\
    This program is free software; you can redistribute it and/or modify\n\
    it under the terms of the GNU General Public License as published by\n\
    the Free Software Foundation; either version 2 of the License, or\n\
    (at your option) any later version.\n\n"));
	
	printf(_("\
    This program is distributed in the hope that it will be useful,\n\
    but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
    GNU General Public License for more details.\n\n"));
	
	printf(_("\
    You should have received a copy of the GNU General Public License\n\
    along with this program; if not, write to the Free Software\n\
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\
    \n"));

	printf(_("contact us: \n"));
	printf("\tweb : http://www.loosersjuegos.com.ar\n");
	printf("\te-mail : hugoruscitti@yahoo.com.ar\n");
	printf("\n"); 

}

/*!
 * \brief lee las opciones del programa comando
 */
void procesar_parametros(int argc, char *argv[], bool &musica, bool &sonido, bool &fullscreen, enum resolucion &res, int &test)
{
	for (int i=1; i<argc; i++)
	{
		int valida=0;

		if (strcmp(argv[i], "--ns") == 0)
		{
			sonido = false;
			valida = 1;
		}

		if (strcmp(argv[i], "--nm") == 0)
		{
			musica = false;
			valida = 1;
		}
		
		if (strcmp(argv[i], "--fullscreen") == 0)
		{
			fullscreen = true;
			valida = 1;
		}
		
		if (strcmp(argv[i], "--low") == 0)
		{
			res = BAJA;
			valida = 1;
		}

		if (strcmp(argv[i], "--help") == 0)
		{
			imprimir_ayuda(argv[0]);
			exit(0);
		}

		if (strcmp(argv[i], "--license") == 0)
		{
			imprimir_licencia();
			exit(0);
		}

		if (strcmp(argv[i], "--test") == 0)
		{
			test = 1;
			valida = 1;
		}
		
		if (!valida)
		{
			printf(_("\ninvalid option '%s'\n\n"), argv[i]);
			exit(1);
		}

	}
}
