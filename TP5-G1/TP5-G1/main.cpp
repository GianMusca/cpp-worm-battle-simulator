#include <iostream>
#include <allegro5/allegro.h>
#include "WormsGUI.h"
#include "EventGenerator.h"
#include "AudioPlayer.h"
#include "Dispatcher.h"

using namespace std;

int main()
{
	int error_gui, error_ev, error_audio, error_w1, error_w2;
	WormsEnviroment env;
	WormsGUI gui(1360, error_gui);
	EventGenerator evgen(50, error_ev);
	AudioPlayer player(error_audio);
	Worm worm1(1000, 573, error_w1);
	Worm worm2(700, 573, error_w2);
	bool kb_success = al_install_keyboard();

	if (error_gui == ERR_NONE && error_ev == ERR_NONE && error_audio == ERR_NONE
		&& error_w1 == ERR_NONE && error_w2 == ERR_NONE && kb_success) {

		evgen.registerEventSource(gui.getDisplayEventSource());
		evgen.registerEventSource(al_get_keyboard_event_source());
		evgen.registerEventSource(worm1.getEventSource());
		evgen.registerEventSource(worm2.getEventSource());
		evgen.start();
		player.loopMusic();

		env = { &gui, &worm1, &worm2, &evgen, &player };

		while(dispatchEvent(env)) {}
	}
	else {
		cout << "Error!" << endl;
		cout << "Error GUI: "<< error_gui << endl;
		cout << "Error EventGenerator: " << error_ev << endl;
		cout << "Error Audio: " << error_audio << endl;
		cout << "Error Worm 1: " << error_w1 << endl;
		cout << "Error Worm 2: " << error_w2 << endl;
		cout << "Error Keyboard: " << !kb_success << endl;
	}
}