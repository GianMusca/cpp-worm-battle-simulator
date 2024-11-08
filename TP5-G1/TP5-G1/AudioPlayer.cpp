#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "AudioPlayer.h"
#include "Errores.h"

AudioPlayer::AudioPlayer(int& error) {
	error = ERR_NONE;
	if (al_is_system_installed() == false) {
		if (!al_init()) {
			error = ERR_AL_INIT;
		}
	}
	if (error == ERR_NONE) {
		if (!al_install_audio()) {
			error = ERR_AL_AUDIO;
		}
		else if (!al_init_acodec_addon()) {
			error = ERR_AL_ACODEC;
		}
		else if (!al_reserve_samples(5)) {
			error = ERR_AL_RSAMPLE;
		}
		else {
			music = al_load_sample("worms-music.wav");
			axeSample = al_load_sample("worms-axe.wav");
			hitSample = al_load_sample("worms-hit.wav");
			
			if (music == NULL || axeSample == NULL || hitSample == NULL) {
				error = ERR_AL_LSAMPLE;
			}
		}
	}
}

AudioPlayer::~AudioPlayer() {

	al_destroy_sample(music);

}