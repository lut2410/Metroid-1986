#include "GameSound.h"


GameSound* GameSound::instance_ = nullptr;


GameSound::GameSound()
{
}


GameSound::~GameSound()
{

	loadedSound_.clear();
}

string GameSound::switchID(int id)
{
	return "";
}

void GameSound::initialize(HWND windowsHandler)
{
	Sound::initializeSoundClass(windowsHandler);
}


void GameSound::play(string soundLink, bool repeat, bool playFromStart /*= true*/)
{
	try
	{
		if (playFromStart)
			loadedSound_.at(soundLink)->stop();
	//	stop(soundLink);

		loadedSound_.at(soundLink)->play(repeat);
	}
	catch (exception)
	{
		loadedSound_.insert(SoundPair(soundLink, new Sound(soundLink.c_str())));
		loadedSound_.at(soundLink)->play(repeat);
	}
}
void GameSound::Play(int id, bool repeat)
{
	Stop(id);
	play(switchID(id), repeat);
}


GameSound* GameSound::getInstance()
{
	if (instance_ == 0)
	{
		instance_ = new GameSound();
	}

	return instance_;
}




void GameSound::stop(string soundLink)
{
	try
	{
		loadedSound_.at(soundLink)->stop();
	}
	catch (exception)
	{

	}
}

void GameSound::Stop(int id)
{
	stop(switchID(id));
}
