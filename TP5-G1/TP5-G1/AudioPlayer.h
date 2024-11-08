#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class AudioPlayer {
public:
	AudioPlayer(int&);
	~AudioPlayer();

	void loopMusic() { al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL); }
	void playAxeSample() { al_play_sample(axeSample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); }
	void playHitSample() { al_play_sample(hitSample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); }

protected:
	ALLEGRO_SAMPLE* music = NULL;
	ALLEGRO_SAMPLE* axeSample = NULL;
	ALLEGRO_SAMPLE* hitSample = NULL;
};