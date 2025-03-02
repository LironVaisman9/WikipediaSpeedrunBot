#include "WikiApple.h"

void WikiApple::processPage(std::shared_ptr<paramStruct> params)
{
	if (params->priority <= _endPageLevel)
	{
		std::vector<std::string> pageLinks = _session.getPageLinks(params->pageName);
		for (auto& link : pageLinks)
		{
			if (link == _endPage)
			{
				std::string pathToEnd = idChainToString(params->idsChain);
				pathToEnd += "->";
				pathToEnd += link;
				_pathsToReuslt.emplace_back(pathToEnd);
			}
			else
			{
				int id = 0;//Replace with code that finds the ID using the string name
				std::shared_ptr<paramStruct> param = std::make_shared<paramStruct>(params->threadManager, id, params->idsChain, params->priority + 1, link);
				params->threadManager->addTask(
					[this](std::shared_ptr<void> data)
					{
						std::shared_ptr<paramStruct> param = std::static_pointer_cast<paramStruct>(data);
						this->processPage(param);
					},
					param->priority, param);
			}
		}
	}
}

std::string WikiApple::idChainToString(std::vector<int> idChain)
{
	std::string pathToEndPage;
	for (auto& id : idChain)
	{
		std::string pageName = ""; //Replace with function that finds the page name from its id
		pathToEndPage += pageName;
		pathToEndPage += "->";
	}
	return pathToEndPage.substr(0,pathToEndPage.length() - 2);
}

WikiApple::WikiApple()
{
	_session;
	_endPage = "";
	_endPageLevel = 10;
}

WikiApple::~WikiApple()
{
}

std::vector<std::string> WikiApple::scrapWikipedia(const std::string& startPage, const std::string& endPage)
{
	_endPage = endPage;
	int id = 0;//Replace with code that finds the ID using the string name
	std::vector<int> idsChain;
	PriorityThreadManager* threadManager = new PriorityThreadManager();
	std::shared_ptr<paramStruct> param = std::make_shared<paramStruct>(threadManager, id,idsChain,0,startPage);
	processPage(param);
	return _pathsToReuslt;
}
