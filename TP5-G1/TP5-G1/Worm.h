#pragma once
#include <allegro5/allegro.h>
#include "Tipos.h"

#define LEFT	false
#define RIGHT	true

typedef enum {IDLE, WALK_WAIT, WALK_WARMUP, WALK, JUMP_WARMUP, JUMP, JUMP_WARMDOWN, AXE_SWING, AXE_HIT}StateType;

typedef enum { EVENT_AXE_SWING, EVENT_AXE_HIT }WormEvent;

class Worm {
public:
	Worm(uint, uint, int&);
	~Worm();
	StateType getState() { return state; }
	uint getSubstate() { return substate; }
	uint getX() { return (uint)x; }
	uint getY() { return (uint)y; }
	bool getOrientation() { return orientation; }
	void beginJump() { changeState(JUMP_WARMUP); };
	void beginWalk(bool);
	void stopWalk();
	void swingAxe() { changeState(AXE_SWING); };
	void changeState(StateType s) { state = s; substate = 0; }
	void update();
	bool isInHitBox(Worm&);
	ALLEGRO_EVENT_SOURCE* getEventSource() { return &wormEventSource; }

protected:
	ALLEGRO_EVENT_SOURCE wormEventSource;
	ALLEGRO_EVENT wormEvent;

	StateType state;	//Estado del movimiento (Idle, Walk, etc...)
	uint substate;		//Subestado, en qué "paso" del movimiento o "frame" se encuentra
	uint walkState;
	bool walking;
	double x, y;
	bool orientation;
	double xspeed, yspeed;
	const uint ymax = 573;
	const uint xmin = 685;
	const uint xmax = 1168;
};