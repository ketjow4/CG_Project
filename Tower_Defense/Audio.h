#pragma once
#include <iostream>
#include <string>

#include "audiere.h"


using namespace audiere;

class Audio
{
public:
	Audio();
	~Audio();

	void Play(std::string fileName);
	void MouseClick();
	void PlayBackground();

private:
	
	AudioDevicePtr device;

	void LoadFile();
};

