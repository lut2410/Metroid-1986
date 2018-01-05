#pragma once
#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL

#define SOUND_INTRO_SCENE				"Resources/Sound/intro_scene.wav"
#define SOUND_PLAY_SCENE				"Resources/Sound/play_scene.wav"
#define SOUND_END_SCENE					"Resources/Sound/end_scene.wav"
#define SOUND_DIE						"Resources/Sound/die.wav"
#define SOUND_BE_WOUNDED				"Resources/Sound/beWounded.wav"
#define SOUND_JUMP						"Resources/Sound/jump.wav"
#define SOUND_FALL_INTO_FIRE			"Resources/Sound/fall_into_fire.wav"
#define SOUND_SHOOT_NORMAL				"Resources/Sound/shoot_normal_bullet.wav"
#define SOUND_SHOOT_ICE					"Resources/Sound/shoot_ice_bullet.wav"
#define SOUND_SHOOT_WAVE				"Resources/Sound/shoot_wave_bullet.wav"
#define SOUND_SHOOT_ROCKET				"Resources/Sound/shoot_missilerocket.wav"
#define SOUND_SET_BOMB					"Resources/Sound/set_bomb.wav"
#define SOUND_HIT_RIPPER				"Resources/Sound/hit_ripper.wav"
#define SOUND_HIT_ENEMY					"Resources/Sound/hit_enemy.wav"
#define SOUND_EXPLODE					"Resources/Sound/explode.wav"
#define SOUND_EAT_BEAM					"Resources/Sound/eat_long,ice,wave_beam.wav"
#define SOUND_EAT_MARUMARI				"Resources/Sound/eat_marumari.wav"
#define SOUND_EAT_MISSIBLEROCKET_BOMB	"Resources/Sound/eat_missilerocket_bomb.wav"
#define SOUND_EAT_HP_TONIC				"Resources/Sound/eat_HPTonic.wav"










#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

#include <sstream>
#include <iostream>
#include <dsound.h>
#include<vector>
#include "CWaveFile.h"

enum SOUND_ID
{
	ID_SOUND_MAP1,
	ID_SOUND_JUMP,
	ID_SOUND_COIN,
	ID_TAIL_TALLWHIP,
	ID_SOUND_MUSHROOM_OBTAIN,
	ID_SOUND_RACOON_LEFT_OBTAIN,
	ID_SOUND_LIFE_UP,
	ID_SOUND_MARIO_SLIPING,
	ID_SOUND_BEAN_STALK,
	ID_SOUND_PIPE_MAZE,
	ID_SOUND_SQUISH,
	ID_SOUND_MARIO_ATTACK,
	ID_SOUND_BLOCK_BREAKING
};
// -----------------------------------------------
// Name: class TSound
// Desc: used to load/ store/ play an audio with wav extension.
// -----------------------------------------------
class Sound
{
public:
	Sound(const char* audioPath);
	~Sound(void);

	static HRESULT initializeSoundClass(HWND windowsHandler);
	static HRESULT releaseSoundClass();

	HRESULT play(bool isLoop = false, DWORD priority = 0);
	HRESULT stop();


private:
	HRESULT loadAudio(const char* audioPath);

private:
	static WAVEFORMATEX bufferFormat_;
	static DSBUFFERDESC bufferDescription_;
	static LPDIRECTSOUND8 audioHandler_;
	static HWND windowsHandler_;

	LPDIRECTSOUNDBUFFER soundBuffer_;
};
