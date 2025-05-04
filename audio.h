#include "AudioTools.h"
#include "AudioTools/Disk/AudioSourceSDFAT.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"


class AudioController {
	public:
		AudioController();
		void playURL(String);
		void loadFile(const char*);
		void loop();
		void play();
		void stop();
		bool getIsPlaying();

	private:
		bool isPlaying;
		bool isLoaded;
		AudioSourceSDFAT *source;
		I2SStream i2s;
		MP3DecoderHelix decoder;
		AudioPlayer* player;
		

};


void initAudio();
AudioController* getAudioController();