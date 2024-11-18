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

#ifndef _ENUM_H
#define _ENUM_H

/// estados del juego
enum juego_estado {J_INICIANDO, J_JUGANDO, J_JUEGO_PERDIDO, J_CONTINUAR, \
	J_CAMBIANDO_NIVEL, J_PAUSA, J_PAUSA_SALE, J_NIVEL_COMPLETADO};

/// estados del menú principal
enum menu_estado {MPRINCIPAL, MJUEGO, MOPCIONES, MVIDEO, MAUDIO, MCONTROLES, MCONF1, MCONF2, MCODIGO, MCONF1GRAB, MCONF2GRAB};

/// resoluciones graficas
enum resolucion {BAJA, ALTA};

/// eje o punto de control para las imagenes
enum ancla {UP_LEFT, UP, UP_RIGHT, LEFT, CENTER, RIGHT, DOWN_LEFT, DOWN, DOWN_RIGHT};

/// escenas gestionadas por mundo
enum nro_escena {MENU, JUEGO, CREDITOS, TECLAS, RECORDS};

/// transiciones entre escenas
enum tipo_transicion {BARRAS, DESDEARRIBA, DESDEABAJO};

/// codigos de sonidos 
enum tipo_sonido {STOC, STIC, SBURBUJA1, SPIERDE, SDISPARA, SMUERE, SSALTA};

/// musicas
enum tipo_musica {MMENU, MJUGANDO};

/// animaciones de sprites 'class simple' y textos
enum tipo_anim {ANONE, ALEFT, ARIGHT, AUPLEFT, AUPRIGHT, ASALIDA, ASUBE, AQUITAR};

/// teclado
enum teclado{ESCAPE,MUP,MDOWN,MLEFT,MRIGHT,P1UP,P1DOWN,P1LEFT,P1RIGHT,P1FIRE,PAUSA,P2UP,P2DOWN,P2LEFT,P2RIGHT,P2FIRE};


/// mensajes del protagonista al juego
enum mensajes{MPUEDE_CONTINUAR, MSIN_CREDITOS};

#endif
