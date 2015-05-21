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
	SoundEffectPtr sound = OpenSoundEffect(device, filename.c_str(), SINGLE);
	if (!sound)
	{
		std::cout << "Can not load sound\n";
		return;
	}
	sound->setVolume(0.7f);
	sound->play();
}

void Audio::MouseClick()
{
	std::string filename = "Audio/click.wav";
	SoundEffectPtr clickSound = OpenSoundEffect(device, filename.c_str(), SINGLE);
	if (!clickSound)
	{
		std::cout << "Can not load click sound\n";
		return;
	}
	clickSound->setVolume(1.0f);
	clickSound->play();
}

void Audio::PlayBackground()
{
	std::string filename = "Audio/backing.mp3";
	OutputStreamPtr stream = OutputStreamPtr(OpenSound(device, filename.c_str(), false));
	if (!stream)
	{
		std::cout << "Can not load background sound\n";
		return;
	}
	stream->setVolume(1.0f);
	stream->setRepeat(true);

	if (!stream->isPlaying())
		stream->play();
}

void Audio::LoadFile()
{

}

Audio::~Audio()
{
}

