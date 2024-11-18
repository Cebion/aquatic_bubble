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

#include "libgrafico.h"
#include "int_gettext.h"


/*!
 * \brief carga todas las imagenes del juego
 *
 * \return 1 en caso de error
 */
int libgrafico :: iniciar(class dialogo *dialogo, SDL_Surface *screen, enum resolucion res)
{
	res_actual = res;
	this->dialogo = dialogo;
	this->screen = screen;
	
	if (cargar_graficos(res_actual))
		return 1;

	return 0;
}

/*!
 * \brief descarga todas las imagenes
 */
void libgrafico :: terminar(void)
{
	ima_silvio.terminar();
	ima_nivel.terminar();
	ima_burbuja.terminar();
	ima_fuente_grande.terminar();
	ima_fuente_chica.terminar();
	ima_pez.terminar();
	ima_menu.terminar();
	ima_items.terminar();
	ima_logos.terminar();
}


/*!
 * \brief carga todo los graficos respetando la resolucion
 *
 * \return 1 en caso de error
 */
int libgrafico :: cargar_graficos(enum resolucion res)
{
	cargando=true;
	
	dialogo->reiniciar(screen);
	dialogo->imprimir_titulo(screen, _("LOADING IMAGES..."));

	dialogo->reiniciar_barra(12);

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_silvio.iniciar("silvio.png", 4, 7, DOWN, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/martianc.png");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_logos.iniciar("logos.png", 2, 2, CENTER, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/logos.png");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_paco.iniciar("paco.png", 4, 7, DOWN, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/paco.png");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_nivel.iniciar("nivel.png", 8, 4, UP_LEFT, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/nivel.png");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_burbuja.iniciar("burbuja.png", 3, 5, DOWN, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/burbuja.png");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_fuente_grande.iniciar("fuente1.png", 2, 52, CENTER, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/fuente1.png");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);

	if (ima_menu.iniciar("menu.jpg", 1, 1, UP_LEFT, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/menu.jpg");
		return 1;
	}

	dialogo->imprimir_barra(screen, 1);
	
	if (ima_pez.iniciar("pez.png", 3, 5, DOWN, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/pez.png");
		return 1;
	}
	
	dialogo->imprimir_barra(screen, 1);

	if (ima_items.iniciar("items.png", 1, 2, DOWN, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/items.png");
		return 1;
	}
	
	dialogo->imprimir_barra(screen, 1);
	
	if (ima_fuente_chica.iniciar("fuente2.png", 2, 52, DOWN, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/fuente2.png");
		return 1;
	}
	
	dialogo->imprimir_barra(screen, 1);

	if (ima_particulas.iniciar("particulas.png", 2, 3, CENTER, res))
	{
		dialogo->imprimir_error(screen, DATA_DIR "ima/particulas.png");
		return 1;
	}
	
	dialogo->imprimir_barra(screen, 1);


	
	cargando=false;
	return 0;
}

/*!
 * \brief modifica los graficos a otro modo de video
 */
int libgrafico :: cambiar_modo_video(void)
{
	terminar();

	if (res_actual == ALTA)
		res_actual = BAJA;
	else
		res_actual = ALTA;

	if (cargar_graficos(res_actual))
		return 1;

	return 0;
}


/*!
 * \brief informa si sigue cargando graficos
 */
int libgrafico :: termino(void)
{
	return !cargando;
}
