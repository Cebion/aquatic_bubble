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
#include "marcas.h"
#include "int_gettext.h"


/*!
 * \brief carga todos los records
 */
void marcas :: iniciar(void)
{
	if (cargar_archivo())
		cargar_por_defecto();
}

/*!
 * \brief intenta recuperar los records almacenados en un archivo
 *
 * \return 1 falla la lectura del archivo, 0 exito
 */
int marcas :: cargar_archivo(void)
{
	FILE *arch;
	char ruta[100];
	char buffer[100];
	char *p;
	int i=0;
		
	strcpy(ruta, getenv("HOME"));
	strcat(ruta, "/.aqbubble_marcas");

	arch = fopen(ruta, "rt");

	if (arch == NULL)
		return 1;

	while (fgets(buffer, 100, arch))
	{
		p = strtok(buffer, "#");
		
		if (p == NULL)
			return 1;

		strcpy(todos[i].nombre, p);

		p = strtok(NULL, "");

		if (p == NULL)
			return 1;
		
		todos[i].puntos = atoi(p);

		i++;
	}
	
	fclose(arch);
	return 0;
}

/*!
 * \brief genera records iniciales
 */
void marcas :: cargar_por_defecto(void)
{
	strcpy(todos[0].nombre, "PRIMERO");
	todos[0].puntos = 400;

	strcpy(todos[1].nombre, "SEGUNDO");
	todos[1].puntos = 350;
	
	strcpy(todos[2].nombre, "TERCERO");
	todos[2].puntos = 320;
	
	strcpy(todos[3].nombre, "CUARTO");
	todos[3].puntos = 300;

	strcpy(todos[4].nombre, "QUINTO");
	todos[4].puntos = 100;

}


/*!
 * \brief muestra todos los puntajes (temporal)
 */
void marcas :: imprimir(void)
{
	printf("tmp (marcas :: imprimir) -> RECORDS:\n");
	
	for (int i=0; i<4; i++)
	{
		printf("[%d] %s : %d puntos\n", i, todos[i].nombre, \
				todos[i].puntos);
	}

	printf("\n");
	guardar_cambios();
}


/*!
 * \brief almacena todos los cambios en un archivo
 */
void marcas :: guardar_cambios (void)
{
	FILE *arch;
	char ruta[100];

	strcpy(ruta, getenv("HOME"));
	strcat(ruta, "/.aqbubble_marcas");
	
	arch = fopen(ruta, "wt");

	if (arch == NULL)
	{
		printf(_("Can't save %s file\n"),ruta);
		return;
	}

	for (int i=0; i<4; i++)
		fprintf(arch, "%s#%i\n", todos[i].nombre, todos[i].puntos);
	
	fclose(arch);
}



/*!
 * \brief obtine el nombre de una de las marcas
 */
void marcas :: get_nombre(char *nombre, int pos)
{
	strcpy(nombre, todos[pos].nombre);
}


/*!
 * \brief obtiene el puntaje de una de las marcas
 */
void marcas :: get_puntos(char *puntos, int pos)
{
	int pts = todos[pos].puntos;

	sprintf(puntos, "%d", pts);
	/*
	puntos[0] = '0' + (pts / 1000) %10;
	puntos[1] = '0' + (pts / 100) %10;
	puntos[2] = '0' + (pts / 10) %10;
	puntos[3] = '0' + (pts / 1) %10;
	puntos[4] = '\0';
	*/
}


/*!
 * \brief muestra un record almacenado
 */
void marcas :: get_marca(char *cadena, int pos)
{
	int tam;
	int i;
	
	get_nombre(cadena, pos);
	tam = strlen(cadena);

	for (i=tam; i<10; i++)
	{
		cadena[i]= '_';
	}

	get_puntos(&cadena[i], pos);
	
}
