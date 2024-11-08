#include <math.h>
#include "Worm.h"
#include "Errores.h"

Worm::Worm(uint newx, uint newy, int& error) {
	x = newx;
	y = newy;
	xspeed = 0;
	yspeed = 0;
	state = IDLE;
	substate = 0;
	walkState = 0;
	walking = false;
	orientation = LEFT;

	error = ERR_NONE;
	if (al_is_system_installed() == false) {
		if (!al_init()) {
			error = ERR_AL_INIT;
		}
	}
	if (error == ERR_NONE) {
		al_init_user_event_source(&wormEventSource);
		wormEvent.user.type = ALLEGRO_GET_EVENT_TYPE('W', 'O', 'R', 'M');
	}
}

Worm::~Worm() {
	al_destroy_user_event_source(&wormEventSource);
}

void Worm::update() {
	switch (state) {
		case JUMP_WARMUP:
			substate++;
			if (substate > 3) {
				changeState(JUMP);
				xspeed = cos(3.1416 / 3.0) * 4.5 * ((orientation==LEFT)?-1:1);
				yspeed = sin(3.1416 / 3.0) * 4.5;
			}
			break;
		case JUMP:
			substate++;
			x += round(xspeed);
			y -= round(yspeed);
			yspeed -= 0.24;
			if (x <= xmin) x = xmin;
			if (x >= xmax) x = xmax;
			if (y >= ymax) {
				y = ymax;
				xspeed = 0;
				yspeed = 0;
				changeState(JUMP_WARMDOWN);
			}
			break;
		case JUMP_WARMDOWN:
			substate++;
			if (substate > 4) {
				changeState(IDLE);
			}
			break;
		case WALK_WAIT:
			substate++;
			if (walking == false) {
				changeState(IDLE);
			}else if (substate > 4) {
				changeState(WALK_WARMUP);
			}
			break;
		case WALK_WARMUP:
			substate++;
			if (substate > 2) {
				changeState(WALK);
			}
			break; 
		case WALK:
			substate++;
			if (substate > 13)
			{
				substate = 0;
				walkState++;
				x += (orientation == RIGHT) ? 9 : -9;
				if (x <= xmin) x = xmin;
				if (x >= xmax) x = xmax;
			}
			if (walkState >= 3)
			{
				walkState = 0;
				if (walking == true) 

					changeState(WALK_WAIT);
				else
					changeState(IDLE);
			}
			break; 
		case AXE_SWING:
			substate++;
			if (substate == 24) {
				wormEvent.user.data1 = EVENT_AXE_SWING;
				al_emit_user_event(&wormEventSource, &wormEvent, NULL);
			}
			if (substate == 27) {
				wormEvent.user.data1 = EVENT_AXE_HIT;
				al_emit_user_event(&wormEventSource, &wormEvent, NULL);
			}
			if (substate >= 62) {
				changeState(IDLE);
			}
			break;
		case AXE_HIT:
			substate++;
			if (substate >= 5) {
				changeState(IDLE);
			}
			break;
		case IDLE:
			substate = 0;
			break;
	}
}

void Worm::beginWalk(bool dir) {
	orientation = dir;
	walking = true;
	changeState(WALK_WAIT);
}

void Worm::stopWalk() {
	walking = false;
}

bool Worm::isInHitBox(Worm& w) {
	double xhit = (orientation == LEFT) ? x - 32 : x + 32;
	double xdist = (w.x - xhit > 0) ? (w.x - xhit) : -(w.x - xhit);
	if (xdist < 15) {
		return true;
	}
	return false;
}