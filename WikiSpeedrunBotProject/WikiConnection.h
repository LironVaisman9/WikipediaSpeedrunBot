#pragma once

#include <iostream>

class WikiConnection
{
private:
	std::string pageName;
	bool connected;
public:
	WikiConnection();
	WikiConnection(std::string pageName);
	bool isConnected();
	void getLinks(); //Replace void with the data structure that we will use for the links
	~WikiConnection();
};

