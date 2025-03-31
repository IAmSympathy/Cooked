/*====================================
// Filename : SoundtrackManager
// Description : gere la musique de background
//				 permet de change la musique et de la mute
// Author : Cedrik Caron,
// Date : November 30th 2024
====================================*/

#pragma once
#include "SFML/Audio.hpp"
#include "string.h"
#include "definitions.h"


class SoundtrackManager
{
private:
	int _currentSoundtrack = 0;
	bool _playing = true;
	sf::Music _soundtrack;

public:
	void toggleSondtrack(bool play);
	void loadSoundtrack(int soundtrack);
};

