#include "Dispatcher.h"

bool dispatchEvent(WormsEnviroment& env) {
	bool quit = false;
	ALLEGRO_EVENT ev;

	if (env.evgen->getEvent(ev)) {
		if (ALLEGRO_EVENT_TYPE_IS_USER(ev.type)) {
			switch (ev.user.data1) {
			case EVENT_AXE_SWING:
				env.player->playAxeSample();
				break;
			case EVENT_AXE_HIT:
				if (ev.user.source == env.worm1->getEventSource()) {
					if (env.worm1->isInHitBox(*env.worm2)) {
						env.player->playHitSample();
						if (env.worm2->getState() == IDLE) env.worm2->changeState(AXE_HIT);
					}
				}
				if (ev.user.source == env.worm2->getEventSource()) {
					if (env.worm2->isInHitBox(*env.worm1)) {
						env.player->playHitSample();
						if (env.worm1->getState() == IDLE) env.worm1->changeState(AXE_HIT);
					}
				}
				break;
			}
		}
		else {
			switch (ev.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				quit = true;
				break;
			case ALLEGRO_EVENT_TIMER:
				env.worm1->update();
				env.worm2->update();
				env.gui->drawLevel();
				env.gui->drawWorm(*env.worm1);
				env.gui->drawWorm(*env.worm2);
				env.gui->showFrame();
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					if (env.worm1->getState() == IDLE) env.worm1->beginJump();
					break;
				case ALLEGRO_KEY_LEFT:
					if (env.worm1->getState() == IDLE) env.worm1->beginWalk(LEFT);
					break;
				case ALLEGRO_KEY_RIGHT:
					if (env.worm1->getState() == IDLE) env.worm1->beginWalk(RIGHT);
					break;
				case ALLEGRO_KEY_A:
					if (env.worm2->getState() == IDLE) env.worm2->beginWalk(LEFT);
					break;
				case ALLEGRO_KEY_D:
					if (env.worm2->getState() == IDLE) env.worm2->beginWalk(RIGHT);
					break;
				case ALLEGRO_KEY_DOWN:
					if (env.worm1->getState() == IDLE) env.worm1->swingAxe();
					break;
				case ALLEGRO_KEY_W:
					if (env.worm2->getState() == IDLE) env.worm2->beginJump();
					break;
				case ALLEGRO_KEY_S:
					if (env.worm2->getState() == IDLE) env.worm2->swingAxe();
					break;
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					quit = true;
					break;
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_RIGHT:
					env.worm1->stopWalk();
					break;
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_D:
					env.worm2->stopWalk();
					break;
				}
				break;
			}
		}
	}

	return !quit;
}