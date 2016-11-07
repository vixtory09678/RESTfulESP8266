#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <ESP8266WiFi.h>

class ServerManager
{
private:
	ServerManager();
	static ServerManager* instance;

	WiFiServer *server;
    int readResponse(String*);
    void write(const char*);
    const char* host;
    int port;
    int num_headers;
    const char* headers[10];
	const char* contentType;

public:
	static ServerManager* getInstance();

	//Generic HTTP Request
    int request(const char* method, const char* path,
                const char* body, String* response);

	// GET path
    int get(const char*);
    // GET path and response
    int get(const char*, String*);

    // POST path and body
    int post(const char* path, const char* body);
    // POST path and body and response
    int post(const char* path, const char* body, String*);

    // PUT path and body
    int put(const char* path, const char* body);
    // PUT path and body and response
    int put(const char* path, const char* body, String*);

    // DELETE path
    int del(const char*);
    // DELETE path and body
    int del(const char*, const char*);
    // DELETE path and response
    int del(const char*, String*);
    // DELETE path and body and response
    int del(const char*, const char*, String*);

    void setHosting(char* host,int port = 80);
    void setContentType(char*);
    void setWiFiServer(WiFiServer *server);

};

#endif