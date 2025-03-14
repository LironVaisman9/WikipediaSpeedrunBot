#pragma once
#include <iostream>
#include <vector>
#include "PriorityThreadManager.h"


struct WikiData
{
	std::vector<std::string> pathsToReuslt;
};
struct ParamStruct
{
    ParamStruct() = default;
    ParamStruct(PriorityThreadManager* threadManager, const int thisId, const std::vector<int>& idsChain, const int priority,const std::string& pageName) :
        idsChain(idsChain),
        priority(priority),
        pageName(pageName)
    {
        this->idsChain.emplace_back(thisId);
        this->threadManager = threadManager;
    }

    PriorityThreadManager* threadManager;
    std::vector<int> idsChain;
    int priority;
    std::string pageName;
};