#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string> 
#include "WormsGUI.h"
#include "Tipos.h"
#include "Errores.h"

using namespace std;

WormsGUI::WormsGUI(int width, int &error) {

	scale = (double)width / 1920.0;
	
	error = ERR_NONE;
	if (al_is_system_installed() == false) {
		if (!al_init()) {
			error = ERR_AL_INIT;
		}
	}
	if (error == ERR_NONE) {
		if (!al_init_image_addon()) {
			error = ERR_AL_IMAGE;
		}
		else {
			display = al_create_display(1920 * scale, 696 * scale);
			if (!display) {
				error = ERR_AL_DISPLAY;
			}
			else {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_flip_display();
				
				background = al_load_bitmap("Background.png");

				scenario = al_load_bitmap("Scenario.png");

				if (!background || !scenario)
					error = ERR_AL_LOAD_BITMAP;

				for (int i = 0; i < 15; i++) {
					string filename = "wwalk-F" + to_string(i+1) + ".png";
					wormWalk[i] = al_load_bitmap(filename.c_str());
					
					if (!wormWalk[i])
						error = ERR_AL_LOAD_BITMAP;
				}
				for (int i = 0; i < 10; i++) {
					string filename = "wjump-F" + to_string(i+1) + ".png";
					wormJump[i] = al_load_bitmap(filename.c_str());

					if (!wormJump[i]) 
						error = ERR_AL_LOAD_BITMAP;
				}
				for (int i = 0; i < 62; i++) {
					string filename = "tile0";
					if (i < 10) filename += "0";
					filename += to_string(i) + ".png";
					wormAxe[i] = al_load_bitmap(filename.c_str());

					if (!wormAxe[i])
						error = ERR_AL_LOAD_BITMAP;
				}
				for (int i = 0; i < 4; i++) {
					string filename = "whit" + to_string(i + 1) + ".png";
					wormHit[i] = al_load_bitmap(filename.c_str());

					if (!wormHit[i])
						error = ERR_AL_LOAD_BITMAP;
				}
			}
		}
	}
}

WormsGUI::~WormsGUI() {
	al_destroy_bitmap(background);		//Does nothing if given the null pointer.
	al_destroy_bitmap(scenario);

	for (int i = 0; i < 15; i++)
		al_destroy_bitmap(wormWalk[i]);
	
	for (int i = 0; i < 10; i++)
		al_destroy_bitmap(wormJump[i]);

	for (int i = 0; i < 62; i++)
		al_destroy_bitmap(wormAxe[i]);

	for (int i = 0; i < 4; i++)
		al_destroy_bitmap(wormHit[i]);

	if (display)
		al_destroy_display(display);
}

void WormsGUI::drawLevel() {
	al_draw_scaled_bitmap(background, 0, 0, 1920, 696, 0, 0, 1920*scale, 696*scale, 0);
	al_draw_scaled_bitmap(scenario, 0, 0, 1920, 696, 0, 0, 1920*scale, 696*scale, 0);
}

void WormsGUI::drawWorm(Worm& worm) {
	ALLEGRO_BITMAP* worm_bmp = getWormBitmap(worm.getState(), worm.getSubstate());
	if (worm_bmp != NULL) {
		uint x = worm.getX();
		uint y = worm.getY();
		int flags = (worm.getOrientation() == RIGHT) ? ALLEGRO_FLIP_HORIZONTAL : 0;
		if (worm.getState() == AXE_SWING) {
			int dx = (worm.getOrientation() == RIGHT) ? -15 : -26;
			al_draw_scaled_bitmap(worm_bmp, 0, 0, 100, 100, (x+dx) * scale, (y-22) * scale, 100 * scale, 100 * scale, flags);
		}
		else {
			al_draw_scaled_bitmap(worm_bmp, 0, 0, 60, 60, x * scale, y * scale, 60 * scale, 60 * scale, flags);
		}
	}

}

ALLEGRO_BITMAP* WormsGUI::getWormBitmap(StateType state, int substate) {
	ALLEGRO_BITMAP* bitmap = NULL;
	switch (state) {
	case IDLE:
	case WALK_WAIT:
		bitmap = wormWalk[3];
		break;
	case WALK_WARMUP:
		if (substate < 3) bitmap = wormWalk[substate];
		break;
	case WALK:
		if (substate <= 7) bitmap = wormWalk[substate + 3];				//1-8
		else if (substate <= 12) bitmap = wormWalk[substate + 2];		//9-13
		else if (substate == 13) bitmap = wormWalk[3];					//14
		break;
	case JUMP_WARMUP:
		if (substate <= 3) bitmap = wormJump[substate];
		break;
	case JUMP:
		bitmap = wormJump[4];
		break;
	case JUMP_WARMDOWN:
		if (substate <= 4) bitmap = wormJump[substate + 5];
		break;
	case AXE_SWING:
		if (substate < 62) bitmap = wormAxe[substate];
		break;
	case AXE_HIT:
		if (substate < 5) bitmap = wormHit[substate];
		break;
	}
	return bitmap;
}