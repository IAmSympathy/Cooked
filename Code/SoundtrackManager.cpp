#include "SoundtrackManager.h"

void SoundtrackManager::toggleSondtrack(bool play)
{
	_playing = play;

	if (_playing) {
		_soundtrack.play();
	}
	else {
		_soundtrack.stop();
	}
}

void SoundtrackManager::loadSoundtrack(int soundtrack)
{
	// Open it from an audio file
	if (!_soundtrack.openFromFile(PATH_AUDIO_MUSIC + std::to_string(soundtrack) + ".ogg"))
	{
		// error...
	}

	// Change some parameters
	_soundtrack.setVolume(15);         // reduce the volume
	_soundtrack.setLoop(true);         // make it loop

	// Play it
	_soundtrack.play();
}
