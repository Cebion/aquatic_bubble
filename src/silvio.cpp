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

#include "silvio.h"
#include "juego.h"

enum {PARADO, CAMINA, CORRE, DISPARA, DISPARA_CORRIENDO, SALTA, DISPARA_SALTANDO, MUERE,INICIANDO,ESPERA};


/*!
 * \brief inicializa las variables del personaje principal.
 */
int silvio :: iniciar(class juego *juego,class grafico *graficos, int x, int y)
{
	ima = graficos;
	this->juego = juego;
	this->x=x;
	this->y=y;
	this->w=graficos->get_w();
	this->h=graficos->get_h();
	velocidad=-20;
	x_inicial=x;
	y_inicial=y;
	hab_intermitente=0;
	intermitente=0;
	paso=0;
	esperando=0;
	flip=1;
	cont_delay=0;
	jugador=0;
	puede_disparar=0;

	puntos=0;
	continuar=1;
	vidas=1;

	this->juego->barra.set_puntos(0, puntos);
	this->juego->barra.set_vidas(0, vidas);

	cargar_animacion(animaciones[PARADO], "0,7,8,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
	cargar_animacion(animaciones[CORRE],"1,2");
	cargar_animacion(animaciones[SALTA],"9");
	cargar_animacion(animaciones[DISPARA],"3,4");
	cargar_animacion(animaciones[MUERE],"12");
	cargar_animacion(animaciones[ESPERA],"13");
	cargar_animacion(animaciones[INICIANDO],"9");


	
	/*
	 *
	 * 	 
	   cambio - 14/03/05
	   
	cargar_animacion(animaciones[PARADO], "0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
	cargar_animacion(animaciones[CORRE],"4,3,4");
	cargar_animacion(animaciones[SALTA],"13");
	cargar_animacion(animaciones[DISPARA],"7,8,9");
	cargar_animacion(animaciones[MUERE],"6");
	cargar_animacion(animaciones[ESPERA],"17");	
	cargar_animacion(animaciones[INICIANDO],"13");
	*/
	
	estado=INICIANDO;

	return 0;
}

/*!
 * \brief gestiona los estado de silvio.
 */
int silvio :: actualizar(void)
{
	actualizar_tecla();
	
	juego->barra.set_puntos(0,puntos);

	switch (estado)
	{
		case PARADO:
			normal();
		break;

		case CAMINA:
			caminar();
		break;

		case CORRE:
			correr();
		break;
		
		case SALTA:
			saltar();
		break;

		case DISPARA:
			disparar();
		break;
		
		case INICIANDO:
			iniciando();
		break;

		case ESPERA:
			if(esperar())
				return 1;
		break;
		
		case MUERE:
			if(terminar())
				return 1;
		break;				
	}

	puede_disparar--;
	intermitente--;
	
	if(intermitente==0)
		hab_intermitente=0;
	
return 0;
}

/*!
 * \brief gestiona el estado parado de silvio.
 */
void silvio :: normal(void)
{	
	if (pide_tecla(P1LEFT))		  
	{
		flip=-1;		
		reiniciar_animacion();
		estado=CORRE;
		return;
	}

	if (pide_tecla(P1RIGHT))
	{
		flip=1;
		reiniciar_animacion();
		estado=CORRE;
		return;
	}
	
	if (pide_tecla(P1UP))
	{
		reiniciar_animacion();
		estado=SALTA;
		velocidad=-30;
		return;
	}

	if(pide_tecla(P1FIRE) && puede_disparar < 10)
	{
		if(!enemigo_cerca(0,0))
		{
			puede_disparar=71;
			reiniciar_animacion();
			estado=DISPARA;
			juego->procesos.crear_burbuja(x+flip*10,y+6,flip,0);
		return;
		}		
	}
	
	avanzar_animacion();
}


/*!
 * \brief gestiona el estado de salto de silvio.
 */
void silvio :: saltar(void)
{	
	int dist;
	
	velocidad++;

	if(pide_tecla(P1LEFT))
	{
		flip=-1;
		x-=2;		
	}
	if(pide_tecla(P1RIGHT))
	{
		flip=1;
		x+=2;
	}

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
	
	no_avanzar();			  
	avanzar_animacion();
}

/*!
 * \brief gestiona el estado camimando de silvio.
 */
void silvio :: caminar(void)
{
}

/*!
 * \brief gestiona el estado corriendo de silvio.
 */
void silvio :: correr(void)
{
	
	if(juego->nivel.get_dist_suelo(x,y-8,8) < 8)
		y-=8;

	avanzar();
	enemigo_cerca(1,0);
	
	if((flip==-1 && !pide_tecla(P1LEFT)) || (flip==1 && !pide_tecla(P1RIGHT)))
	{
		reiniciar_animacion();
		estado=PARADO;
	}
	
	if(pisa_suelo())
	{
		y+=juego->nivel.get_dist_suelo(x,y,3);
	}
	else
	{
		reiniciar_animacion();
		velocidad=0;
		estado=SALTA;
	}
	
	if(pide_tecla(P1UP))
	{
		velocidad=-30;
		reiniciar_animacion();
		estado=SALTA;
		return;
	}

	avanzar_animacion();
	
	if(juego->nivel.get_dist_pared(x,y-14,20*flip) == (20*flip))
			return;
	
	no_avanzar();			  
}

/*!
 *\brief gestiona el estado disparando de silvio.
 */
void silvio :: disparar(void)
{	
		  
	if(avanzar_animacion())
	{
		reiniciar_animacion();
		estado=PARADO;
		return;
	}
	
}

/*!
 * \brief gestiona el estado del salto inicial, al comenzar el nivel
 */
void silvio :: iniciando(void)
{	
	int dist;
	
	velocidad++;
	flip=1;

	
//	x+=2;
	x+=flip*2;
	
	if(velocidad > 0)
	{
		dist = juego->nivel.get_dist_suelo(x,y,velocidad >> 3);
		y+=dist;
			
		if(dist < velocidad >>3)
		{
			reiniciar_animacion();
			estado=PARADO;
		}
	}
	else
		y+=velocidad >> 3;
/*
	if(juego->nivel.get_dist_pared(x,y-14,20*flip) == (20*flip))
			return;
	
//	no_avanzar();			  */
	avanzar_animacion();
}

int silvio::esperar(void)
{
	esperando++;
	if(pide_tecla(P1FIRE))
	{
		vidas=3;
		continuar--;
		juego->barra.set_vidas(jugador, vidas);
		esperando=0;
		velocidad=-20;
		x=x_inicial;
		y=y_inicial;
		estado=INICIANDO;
	}
	else
	{
		if(esperando == 800)
		{
			juego->mensaje(jugador, MSIN_CREDITOS);
			return 1;
		}
	}

return 0;
}
