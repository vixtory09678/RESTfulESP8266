/*
Library ServerManager service HTTP Protocol RESTful
Support only json data now 
created by teamkung
github www.github.com/vixtory09678
*/

#include <ServerManager.h>
#include <ESP8266WiFi.h>

const char* ssid = "teamkuywa";
const char* password = "testtest";

WiFiServer server(80);

const char* urlPart = "/channels/106748/fields/1/last.json";

void setup(){
	Serial.begin(115200);
	WiFi.begin(ssid,password);
	ServerManager::getInstance()->setWiFiServer(&server);
}
String jsonStr = "";
void loop(){
	delay(1000);

	ServerManager::getInstance()->setHosting("api.thingspeak.com",80);
	ServerManager::getInstance()->get(urlPart,&jsonStr);
	//ServerManager::get(urlPart);
	
	Serial.print("data is ");
	Serial.println(jsonStr);
}