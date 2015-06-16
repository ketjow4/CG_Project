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

	/**
	* Funkcja odtwarza dzwiêk z pliku.
	* @param fileName nazwa pliku dzwiêkowego
	*/
	void Play(std::string fileName);
	/**
	* Funkcja odtwarza dzwiêk klikniêcia myszy.
	*/
	void MouseClick();
	/**
	* Funkcja odtwarza dzwiêki t³a.
	*/
	void PlayBackground();
private:
	AudioDevicePtr device;
};

