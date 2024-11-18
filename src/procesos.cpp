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

#include "procesos.h"
#include "juego.h"
#include <math.h>


/*!
 *\brief constructor del objeto proceso
 */
procesos :: procesos(void)
{
}

/*!
 *\brief destructor de silvio
 */
procesos :: ~procesos()
{
}

/*!
 *\brief inicializa el objeto proceso
 */
void procesos :: iniciar(class juego *juego)
{
	this->juego = juego;
}

/*!
 *\brief crea el personaje principal silvio
 */
void procesos :: crear_silvio(class grafico *grafico, int x, int y)
{
	n_protagonistas protagonistas;
	list <n_protagonistas> :: iterator nodo;
	
	protagonistas.obj=new class silvio;
	protagonistas.jugador=0;
	lista_protagonistas.push_front(protagonistas);
	
	nodo=lista_protagonistas.begin();
	(*nodo).obj->iniciar(juego,grafico,x,y);
}


void procesos :: crear_paco(class grafico *grafico, int x, int y)
{
	n_protagonistas protagonistas;
	list <n_protagonistas> :: iterator nodo;
	
	protagonistas.obj=new class paco;
	protagonistas.jugador=1;
	lista_protagonistas.push_front(protagonistas);
	
	nodo=lista_protagonistas.begin();
	(*nodo).obj->iniciar(juego,grafico,x,y);
}

/*!
 * \brief Crea enemigos
 */
void procesos :: crear_enemigo(class grafico *grafico,int x,int y)
{
	n_enemigos enemigo;
	list <n_enemigos> :: iterator nodo;
	
	enemigo.obj=new class pez;
	lista_enemigos.push_front(enemigo);
	
	nodo=lista_enemigos.begin();
	(*nodo).obj->iniciar(juego,grafico,x,y);
}

/*!
 *\brief crea la burbuja
 */
void procesos :: crear_burbuja(int x,int y,int flip,int jugador)
{
	n_items burbuja;
	list <n_items> :: iterator nodo;
	
	burbuja.obj=new class burbuja;
	burbuja.jugador=jugador;
	
	lista_burbuja.push_front(burbuja);	
	nodo=lista_burbuja.begin();	
	(*nodo).obj->iniciar(juego,&juego->mundo->libgrafico.ima_burbuja,x,y,flip);
}

/*!
 * \brief actualiza todos los procesos
 */
void procesos :: actualizar(void)
{	
	actualizar_puntos_protagonista(lista_protagonistas);	  
	  
	actualizar_listas(lista_protagonistas);
	actualizar_listas(lista_burbuja);
	actualizar_listas(lista_enemigos);

	if(lista_enemigos.empty())
	{
		juego->nivel_completado();
//		reiniciar_protagonistas(lista_protagonistas);
	}

}

/*!
 * \brief imprime todos los procesos en la pantalla
 */
void procesos :: imprimir(SDL_Surface *screen, SDL_Rect *modif, int &lim)
{
//	static int i=0;
		  
//	if(!lista_protagonistas.empty())		 
//	{
//

	imprimir_listas(screen,modif,lim,lista_protagonistas);	
	imprimir_listas(screen,modif,lim,lista_burbuja);
	imprimir_listas(screen,modif,lim,lista_enemigos);

	
//	}
/*
	else
	{
		if (i==0)
		{
			i++;
//			juego->game_over();
		}
	}
*/
}
/*!
 */
template <class S>
void procesos :: actualizar_listas(list<S> &list_ref)
{
	typename list <S> :: iterator nodo;

	for(nodo=list_ref.begin();nodo != list_ref.end();nodo++)
	{	
		if((*nodo).obj->actualizar())
		{
			nodo=list_ref.erase(nodo);
			nodo--;
		}
	}

}

/*!
 *\brief imprime las listas.
 */
template <class S>
void procesos :: imprimir_listas(SDL_Surface *screen,SDL_Rect *modif,int &lim,list<S> &list_ref)
{
	typename list <S> :: iterator nodo;

	for(nodo=list_ref.begin();nodo != list_ref.end();nodo++,lim++)
		(*nodo).obj->imprimir(screen,&(modif[lim]));
}


/*!
 *\brief avisa si hay una colision entre enemigo, personaje, items.
 */
void procesos :: avisar_colisiones()
{
	colision_enemigo_personaje();
	colision_enemigo_burbuja();
	colision_enemigo_enemigo();
}

/*!
 *\brief obtiene la distancia entre dos puntos.
 */
