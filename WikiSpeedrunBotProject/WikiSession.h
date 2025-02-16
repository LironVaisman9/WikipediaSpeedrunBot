#pragma once

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <fstream>
#include <sstream>

#define PAGE_DOESNT_EXIST "Wikipedia does not have an article with this exact name"

class WikiSession
{
private:
	CURL* _curl;
	std::stringstream _bufferData;
public:
	WikiSession();
	void sendHttpRequest(const std::string& pageName);
	std::vector<std::string> getLinks();
	~WikiSession();
};

