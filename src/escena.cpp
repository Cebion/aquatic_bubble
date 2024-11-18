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
#include "escena.h"

/*!
 * \brief genera un mensaje de texto en un vector de textos
 */
void escena :: crear_texto(class grafico *ima, class cadena* textos[], int &lim, char *nombre, int max_textos, enum tipo_anim anim)
{
	int posy = 340 - (max_textos*50)/2;

	textos[lim] = new class cadena;
	textos[lim]->iniciar(ima, nombre, anim, 320, posy+lim*50, 32, 40);
	
	lim++;
}
