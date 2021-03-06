/*
SoLoud audio engine
Copyright (c) 2013-2014 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#ifndef SOLOUD_AUDIOSOURCE_H
#define SOLOUD_AUDIOSOURCE_H

#include "soloud.h"
#include "soloud_fader.h"
#include "soloud_filter.h"

namespace SoLoud
{
	class AudioSource;

	struct AudioSourceResampleData
	{
		AudioSourceResampleData();
		~AudioSourceResampleData();
		float *mBuffer;
	};

	// Base class for audio instances
	class AudioSourceInstance
	{
	public:
		enum FLAGS
		{			
			// This audio instance loops (if supported)
			LOOPING = 1,
			// This audio instance is protected - won't get stopped if we run out of voices
			PROTECTED = 2,
			// This audio instance is paused
			PAUSED = 4
		};
		// Ctor
		AudioSourceInstance();
		// Dtor
		virtual ~AudioSourceInstance();
		// Play index; used to identify instances from handles
		unsigned int mPlayIndex;
		// Loop count
		unsigned int mLoopCount;
		// Flags; see AudioSourceInstance::FLAGS
		unsigned int mFlags;
		// Pan value, for getPan()
		float mPan;
		// Left channel volume (panning)
		float mLVolume;
		// Right channel volume (panning)
		float mRVolume;
		// Overall volume
		float mVolume;
		// Base samplerate; samplerate = base samplerate * relative play speed
		float mBaseSamplerate;
		// Samplerate; samplerate = base samplerate * relative play speed
		float mSamplerate;
		// Number of channels this audio source produces
		unsigned int mChannels;
		// Relative play speed; samplerate = base samplerate * relative play speed
		float mRelativePlaySpeed;
		// How long this stream has played, in seconds.
		time mStreamTime;
		// Fader for the audio panning
		Fader mPanFader;
		// Fader for the audio volume
		Fader mVolumeFader;
		// Fader for the relative play speed
		Fader mRelativePlaySpeedFader;
		// Fader used to schedule pausing of the stream
		Fader mPauseScheduler;
		// Fader used to schedule stopping of the stream
		Fader mStopScheduler;
		// Affected by some fader
		int mActiveFader;
		// Fader-affected l/r volumes
		float mFaderVolume[2 * 2];
		// ID of the sound source that generated this instance
		unsigned int mAudioSourceID;
		// Handle of the bus this audio instance is playing on. 0 for root.
		unsigned int mBusHandle;
		// Filter pointer
		FilterInstance *mFilter[FILTERS_PER_STREAM];
		// Initialize instance. Mostly internal use.
		void init(int aPlayIndex, float aBaseSamplerate, int aChannels, int aSourceFlags);
		// Buffers for the resampler
		AudioSourceResampleData *mResampleData[2];
		// Sub-sample playhead; 16.16 fixed point
		unsigned int mSrcOffset;
		// Samples left over from earlier pass
		unsigned int mLeftoverSamples;
		// Number of samples to delay streaming
		unsigned int mDelaySamples;
		// Get N samples from the stream to the buffer
		virtual void getAudio(float *aBuffer, unsigned int aSamples) = 0;
		// Has the stream ended?
		virtual bool hasEnded() = 0;
		// Seek to certain place in the stream. Base implementation is generic "tape" seek (and slow).
		virtual void seek(time aSeconds, float *mScratch, unsigned int mScratchSize);
		// Rewind stream. Base implementation returns NOT_IMPLEMENTED, meaning it can't rewind.
		virtual result rewind();
	};

	class Soloud;

	// Base class for audio sources
	class AudioSource
	{
	public:
		enum FLAGS
		{
			// The instances from this audio source should loop
			SHOULD_LOOP = 1,
			// Only one instance of this audio source should play at the same time
			SINGLE_INSTANCE = 2,
			// Visualization data gathering enabled. Only for busses.
			VISUALIZATION_DATA = 4
		};
		// Flags. See AudioSource::FLAGS
		unsigned int mFlags;
		// Base sample rate, used to initialize instances
		float mBaseSamplerate;
		// Number of channels this audio source produces
		unsigned int mChannels;
		// Sound source ID. Assigned by SoLoud the first time it's played.
		unsigned int mAudioSourceID;
		// Filter pointer
		Filter *mFilter[FILTERS_PER_STREAM];
		// Pointer to the Soloud object. Needed to stop all instances in dtor.
		Soloud *mSoloud;

		// CTor
		AudioSource();
		// Set the looping of the instances created from this audio source
		void setLooping(bool aLoop);
		// Set whether only one instance of this sound should ever be playing at the same time
		void setSingleInstance(bool aSingleInstance);
		// Set filter. Set to NULL to clear the filter.
		virtual void setFilter(unsigned int aFilterId, Filter *aFilter);
		// DTor
		virtual ~AudioSource();
		// Create instance from the audio source. Called from within Soloud class.
		virtual AudioSourceInstance *createInstance() = 0;
		// Stop all instances of this audio source
		void stop();
	};
};

#endif
