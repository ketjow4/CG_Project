#include "Audio.h"


Audio::Audio()
{
	device = OpenDevice();
	std::cout << "Initializing audio engine\n";
	if (!device)
	{
		std::cout << "Can not initialize audio device.\n";
		return;
	}
}

void Audio::Play(std::string filename)
{
	stream = OutputStreamPtr(OpenSound(device, filename.c_str(), false));
	if (!stream)
	{
		std::cout << "Can not load sound\n";
		return;
	}
	stream->setVolume(1.0f);
	stream->setRepeat(true);

	if (!stream->isPlaying())
		stream->play();
}

void Audio::PlayBackground()
{
	std::string filename = "Audio/backing.mp3";
	stream = OutputStreamPtr(OpenSound(device, filename.c_str(), false));
	if (!stream)
	{
		std::cout << "Can not load sound\n";
		return;
	}
	stream->setVolume(1.0f);
	stream->setRepeat(true);

	if (!stream->isPlaying())
		stream->play();
}

Audio::~Audio()
{
}
