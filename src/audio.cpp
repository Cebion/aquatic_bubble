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

#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include "audio.h"
#include "int_gettext.h"

/*!
 * \brief destructor
 */
audio :: ~audio()
{
	if (sonido)
		descargar_sonidos();

	if (musica)
		descargar_musicas();
	
	Mix_CloseAudio();
}


/*!
 * \brief inicializa el subsistema de musica y sonido
 */
int audio :: iniciar (const bool musica, const bool sonido)
{

	if (musica || sonido)
	{
		if (iniciar_sistema_audio())
		{
			printf(_("- Audio system disabled because of errors\n"));
			hab_sistema = false;
			this->musica = false;
			this->sonido = false;
		}
		else
		{
			printf(_("+ Starting audio system\n"));

			hab_sistema = true;

			if (sonido)
				cargar_sonidos();

			if (musica)
				cargar_musicas();


			this->musica = musica;
			this->sonido = sonido;
		}
	}
	else
	{
		printf(_("- Audio system disabled from paremeters\n"));

		hab_sistema = false;
		this->musica = false;
		this->sonido = false;
	}

	return 0;
}


/*!
 * \brief ejecuta el subsistema de audio de SDL
 *
 * \return 1 en caso de error, 0 en caso contrario
 */
int audio :: iniciar_sistema_audio (void)
{
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) == -1)
	{
		printf(_("Error in audio subsystem: %s\n"), SDL_GetError());
		return 1;
	}

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
	{
		printf(_("Couldn't set 44100 Hz 16 bits audio: %s\n"),\
					SDL_GetError());
		return 1;
	}

	printf(_("+ Starting sound subsystem\n"));
	return 0;
}


/*!
 * \brief reproduce un sonido
 */
void audio :: play(enum tipo_sonido indice)
{
	if (!sonido)
		return;

	Mix_PlayChannel(0, snd[indice], 0);
}


/*!
 * \brief reproduce una canción
 */
void audio :: play_musica(enum tipo_musica indice)
{
	if (!musica)
		return;
}


/*!
 * \brief alterna entre 'musica habilitada' y 'musica deshabilitada'
 */
void audio :: cambiar_musica(void)
{
	if (musica)
		cancelar_musica();
	else
		habilitar_musica();
}


/*!
 * \brief alterna entre 'sonido habilitado' y 'sonido deshabilitado'
 */
void audio :: cambiar_sonido(void)
{
	if (sonido)
		cancelar_sonido();
	else
		habilitar_sonido();
}



/*!
 * \brief carga y habilita las músicas
 */
void audio :: habilitar_musica(void)
{
	if (!hab_sistema)
	{
		printf(_("Couldn't enable music because of audio subsystem"\
					" is disabled\n"));
		return;
	}
	
	musica = true;
}

/*!
 * \brief habilita los efectos de sonido
 */
void audio :: habilitar_sonido(void)
{
	if (!hab_sistema)
	{
		printf(_("Couldn't enable sound because of sound subsystem"\
					" is disabled\n"));
		return;
	}

	sonido = true;
}

/*!
 * \brief detiene las musicas
 */
void audio :: cancelar_musica(void)
{
	musica = false;
}

/*!
 * \brief cancela los efectos de sonido
 */
void audio :: cancelar_sonido(void)
{
	sonido = false;
}

/*!
 * \brief carga los archivos de sonido
 *
 * \return 1 en caso de error
 */
int audio :: cargar_sonidos(void)
{
	snd[0] = Mix_LoadWAV(DATA_DIR "sonidos/toc.wav");
	snd[1] = Mix_LoadWAV(DATA_DIR "sonidos/tic.wav");
	snd[2] = Mix_LoadWAV(DATA_DIR "sonidos/burbuja1.wav");
	snd[SPIERDE] = Mix_LoadWAV(DATA_DIR "sonidos/pierde.wav");
	return 0;
}


/*!
 * \brief carga todos los archivos musicales
 *
 * \return 1 en caso de errores
 */
int audio :: cargar_musicas(void)
{
	//musicas[i] = Mix_LoadMUS(nombres[i]);
	return 0;
}


/*!
 * \brief libera espacio de memoria pedido por cargar_sonidos
 */
void audio :: descargar_sonidos(void)
{
	Mix_FreeChunk(snd[0]);
	Mix_FreeChunk(snd[1]);
	Mix_FreeChunk(snd[2]);
	Mix_FreeChunk(snd[3]);
}



/*!
 * \brief libera memoria
 */
void audio :: descargar_musicas(void)
{
	//Mix_FreeMusic(musicas[0]);
}
