#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Worm.h"
#include "Errores.h"

class WormsGUI {
public:
	WormsGUI(int width, int&);
	~WormsGUI();

	void drawLevel();
	void drawWorm(Worm&);
	void showFrame() { al_flip_display(); }

	ALLEGRO_EVENT_SOURCE* getDisplayEventSource() { return al_get_display_event_source(display); }

private:
	ALLEGRO_BITMAP* getWormBitmap(StateType state, int substate);
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* scenario;

	ALLEGRO_BITMAP* wormWalk[15];
	ALLEGRO_BITMAP* wormJump[10];
	ALLEGRO_BITMAP* wormAxe[62];
	ALLEGRO_BITMAP* wormHit[5];

	double scale;
};