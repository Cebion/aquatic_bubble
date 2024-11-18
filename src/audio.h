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

#ifndef _AUDIO_H
#define _AUDIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "enum.h"

/*!
 * \brief Un estado del juego: menu
 */
class audio
{
	public:
		~audio();
		int iniciar(const bool musica, const bool sonido);
		void play(enum tipo_sonido indice);
		void play_musica(enum tipo_musica musica);
		
		bool get_sonido(void) {return sonido;};
		bool get_musica(void) {return musica;};
	
		void cambiar_musica(void);
		void cambiar_sonido(void);
		
	private:
		bool musica;
		bool sonido;
		bool hab_sistema;

		Mix_Chunk *snd[5];
		Mix_Music *mus[5];

		int iniciar_sistema_audio(void);
		int cargar_sonidos(void);
		int cargar_musicas(void);
		void descargar_sonidos(void);
		void descargar_musicas(void);
		
		void habilitar_musica(void);
		void habilitar_sonido(void);
		void cancelar_musica(void);
		void cancelar_sonido(void);
};
		
#endif
