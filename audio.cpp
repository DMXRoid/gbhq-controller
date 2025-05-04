#include "AudioTools.h"
#include "AudioTools/Disk/AudioSourceSDFAT.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"
#include "audio.h"
#include "util.h"

AudioController* audioController;


AudioController::AudioController() {
  auto config = i2s.defaultConfig(TX_MODE);
  config.i2s_format = I2S_LSB_FORMAT;
  config.pin_bck = 32;
  config.pin_ws = 25;
  config.pin_data = 12;
  i2s.begin(config);
  source = new AudioSourceSDFAT("/gbhq", "mp3");
  player = new AudioPlayer(*source, i2s, decoder);
}

void AudioController::loadFile(const char *filePattern) {
	if (isPlaying) {
		stop();
	}
	isLoaded = false;
	source->end();
	delete(source);
	source = new AudioSourceSDFAT("/gbhq", "mp3");
	source->setFileFilter(filePattern);
	player->setAudioSource(*source);
	
	isLoaded = true;
}


void AudioController::loop() {
  if(isLoaded && isPlaying) {
  	player->copy();
  }
}

void AudioController::play() {
  if(isLoaded && !isPlaying) {
	player->begin();
	isPlaying = true;
  }
}

void AudioController::stop() {
	if(isLoaded && isPlaying) {
		player->stop();
	}
	isPlaying = false;
}


void initAudio() {
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);
  audioController = new AudioController();
}

AudioController* getAudioController() {
  return audioController;
}

void audioLoop() {
  getAudioController()->loop();
}