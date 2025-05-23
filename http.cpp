#include <ArduinoJson.h>
#include "config.h"
#include "util.h"
#include "networking.h"
#include "gbhq.h"
#include "LittleFS.h"
#include "audio.h"
#include "servo.h"

#include "http.h"

void (*resetFunc)(void) = 0;

HttpServer* httpServer;

HttpServer::HttpServer() {
  WebServer server(80);

  log("Starting HTTP setup");
  // dump the logs
}
void HttpServer::sendHTMLResponse(String rt, int code) {
  server.sendHeader("Cache-Control", "nocache");
  server.send(code, "text/html; charset=utf-8", rt);
}

void HttpServer::sendJSONResponse() {
  server.sendHeader("Cache-Control", "nocache");
  String rt;
  serializeJsonPretty(responseMessage, rt);
  server.send(responseMessage["code"], "application/json; charset=utf-8", rt);
}

void HttpServer::handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {

	String filename = upload.filename;
	if (!filename.startsWith("/")) {
	  filename = "/" + filename;
	}
	log("handleFileUpload Name: ");
	log(filename);
	fsUploadFile = LittleFS.open(filename, "w");
	filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
	log("handleFileUpload Data: ");
	log(upload.currentSize);
	if (fsUploadFile) {
	  fsUploadFile.write(upload.buf, upload.currentSize);
	}
  } else if (upload.status == UPLOAD_FILE_END) {
	if (fsUploadFile) {
	  fsUploadFile.close();
	}
	log("handleFileUpload Size: ");
	log(upload.totalSize);
  }
}
void HttpServer::init() {
  //server.onFileUpload(handleUpload);
  server.on("/act", HTTP_POST, [this]() {
	log("doing ACT stuff");
	requestJSON.clear();
	responseMessage.clear();
	log("SERVER ARG::::::::");
	log(server.arg("plain"));
	deserializeJson(requestJSON, server.arg("plain"));
	handleJSONAction();
	sendJSONResponse();
  });

  server.on("/get-logs", [this]() {
	log("getting logs");
	String l = getFileContents(LOG_FILE);
	sendHTMLResponse(l, 200);
  });

  server.on("/upload", HTTP_ANY,
            [&]() {
	          sendHTMLResponse("ok", 200);
	          log("200 sent");
            });

  server.on("/get-file", [this]() {
	String l = getFileContents(server.arg("n"));
	log("requested file" + l);
	l.replace("\n", "\n<br>\n");
	sendHTMLResponse(l, 200);
  });
  server.on("/ok", [this]() {
	sendHTMLResponse("ok", 200);
  });

  server.begin();
  log("HTTP setup complete");
}


void HttpServer::handleJSONAction() {
  log("about to do some json");

  if (requestJSON["action"]) {
	log("doing JSON stuff");
	if (requestJSON["action"] == "get-config") {
	  log("getting config, maybe");
	  responseMessage["code"] = 200;
	  responseMessage["message"] = config;
	} else if (requestJSON["action"] == "cycle-pins") {
	  log("cycling pins");
	  getGBHQController()->cyclePins();
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "set-config") {
	  mergeJSON(config, requestJSON["config"]);
	  saveConfig();
	  resetFunc();
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "override-config") {
	  config = requestJSON["config"];
	  saveConfig();
	  resetFunc();
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "pin_on") {
	  getGBHQController()->pinOn(requestJSON["pin_index"]);
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "pin_off") {
	  getGBHQController()->pinOff(requestJSON["pin_index"]);
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "reset") {
	  resetFunc();
	} else if (requestJSON["action"] == "play-audio") {
	  log("playing audio");
	  getAudioController()->loadFile(requestJSON["file_pattern"]);
	  getAudioController()->play();
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "play-script") {
	  log("playing script");
	  getGBHQController()->playScript(requestJSON["script_name"]);
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "set-servo") {
	  log("moving servo");
	  getServoController()->setServoPosition(requestJSON["index"], requestJSON["position"]);
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	} else if (requestJSON["action"] == "save-scripts") {
	  log("moving servo");
	  String s;
	  serializeJsonPretty(requestJSON["scripts"], s);
	  writeToFile("/scripts.json", s);
	  getGBHQController()->loadScripts();
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	}
	else if (requestJSON["action"] == "load-scripts") {
	  getGBHQController()->loadScripts();
	  responseMessage["code"] = 200;
	  responseMessage["message"] = "success";
	}
  }
}


void HttpServer::loop() {
  server.handleClient();
}

HttpServer* getHttpServer() {
  if (httpServer == NULL) {
	httpServer = new HttpServer();
  }
  return httpServer;
}

void handleUpload() {
  log("handling upload");
  getHttpServer()->handleFileUpload();
}
