#pragma once
#include <allegro5/allegro.h>

class EventGenerator {
public:
	EventGenerator(double, int&);
	~EventGenerator();

	void start(){ al_start_timer(timer); }
	bool getEvent(ALLEGRO_EVENT&);

	void registerEventSource(ALLEGRO_EVENT_SOURCE* source);
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	double tickspersec;
};