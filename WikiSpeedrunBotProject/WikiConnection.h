#pragma once

#include <iostream>

class WikiConnection
{
private:
	std::string _pageName;
	bool _connected;
public:
	WikiConnection();
	WikiConnection(std::string pageName);
	std::string getPageName() const;
	bool isConnected() const;
	void getLinks(); //Replace void with the data structure that we will use for the links
	~WikiConnection();
};

