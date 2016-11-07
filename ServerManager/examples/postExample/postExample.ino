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
bool checkSend = false;

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  ServerManager::getInstance()->setWiFiServer(&server);
}
String jsonStr = "";
unsigned long timeDelay = 0;

void loop(){

  //get
  ServerManager::getInstance()->setHosting("api.thingspeak.com",80);
  if(millis() - timeDelay > 500){
    ServerManager::getInstance()->get(urlPart,&jsonStr);
    //ServerManager::getInstance()->get(urlPart);
  }
  

  //post
  String getValuetoSend = readFromSerial();
  if(checkSend && getValuetoSend.length() > 0){
    String send = "api_key=CQ0CIKNV5SONBQS3&field1="+getValuetoSend;
    ServerManager::getInstance()->post(send.c_str(),&jsonStr);
  }
    
  //Display
  Serial.print("data is ");
  Serial.println(jsonStr);
}

String readFromSerial(){
  String valueFromUser = "";
  while(Serial.available()){
    char r = Serial.read();
    if(r > 47 && r < 58){
      valueFromUser.concat(r);
    }else{
      if(r == '\n') checkSend = true;
    }
  }
  return valueFromUser;
}