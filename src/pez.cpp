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

#include "pez.h"
#include "juego.h"

enum {PARADO, CAMINA, CORRE, SALTA, ENCERRADO, MUERE, COLISION};


/*!
 * \brief inicializa las variables del enemigo.
 */
int pez :: iniciar(class juego *juego,class grafico *graficos, int x, int y)
{
	ima = graficos;
	this->juego = juego;
	this->x=x;
	this->y=y;
	this->w=graficos->get_w();
	this->h=graficos->get_h();
	velocidad=0;
	colisiones=0;
	encierro=0;
	hab_rebote=0;
	paso=0;
	pausa=0;
	cant_rebote=0;
	flag=0;
	cont_delay=0;
	flip=1;

	cargar_animacion(animaciones[PARADO],"0,1,2");
	cargar_animacion(animaciones[COLISION],"7,8,7,9,7,10,7,11");
	cargar_animacion(animaciones[ENCERRADO],"3,4,5,4");
	cargar_animacion(animaciones[MUERE],"7,14,7,14");
	
	cargar_animacion(animaciones[SALTA],"0");
	cargar_animacion(animaciones[CAMINA],"0");
	cargar_animacion(animaciones[CORRE],"0");

	estado=PARADO;
	
	if(!pisa_suelo())
		estado=SALTA;
	
	return 0;
}


/*!
 * \brief gestiona los estado de pez.
 */
int pez :: actualizar(void)
{
	
	switch (estado)
	{
		case PARADO:
			normal();
		break;

		case CAMINA:
			caminar();
		break;

		case ENCERRADO:
			encerrado();
		break;

		case COLISION:
			colision();
		break;
		
		case SALTA:
			saltar();
		break;

		case MUERE:
			if(morir())
				return 1;
		break;	
		
		default:
			terminar();
	}

	return 0;
}

/*!
 * \brief gestiona el estado parado de pez.
 */
void pez :: normal(void)
{
		
	if (flag <= 100)
	{
		if(flip == 1)
			x+=1;
		else
			x-=1;
		
	flag++;
	}
	else
	{
		flag=0;
		flip*=-1;
	}


	if(!pisa_suelo())
	{
		reiniciar_animacion();
		estado=SALTA;
	}
	
	avanzar_animacion();		  
}



/*!
 * \brief gestiona el estado de salto de pez.
 */
void pez :: saltar(void)
{
	int dist;
	
	velocidad++;

	if(velocidad > 0)
	{
		dist =juego->nivel.get_dist_suelo(x,y,velocidad >> 3);
		y+=dist;
			
		if(dist < velocidad >>3)
		{
			reiniciar_animacion();
			estado=PARADO;
		}
	}
	else
		y+=velocidad >> 3;

	if(juego->nivel.get_dist_pared(x,y-14,20*flip) == (20*flip))
			return;
	
	//no avanza
	no_avanzar();			  
}

/*!
 * \brief gestiona el estado camimando de pez.
 */
void pez :: caminar(void)
{
	avanzar_animacion();
}

/*!
 * \brief gestiona el estado corriendo de pez.
 */
void pez :: correr(void)
{
	avanzar_animacion();
}

/*!
 *\brief gestiona el estado muerto de pez.
 */
int pez :: morir(void)
{
	if(avanzar_animacion())
		  return 1;
	else
		return 0;
}

int pez:: terminar(void)
{
}
void pez :: encerrado(void)
{	
	avanzar_animacion();
	encierro++;

	if(encierro==400)
	{
		reiniciar_animacion();
		estado=PARADO;
	//	y-=16;
		encierro=0;
		return;
	}
	
	if(hab_rebote==0)//cuando estoy encerrado y me esta moviendo el protagonista
	{
		if(juego->nivel.get_dist_suelo(x,y-15,7) > 6)
			buscar_piso();
		
		if(juego->nivel.get_dist_pared(x,y-15,20*flip) == (20*flip))
			return;
		
		no_avanzar();
	}
	
	if(hab_rebote == 1)
	{	
		encierro=0;
		
		if(flip==1)
			x+=4;
		else
			x-=4;
		
		if(juego->nivel.get_dist_suelo(x,y-15,7) > 6)
			buscar_piso();
		
		if(juego->nivel.get_dist_pared(x,y-15,20*flip) == (20*flip))
			return;

		cant_rebote++;
		
		if(cant_rebote==3)
				  estado=MUERE;

		if(flip==1)
			x-=4;
		else
			x+=4;
		
		flip*=-1;

		return;
	}
	
}

void pez :: colision(void)
{
		  
	if (avanzar_animacion())
	{
		estado=ENCERRADO;
//		y+=100;
		velocidad=-1;
		reiniciar_animacion();
		encierro=0;
		return;
	}
	

	if(paso == (colisiones+1))
	{
		pausa++;	
		if( pausa < 240)		  
		{
			cont_delay=0;
			return;
		}	
		paso-=2;
		colisiones-=2;
	}
	
	if(paso==-1)
	{
		reiniciar_animacion();
		estado=PARADO;
	}
	
}

void pez :: buscar_piso(void)
{
	int dist;

	velocidad++;

	if(velocidad > 0)
	{
		dist =juego->nivel.get_dist_suelo(x,y-15,velocidad >> 2);
		y+=dist+5;
		
		if(dist < velocidad >>2)
		{
			velocidad=-1;
			return;
		}
	}
	else
		y+=velocidad >> 2;
	
}
