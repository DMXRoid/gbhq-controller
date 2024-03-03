#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"
#include "audio.h"

AudioController* audioController;

AudioController::AudioController() {
	AudioLogger::instance().begin(Serial, AudioLogger::Debug);  
	AnalogAudioStream analogStream;
	EncodedAudioStream decoder(&analogStream, new MP3DecoderHelix());
	StreamCopy copier(decoder, targetURL);

	auto config = analogStream.defaultConfig(TX_MODE);
	analogStream.begin(config);
	decoder.begin();
}


void AudioController::loop() {
	if (isPlaying) {
		copier.copy();
	}
}

void AudioController::playURL(String url) {
	targetURL.begin(url.c_str());
	isPlaying = true;
}
void initAudio() {
	audioController = new AudioController();
}

AudioController* getAudioController() {
	return audioController;
}

void audioLoop() {
	getAudioController()->loop();
}