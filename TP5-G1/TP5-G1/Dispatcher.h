#pragma once
#include "EventGenerator.h"
#include "WormsGUI.h"
#include "Worm.h"
#include "AudioPlayer.h"

typedef struct {
	WormsGUI* gui;
	Worm* worm1;
	Worm* worm2;
	EventGenerator* evgen;
	AudioPlayer* player;
}WormsEnviroment;

bool dispatchEvent(WormsEnviroment& env);