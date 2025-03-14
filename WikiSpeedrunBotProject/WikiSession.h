#pragma once

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <unordered_set>

#define PAGE_DOESNT_EXIST "Wikipedia does not have an article with this exact name"

class WikiSession
{
public:
	WikiSession();
	~WikiSession();

	std::unordered_set<std::string> getPageLinks(const std::string& pageName);
	void saveHtmlLocally(const std::string& pageName,const std::string& filePath);

private:
	void sendHttpRequest(const std::string& pageName);
	std::unordered_set<std::string> bufferToLinks() const;
	void saveBufferAsHtml(const std::string& filePath) const;

private:
	CURL* _curl;
	std::string _bufferData;
};

