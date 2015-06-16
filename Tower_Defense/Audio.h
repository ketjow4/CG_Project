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
	* Funkcja odtwarza dzwi�k z pliku.
	* @param fileName nazwa pliku dzwi�kowego
	*/
	void Play(std::string fileName);
	/**
	* Funkcja odtwarza dzwi�k klikni�cia myszy.
	*/
	void MouseClick();
	/**
	* Funkcja odtwarza dzwi�ki t�a.
	*/
	void PlayBackground();
private:
	AudioDevicePtr device;
};

