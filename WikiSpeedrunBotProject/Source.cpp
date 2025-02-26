#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <ctime>
#include "PriorityThreadManager.h"
#include "WikiSession.h"
#include "Timer.h"


void sampleThing()
{

    WikiSession session;
    Timer timer;

    timer.start();
    std::vector<std::string> israelHrefs = session.getPageLinks("Israel");
    double timeTaken = timer.getDuration();

    std::cout << "Israel hrefs:\n=========================" << std::endl;
    for (const std::string& href : israelHrefs)
    {
        std::cout << href << std::endl;
    }

    std::cout << "-------------------------------------------" << std::endl;

    timer.start();
    std::vector<std::string> russiaHrefs = session.getPageLinks("Russia");
    double timeTaken2 = timer.getDuration();

    std::cout << "Russia hrefs:\n=========================" << std::endl;
    for (const std::string& href : russiaHrefs)
    {
        std::cout << href << std::endl;
    }

    std::cout << "-------------------------------------------" << std::endl;

    timer.start();
    std::vector<std::string> chinaHrefs = session.getPageLinks("China");
    double timeTaken3 = timer.getDuration();

    std::cout << "China hrefs:\n=========================" << std::endl;
    for (const std::string& href : chinaHrefs)
    {
        std::cout << href << std::endl;
    }

    std::cout << "Israel size: " << israelHrefs.size() << std::endl;
    std::cout << "Israel time: " << timeTaken << " microseconds" << std::endl;

    std::cout << "Russia size: " << russiaHrefs.size() << std::endl;
    std::cout << "Russia time: " << timeTaken2 << " microseconds" << std::endl;

    std::cout << "China size: " << chinaHrefs.size() << std::endl;
    std::cout << "China time: " << timeTaken3 << " microseconds" << std::endl;

    session.saveHtmlLocally("Israel", "C:\\Users\\453D~1\\Desktop");
}

//struct FuncStruct
//{
//    FuncStruct()
//    {
//        std::cout << __FUNCTION__ "Constructed default\n";
//    };
//    FuncStruct(PriorityThreadManager* threadManager, int value);
//
//    PriorityThreadManager* threadManager;
//    int value;
//};

//void printInt(std::shared_ptr <void> voidParam)
//{
//    std::shared_ptr<FuncStruct> param = std::static_pointer_cast<FuncStruct>(voidParam);
//
//    // After 5 times stop
//    if (param->value % 5 != 0)
//    {
//        std::cout << ("v: " + std::to_string(param->value) + "\n");
//        
//        std::shared_ptr<FuncStruct> newParam = std::make_shared<FuncStruct>(
//            param->threadManager,
//            param->value * 2
//        );
//
//        param->threadManager->addTask(
//            printInt, 
//            newParam->value % PriorityThreadManager::MAX_PRIORITIES_AMOUNT, 
//            newParam
//        );
//    }
//}

//void testThreadManager()
//{
//    PriorityThreadManager threadManager;
//
//    std::shared_ptr<FuncStruct> param1 = std::make_shared<FuncStruct>();
//    param1->threadManager = &threadManager;
//    param1->value = 12;
//    threadManager.addTask(printInt, 0, param1);
//
//    /*std::shared_ptr<FuncStruct> param2 = std::make_shared<FuncStruct>();
//    param2->threadManager = &threadManager;
//    param2->value = 4;
//    threadManager.addTask(printInt, 0, param2);
//
//    std::shared_ptr<FuncStruct> param3 = std::make_shared<FuncStruct>();
//    param3->threadManager = &threadManager;
//    param3->value = 2;
//    threadManager.addTask(printInt, 0, param3);*/
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//}

int main() 
{
    

    return 0;
}

//FuncStruct::FuncStruct(PriorityThreadManager* threadManager, int value)
//    : threadManager(threadManager), value(value)
//{}
