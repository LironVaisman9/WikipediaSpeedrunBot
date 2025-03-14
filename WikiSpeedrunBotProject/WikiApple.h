#pragma once
#include <iostream>
#include <vector>
#include "WikiStructs.h"
#include "WikiSession.h"

class WikiApple
{
public:
	WikiApple();
	~WikiApple();

	std::vector<std::string> scrapWikipedia(const std::string& startPage, const std::string& endPage);

private:

	std::vector<std::string> _pathsToResult;

	std::string _endPage;
	int _endPageLevel;
	std::unordered_set<std::string> _usedPages;

	std::vector<std::unique_ptr<WikiSession>> _sessions;

private:
	void processPage(std::shared_ptr<ParamStruct> params, const unsigned int threadID);
	std::string idChainToString(std::vector<int> idChain);
};


