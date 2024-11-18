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

#ifndef _ENEMIGOS_H
#define _ENEMIGOS_H

#include "actor.h"

class enemigos : public actor 
{
	public:
		virtual int iniciar(class juego *juego, grafico *_grafico, int x, int y)=0;
		void imprimir(SDL_Surface *screen, SDL_Rect *rect);
		void colision_con_burbuja(void);
		void set_rebote(int r){hab_rebote=r;}
		int get_rebote(void){return hab_rebote;}
		void set_encierro(int e){encierro=e;}
		
	protected:
		int flag,pausa,colisiones,hab_rebote,encierro,cant_rebote;	
};

#endif
