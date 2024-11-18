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
#include "texto.h"
#include "int_gettext.h"

/*!
 * \brief constructor
 */
texto :: texto()
{
	lim_cadena = 0;
}


texto :: ~texto()
{
	printf("liberando cadenas\n");
	
	for (int i = 0; i < lim_cadena; i++)
		delete cadena[i];
}

/*!
 * \brief genera el texto a mostrar
 */
void texto :: crear (class grafico *letras)
{
	ima = letras;

	mensaje(_("CREDITS"));
	mensaje("");
	mensaje(_("PROGRAMING:"));
	mensaje("- HUGO RUSCITTI:");
	mensaje("- GABRIEL VALENTIN");
	mensaje("");
	mensaje(_("GRAPHICS:"));
	mensaje("- WALTER VELAZQUEZ");
	mensaje("");
	mensaje("WEB SITE:");
	mensaje("WWW.LOOSERSJUEGOS.COM.AR");
		
//	cadena[0].iniciar(ima, _("CREDITS"), ASUBE, 30, 30, 320, 510 + 50*0);
//	cadena[1].iniciar(ima, "", ASUBE, 30, 30, 320, 510 + 50*1);
//	cadena[2].iniciar(ima, _("PROGRAMING:"), ASUBE, 30, 30, 320, 510 + 50*2);
//	cadena[3].iniciar(ima, "- HUGO RUSCITTI   ", ASUBE, 30, 30, 320,\
			510 + 50*3);
//	cadena[4].iniciar(ima, "- GABRIEL VALENTIN", ASUBE, 30, 30, 320,\
			510 + 50*4);
//	cadena[5].iniciar(ima, "", ASUBE, 30, 30, 320, 510 + 50*5);
//	cadena[6].iniciar(ima, _("GRAPHICS:"), ASUBE, 30, 30, 320, 510 + 50*6);
//	cadena[7].iniciar(ima, "- WALTER VELAZQUEZ", ASUBE, 30, 30, 320,\
			510 + 50*7);
//	cadena[8].iniciar(ima, "", ASUBE, 30, 30, 320, 510 + 50*8);
//	cadena[9].iniciar(ima, "WWW.LOOSERSJUEGOS.COM.AR", ASUBE, 26, 30, 320,\
			510 + 50*9);
}

/*!
 * \brief actualización lógica
 */
void texto :: actualizar (void)
{
	for (int i = 0; i < lim_cadena; i++)
		cadena[i]->actualizar();
}


/*!
 * \brief actualización lógica
 */
void texto :: actualizar_invertido (void)
{
	for (int i = 0; i < lim_cadena; i++)
		cadena[i]->actualizar_invertido();
}


/*!
 * \brief imprime todos los objetos sobre dst
 */
void texto :: imprimir (SDL_Surface *dst, SDL_Rect *rect, int &lim)
{
	for (int i = 0; i < lim_cadena; i++)
		cadena[i]->imprimir(dst, rect, lim);
}


/*!
 * \brief Añade otro mensaje de textos a los creditos
 */
void texto :: mensaje (char *mensaje)
{

	if (lim_cadena == 100)
	{
		printf(_("lim_cadena is out of range of 0 to 100\n"));
		return;
	}
	
	cadena[lim_cadena] = new class cadena;
	
	cadena[lim_cadena]->iniciar(ima, mensaje, ASUBE, 320,\
			510 + 50*lim_cadena);
	lim_cadena++;
}
