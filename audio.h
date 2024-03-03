#include <AudioTools.h>


class AudioController {
	public:
		AudioController();
		void playURL(String);
		void loop();
		bool getIsPlaying();
	private:
		bool isPlaying;
		URLStream targetURL;
		AnalogAudioStream analogStream;
		EncodedAudioStream decoder;
		StreamCopy copier;

};

void initAudio();
AudioController* getAudioController();