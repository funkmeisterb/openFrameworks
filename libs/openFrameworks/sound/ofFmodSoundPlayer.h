#pragma once

#include "ofConstants.h"


#include "ofBaseSoundPlayer.h"


extern "C" {
#include "fmod.h"
#include "fmod_errors.h"
#include "fmod_dsp.h"
}

//		TO DO :
//		---------------------------
// 		-fft via fmod, as in the last time...
// 		-close fmod if it's up
//		-loadSoundForStreaming(char * fileName);
//		---------------------------

// 		interesting:
//		http://www.compuphase.com/mp3/mp3loops.htm


// ---------------------------------------------------------------------------- SOUND SYSTEM FMOD

// --------------------- global functions:
void ofFmodSoundStopAll();
void ofFmodSoundSetVolume(float vol);
void ofFmodSoundUpdate();						// calls FMOD update.
float * ofFmodSoundGetSpectrum(int nBands);		// max 512...


// --------------------- player functions:
class ofFmodSoundPlayer : public ofBaseSoundPlayer {

	public:

		ofFmodSoundPlayer();
		virtual ~ofFmodSoundPlayer();

		bool loadSound(string fileName, bool stream = false);
		void unloadSound();
		void play();
		void stop();

		void setVolume(float vol);
		void setPan(float vol);
		void setSpeed(float spd);
		void setPaused(bool bP);
		void setLoop(bool bLp);
		void setMultiPlay(bool bMp);
		void setPosition(float pct); // 0 = start, 1 = end;
		void setPositionMS(int ms);
		void setLowpass(float pct); // { lowpass = pct; } // 0 or 1 = bypass

		float getPosition();
		int getPositionMS();
		bool getIsPlaying();
		float getSpeed();
		float getPan();
		float getVolume();
		float getLowpass() { return lowpass; }
		bool isLoaded();

		static void initializeFmod();
		static void closeFmod();

		bool isStreaming;
		bool bMultiPlay;
		bool bLoop;
		bool bLoadedOk;
		bool bPaused;
		float pan; // -1 to 1
		float volume; // 0 - 1
		float internalFreq; // 44100 ?
		float speed; // -n to n, 1 = normal, -1 backwards
		float lowpass; // 0 - 1
		unsigned int length; // in samples;

		FMOD_RESULT result;
		FMOD_CHANNEL * channel;
		FMOD_SOUND * sound;
		FMOD_DSP * lowpassDSP;
};

