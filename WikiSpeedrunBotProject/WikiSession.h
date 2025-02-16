#pragma once

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <fstream>
#include <sstream>

class WikiSession
{
private:
	CURL* _curl;
	std::stringstream _bufferData;
public:
	WikiSession();
	void sendHttpRequest(std::string pageName);
	std::vector<std::string> getLinks();
	//~WikiSession();
};

