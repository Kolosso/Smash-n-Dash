#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"

typedef enum
{
	punchSE, punchMissSE, jumpSE, dashSE, deathSE
}soundEffects;

class AudioManager
{
	// Member Methods
public:
	AudioManager();
	~AudioManager();

	bool Initialise();

	void Update();
	void PlaySound(soundEffects _SoundEffect);
	void PlayMusic();

	void VolumeUp();
	void VolumeDown();

protected:
private:

	void VolumeControl();
	// Member Variables
public:
protected:
	FMOD::System* m_FMODsystem;
	FMOD::Channel* m_FMODchannel;
	FMOD::Channel* m_FMODchannelMusic;
	FMOD::Sound* m_FMODsoundPunch;
	FMOD::Sound* m_FMODsoundPunchMiss;
	FMOD::Sound* m_FMODsoundDash;
	FMOD::Sound* m_FMODsoundJump;
	FMOD::Sound* m_FMODsoundDeath;
	FMOD::Sound* m_FMODsoundMusic;
private:
	float volume;
	float volumeMusic;
	bool muted;
};

#endif __AUDIOMANAGER_H__