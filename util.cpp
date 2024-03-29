#include "LittleFS.h"
#include "config.h"
#include "util.h"
File logFile; 

void log(String l) {
	Serial.println(l);
	if(logFile) {
		if (logFile.size() > 15000) { 
			logFile.close();
			initLogs();
		}
		int b = logFile.println(l);
		if(!b) {
			Serial.println("Could not write to log file.	Log line: " + l);
		}
	}
	else {
		Serial.println("Could not open log file. Log line: " + l);
	}
}

void initFS() {
	if(LittleFS.begin(true)) {
		log("Filesystem mounted");
	}
	else {
		log("Filesystem mounting failed");
	}
	
}



void initLogs() {
	// truncate the log file
	logFile = LittleFS.open(LOG_FILE, "w+");
	if(!logFile) {
		Serial.println("Couldn't create log file");
		Serial.println("Trying to format...");
		if(LittleFS.format()) {
			initLogs();
		}
	}
}

String getFileContents(String fileName) {
	String c;
	File f;
	
	f = LittleFS.open(fileName, "r");
	
	if(f) {
		c = f.readString();
		if (fileName != LOG_FILE) {
			f.close();
		}
	}
	else {
		log("Couldn't open file: " + fileName);
	}
	return c;
}

bool writeToFile(String fileName, String contents) {
	log("Writing to file " + fileName + ": " + contents);
	bool s;
	File f = LittleFS.open(fileName, "a+");
	if(f) {
		int b = f.print(contents);
		if(!b) {
			log("Couldn't write to file: " + fileName);
		}
		else {
			s = true;
		}
		f.close();
	}
	else {
		log("Couldn't open file: " + fileName);
	}
	return s;
}

void mergeJSON(JsonVariant dst, JsonVariantConst src)
{
  if (src.is<JsonObjectConst>())
  {
    for (JsonPairConst kvp : src.as<JsonObjectConst>())
    {
      if (dst[kvp.key()]) 
        mergeJSON(dst[kvp.key()], kvp.value());
      else
        dst[kvp.key()] = kvp.value();
    }
  }
  else
  {
    dst.set(src);
  }
}
