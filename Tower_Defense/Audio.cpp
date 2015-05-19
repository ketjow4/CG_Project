#include "Audio.h"


Audio::Audio()
{
	AudioDevicePtr device(OpenDevice());
	std::cout << "Initializing audio engine\n";
	if (!device)
	{
		std::cout << "Can not initialize audio device.\n";
		return;
	}
	std::string filename = "Audio/backing.mp3";
	stream = OutputStreamPtr(OpenSound(device, filename.c_str(), false));
	if (!stream)
	{
		std::cout << "Can not load sound\n";
		return;
	}
	stream->setVolume(1.0f);
	stream->setRepeat(true);
}

void Audio::Play()
{
	if (!stream->isPlaying())
		stream->play();
}


Audio::~Audio()
{
}
