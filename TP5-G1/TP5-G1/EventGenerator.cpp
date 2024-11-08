#include <allegro5/allegro.h>
#include "EventGenerator.h"
#include "Tipos.h"
#include "Errores.h"

EventGenerator::EventGenerator(double ticks, int& error) {
	tickspersec = ticks;
	timer = NULL;
	event_queue = NULL;
	error = ERR_NONE;
	if (al_is_system_installed() == false) {
		if (!al_init()) {
			error = ERR_AL_INIT;
		}
	}
	if (error == ERR_NONE) {
		timer = al_create_timer(1.0 / tickspersec);
		if (!timer) {
			error = ERR_AL_TIMER;
		}
		else {
			event_queue = al_create_event_queue();
			if (!event_queue) {
				al_destroy_timer(timer);
				error = ERR_AL_EVQUEUE;
			}
			else {
				registerEventSource(al_get_timer_event_source(timer));
			}
		}
	}
}

EventGenerator::~EventGenerator() {
	if (timer != NULL) al_destroy_timer(timer);
	if (event_queue != NULL) al_destroy_event_queue(event_queue);
}

void EventGenerator::registerEventSource(ALLEGRO_EVENT_SOURCE* source) {
	al_register_event_source(event_queue, source);
}

bool EventGenerator::getEvent(ALLEGRO_EVENT& ev) {
	return al_get_next_event(event_queue, &ev);
}