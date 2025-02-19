#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <ctime>
#include "WikiSession.h"
#include "Timer.h"


int main() 
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
    std::vector<std::string> chinaHrefs= session.getPageLinks("China");
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

    return 0;
}
