#include <WString.h>
#include <HardwareSerial.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

String getFileContents(String);
bool writeToFile(String, String);
void log(String);
void initFS();
void initLogs();

void mergeJSON(JsonVariant, JsonVariantConst);