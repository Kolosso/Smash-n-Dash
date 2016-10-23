// Local includes:
#include "audiomanager.h"

// Library includes:
#include <iostream>

AudioManager::AudioManager()
: m_FMODsystem(0)
, m_FMODchannel(0)
, m_FMODchannelMusic(0)
, m_FMODsoundPunch(0)
, m_FMODsoundPunchMiss(0)
, m_FMODsoundDash(0)
, m_FMODsoundJump(0)
, m_FMODsoundDeath(0)
, m_FMODsoundMusic(0)
, volume(0.7f)
, volumeMusic(volume / 3)
, muted(false)
{

}

AudioManager::~AudioManager()
{
	m_FMODsystem->release();
}

bool
AudioManager::Initialise()
{
	FMOD_RESULT result;
	//FMOD::System *system = NULL;

	result = FMOD::System_Create(&m_FMODsystem);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = m_FMODsystem->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = m_FMODsystem->createSound("assets\\sePunch.wav", FMOD_2D, 0, &m_FMODsoundPunch);
	result = m_FMODsystem->createSound("assets\\sePunchMiss.wav", FMOD_2D, 0, &m_FMODsoundPunchMiss);
	result = m_FMODsystem->createSound("assets\\seDash.wav", FMOD_2D, 0, &m_FMODsoundDash);
	result = m_FMODsystem->createSound("assets\\seJump.wav", FMOD_2D, 0, &m_FMODsoundJump);
	result = m_FMODsystem->createSound("assets\\seDeath.wav", FMOD_2D, 0, &m_FMODsoundDeath);

	// Music by Eric Matyas    www.soundimage.org
	result = m_FMODsystem->createStream("assets\\Monster-Street-Fighters.mp3", FMOD_2D | FMOD_LOOP_NORMAL, 0, &m_FMODsoundMusic);

	if (result != FMOD_OK)
	{ 
		return(false);
	}
	
	return(true);
}

void
AudioManager::Update()
{
	m_FMODsystem->update();
}

void
AudioManager::PlaySound(soundEffects _SoundEffect)
{
	if (!muted)
	{
		if (_SoundEffect == punchSE)
		{
			m_FMODsystem->playSound(m_FMODsoundPunch, 0, 0, &m_FMODchannel);
		}
		if (_SoundEffect == punchMissSE)
		{
			m_FMODsystem->playSound(m_FMODsoundPunchMiss, 0, 0, &m_FMODchannel);
		}
		if (_SoundEffect == dashSE)
		{
			m_FMODsystem->playSound(m_FMODsoundDash, 0, 0, &m_FMODchannel);
		}
		if (_SoundEffect == jumpSE)
		{
			m_FMODsystem->playSound(m_FMODsoundJump, 0, 0, &m_FMODchannel);
		}
		if (_SoundEffect == deathSE)
		{
			m_FMODsystem->playSound(m_FMODsoundDeath, 0, 0, &m_FMODchannel);
		}
	}
	VolumeControl();
}

void
AudioManager::PlayMusic()
{
	m_FMODsystem->playSound(m_FMODsoundMusic, 0, 0, &m_FMODchannelMusic);
	m_FMODchannelMusic->setVolume( volumeMusic );

}

void
AudioManager::VolumeUp()
{
	volume += 0.1f;
	volumeMusic = volume / 3;
	VolumeControl();
}

void
AudioManager::VolumeDown()
{
	volume -= 0.1f;
	volumeMusic = volume / 3;
	VolumeControl();
}

void
AudioManager::VolumeControl()
{
	if (volume <= 0.0f)
	{
		muted = true;
		volume = 0.0f;
		m_FMODchannel->setMute( muted );
		m_FMODchannel->setVolume( volume );
		m_FMODchannelMusic->setMute( muted );
		m_FMODchannelMusic->setVolume( volumeMusic );
	}
	else
	{
		muted = false;
		if (volume > 1.0f)
		{
			volume = 1.0f;
		}
		m_FMODchannel->setMute( muted );
		m_FMODchannel->setVolume( volume );
		m_FMODchannelMusic->setMute( muted );
		m_FMODchannelMusic->setVolume( volumeMusic );
	}
}