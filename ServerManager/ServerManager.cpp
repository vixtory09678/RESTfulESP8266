#include "ServerManager.h"

ServerManager* ServerManager::instance = NULL;

ServerManager::ServerManager(){
	contentType = "application/x-www-form-urlencoded";
	server = NULL;
}

ServerManager* ServerManager::getInstance(){
	if(!instance){
		instance = new ServerManager;
	}

	return instance;
}

void ServerManager::setHosting(char* host,int port){
	this->host = host;
	this->port = port;
}

void ServerManager::setWiFiServer(WiFiServer *server){
	this->server = server;
}

void ServerManager::setContentType(char* contentType){
	this->contentType = contentType;
}

//GET path
int ServerManager::get(const char* path){
	return request("GET",path,NULL,NULL);
}
//GET path with response
int ServerManager::get(const char* path, String* response){
	return request("GET",path,NULL,response);
}

// POST path and body
int ServerManager::post(const char* path, const char* body){
  return request("POST", path, body, NULL);
}

// POST path and body with response
int ServerManager::post(const char* path, const char* body, String* response){
  return request("POST", path, body, response);
}

// PUT path and body
int ServerManager::put(const char* path, const char* body){
  return request("PUT", path, body, NULL);
}

// PUT path and body with response
int ServerManager::put(const char* path, const char* body, String* response){
  return request("PUT", path, body, response);
}

// DELETE path
int ServerManager::del(const char* path){
  return request("DELETE", path, NULL, NULL);
}

// DELETE path and response
int ServerManager::del(const char* path, String* response){
  return request("DELETE", path, NULL, response);
}

// DELETE path and body
int ServerManager::del(const char* path, const char* body ){
  return request("DELETE", path, body, NULL);
}

// DELETE path and body with response
int ServerManager::del(const char* path, const char* body, String* response){
  return request("DELETE", path, body, response);
}

//Generic HTTP Request
int ServerManager::request(const char* method, const char* path,
                	const char* body, String* response){
	WiFiClient client = server->available();
	String rawData = "";

	if(client.connect(host,port)){
		String post = String(String(method)+" "+ String(path) +" HTTP/1.1\r\n" +
							"Host: " + String(host) + "\r\n" +
							"Connection: close\r\n");
		if(body != NULL){
      		char contentLength[30];
      		sprintf(contentLength, "Content-Length: %d\r\n", strlen(body));
      		post.concat(String(contentLength));
      		post.concat(String("Content-Type: " + String(contentType) + "\r\n"));
    	}

    	post.concat("\r\n");

    	if(body != NULL){
    		post.concat(String(String(body)+"\r\n\r\n"));
    	}
    	client.print(post); //sending request to server

    	delay(100); //Make sure you write all those bytes.
	
		//wait for response from server
    	while(!client.available()){

    	}

    	//read data loop
    	while(client.available()){
    		char c = (char)client.read();
    		if(response != NULL){
    			rawData.concat(c);
    		}
    	}

    	//get json string from response
    	if(rawData.indexOf("{") < 0){
    		*response = "empty";
    	}else{
    		*response = rawData.substring(rawData.indexOf("{"),
    									rawData.indexOf("}")+1);
    	}

    	client.stop(); // close comunicate
    	delay(50);
	}

	return 1;
}