float procesos :: distancia(int x1,int y1,int x2,int y2)
{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

int procesos :: hay_enemigo_cerca(int avanze,int jugador)
{
	list<n_enemigos>:: iterator nodo;
	list<n_protagonistas>::iterator prot;
	int valor;
	float delta;
	
	prot=busca_protagonista(jugador);
	//radio=14+20
	
	for(nodo=lista_enemigos.begin();nodo != lista_enemigos.end();nodo++)
	{
		if((*nodo).obj->get_estado()==4)	  
		{
			delta=distancia((*prot).obj->get_x()-6,(*prot).obj->get_y()-36,(*nodo).obj->get_x()-5,(*nodo).obj->get_y()-53);
			
			switch (avanze)
			{
				case 0://si quiere pegarle
								 
					if(delta <= 44)
					{	
						(*nodo).jugador=(*prot).jugador;
						(*nodo).obj->set_rebote(1);
						(*nodo).obj->set_flip((*prot).obj->get_flip());	
						return 1;
					}
					break;
						
				case 1://si quiero mover la burbuja

					if(delta <= (42))
					{  
						if((*nodo).obj->get_rebote() != 1)//poner esto en pez
							(*nodo).obj->set_flip((*prot).obj->get_flip());	
	
						valor=(*nodo).obj->get_flip();
					
						if(((*nodo).obj->get_x() * valor) > ((*prot).obj->get_x()*valor))
						{
							(*nodo).obj->set_encierro(0);
							(*nodo).obj->avanzar();
						}
					}
					break;
			}
		}
	}
		
	return 0;
}

void procesos:: suma_puntos(int puntaje,int jugador)
{
	list<n_protagonistas>::iterator nodo;
	
	nodo=busca_protagonista(jugador);	
	(*nodo).obj->sumar_puntos(puntaje);
}


list<n_protagonistas>::iterator procesos::busca_protagonista(int jugador)//cambiar se puede
{
	list<n_protagonistas>::iterator nodo;
	
	for(nodo=lista_protagonistas.begin();nodo!=lista_protagonistas.end();nodo++)
	{
		if((*nodo).jugador==jugador)		  
			return nodo;
	}

	return 0;
}


void procesos:: colision_enemigo_personaje(void)
{
	list <n_protagonistas> :: iterator prot;
	list <n_enemigos> :: iterator nodo;
	float delta;
	
	//radio= 14+20 
	for(nodo=lista_enemigos.begin();nodo != lista_enemigos.end();nodo++)
	{
		if((*nodo).obj->get_estado() != 4)		  
		{
			for(prot=lista_protagonistas.begin();prot!=lista_protagonistas.end();\
								 prot++)
			{
				delta=distancia((*prot).obj->get_x()-6,(*prot).obj->get_y()-36,\
									 (*nodo).obj->get_x(),(*nodo).obj->get_y()-47);
	
				if((delta <= 34) && ((*prot).obj->get_visibilidad() == 0))
					(*prot).obj->colision_con_enemigo();
			}
		}
	}
	
}

void procesos::colision_enemigo_burbuja(void)
{
	list <n_enemigos> :: iterator nodo;
	list <n_items> :: iterator nodo2;
	float delta;
	//se fija si colisiona enemigo-burbuja
   //radio=25+20 

	for(nodo=lista_enemigos.begin();nodo != lista_enemigos.end();nodo++)
	{
		for(nodo2=lista_burbuja.begin();nodo2 !=lista_burbuja.end();nodo2++)		  
		{
			delta=distancia((*nodo2).obj->get_x(),(*nodo2).obj->get_y()-32,(*nodo).obj->get_x(),(*nodo).obj->get_y()-47);
	
			if(delta <= 45)
			{
				(*nodo).obj->colision_con_burbuja();
				suma_puntos(1,(*nodo2).jugador);
				nodo2=lista_burbuja.erase(nodo2);
				nodo2--;
			}
		}
	}
}


void procesos::colision_enemigo_enemigo(void)
{
	list <n_enemigos> lista_aux;
	list <n_enemigos> :: iterator nodo;
	list <n_enemigos> :: iterator ptr;
	list <n_enemigos> :: iterator punt;
	float delta;
	
	// se fija si colisiona enemigo-enemigo
	
	for(nodo=lista_enemigos.begin();nodo != lista_enemigos.end();nodo++)
	{
		if((*nodo).obj->get_estado() == 4)
		{
			lista_aux.push_front(*nodo);
			nodo=lista_enemigos.erase(nodo);

			ptr=lista_aux.begin();
	
			for(punt=lista_enemigos.begin();punt != lista_enemigos.end();punt++)
			{
				if((*punt).obj->get_estado() == 4)//se fija si el otro esta encerrado
				{
					delta=distancia((*ptr).obj->get_x()-4,(*ptr).obj->get_y()-65,(*punt).obj->get_x()-4,(*punt).obj->get_y()-65);
					
					if(delta <= 50)
					{
						(*punt).obj->cambiar_flip();
						(*ptr).obj->cambiar_flip();
					}
				}
				else
				{
					delta=distancia((*ptr).obj->get_x()-5,(*ptr).obj->get_y()-53,(*punt).obj->get_x(),(*punt).obj->get_y()-47);
					
					if(delta<=46)
					{
						suma_puntos(1,(*ptr).jugador);
						(*punt).obj->set_estado(5);		  
					}
				}
			}	
			nodo--;
		}
	}
	
	if(!lista_aux.empty())
	for(nodo=lista_aux.begin();nodo != lista_aux.end();nodo++)
		lista_enemigos.push_front(*nodo);
	
}


int procesos :: get_puntos(int jugador)
{
	return puntos[jugador];
}

void procesos::reiniciar_protagonistas(list<n_protagonistas> lista)
{
	list<n_protagonistas> :: iterator nodo;
	
	for(nodo=lista_protagonistas.begin();nodo!=lista_protagonistas.end();nodo++)
	{
		(*nodo).obj->set_estado(8);//iniciando
		(*nodo).obj->set_x_inicial();
		(*nodo).obj->set_y_inicial();
		(*nodo).obj->set_velocidad();

	}

}
void procesos :: actualizar_puntos_protagonista(list<n_protagonistas>lista_protagonistas)
{
	int i=0;
	list<n_protagonistas> :: iterator nodo;
	
	for(nodo=lista_protagonistas.begin();nodo!=lista_protagonistas.end();\
						 nodo++,i++)
		puntos[i]=(*nodo).obj->get_puntos();
}


/*!
 * \brief obtiene la cantidad de protagonistas con vida
 */
int procesos :: get_cant_protagonistas(void)
{
	int cant=0;
	list<n_protagonistas> :: iterator nodo;
	
	
	for(nodo = lista_protagonistas.begin();\
			nodo != lista_protagonistas.end(); cant++, nodo++)
		;
	
	return cant -1;
}
