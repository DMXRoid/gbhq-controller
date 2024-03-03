#include "ArduinoJson/Array/JsonArray.hpp"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <LittleFS.h> 


class HttpServer {
	public:
		HttpServer();
		void loop();
		void init();
		void handleFileUpload();
		void sendHTMLResponse(String, int);
	private:
		WebServer server;
		JsonDocument responseMessage;
		JsonDocument requestJSON;
		
		File fsUploadFile;
		void sendResponse(String, int);
		
		void sendJSONResponse();
		

		void handleJSONAction();		

};

void handleUpload();
HttpServer* getHttpServer();
extern HttpServer* httpServer;

