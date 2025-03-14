#include "WikiApple.h"
#include <sstream>

void WikiApple::processPage(std::shared_ptr<ParamStruct> params, const unsigned int threadID)
{
	if (params->priority > _endPageLevel)
	{
		std::cout << "\n\n\n\nFOUND PAGE\n\n\n";
		return;
	}

	std::stringstream strStream;
	strStream << "At depth: " << params->priority << " thread: #" << threadID << " | " << params->pageName << std::endl;
	std::cout << strStream.rdbuf();

	std::unordered_set<std::string> pageLinks = _sessions[threadID]->getPageLinks(params->pageName);

	for (const auto& link : pageLinks)
	{
		if (_usedPages.find(link) != _usedPages.end())
		{
			continue;
		}

		_usedPages.insert(link);

		if (link != _endPage)
		{
			int id = 0;//Replace with code that finds the ID using the string name
			std::shared_ptr<ParamStruct> newParams = std::make_shared<ParamStruct>(
				params->threadManager, 
				id, 
				params->idsChain, 
				params->priority + 1,
				link
			);

			params->threadManager->addTask(
				[&](std::shared_ptr<void> data, const unsigned int threadID)
				{
					std::shared_ptr<ParamStruct> curParams = std::static_pointer_cast<ParamStruct>(data);
					

					this->processPage(curParams, threadID);
				},
				newParams->priority, 
				newParams
			);
		}
		else
		{
			// Set end path
			std::string pathToEnd = idChainToString(params->idsChain);

			pathToEnd += "->";
			pathToEnd += link;

			_pathsToResult.emplace_back(pathToEnd);
			
			return;
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
	_sessions.resize(std::thread::hardware_concurrency());
	for (size_t i = 0; i < _sessions.size(); i++)
	{
		_sessions[i] = std::make_unique<WikiSession>();
	}


	_endPage = "";

	_endPageLevel = 10;
}

WikiApple::~WikiApple()
{
}

std::vector<std::string> WikiApple::scrapWikipedia(const std::string& startPage, const std::string& endPage)
{
	_endPage = endPage;
	_endPageLevel = 10;

	int id = 0;//Replace with code that finds the ID using the string name
	std::vector<int> idsChain;
	PriorityThreadManager* threadManager = new PriorityThreadManager();
	
	std::shared_ptr<ParamStruct> param = std::make_shared<ParamStruct>(threadManager, id, idsChain,0,startPage);
	_usedPages.insert(startPage);
	processPage(param, 0);

	std::this_thread::sleep_for(std::chrono::seconds(1000));

	return _pathsToResult;
}
