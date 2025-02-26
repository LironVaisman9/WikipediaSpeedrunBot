#pragma once
#include <iostream>
#include <vector>
#include "PriorityThreadManager.h"


struct WikiData
{
	std::vector<std::string> pathsToReuslt;
};
struct FuncStruct
{
    FuncStruct() = default;
    FuncStruct(PriorityThreadManager* threadManager, const int thisId, const std::vector<int>& idsChain, const int priority) :
        idsChain(idsChain),
        priority(priority)
    {
        this->idsChain.emplace_back(thisId);
        this->threadManager = threadManager;
    }

    PriorityThreadManager* threadManager;
    std::vector<int> idsChain;
    int priority;
};