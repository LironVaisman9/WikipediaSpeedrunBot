#pragma once
#include <iostream>
#include <vector>
#include "WikiStructs.h"
#include "WikiSession.h"

class WikiApple
{
private:
	WikiSession _session;
	std::vector<std::string> _pathsToReuslt;
	std::string _endPage;
	int _endPageLevel;
private:
	void processPage(std::shared_ptr<paramStruct> params);
	std::string idChainToString(std::vector<int> idChain);
public:
	WikiApple();
	~WikiApple();

	std::vector<std::string> scrapWikipedia(const std::string& startPage,const std::string& endPage);
};


