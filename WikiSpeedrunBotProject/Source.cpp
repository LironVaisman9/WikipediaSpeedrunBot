#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <ctime>
#include "WikiSession.h"


int main() 
{
    WikiSession* session = new WikiSession();
    clock_t start_time = clock();
    session->sendHttpRequest("Israel");
    std::vector<std::string> hrefs = session->getLinks();
    clock_t end_time = clock();
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    for (const std::string& href : hrefs)
    {
        std::cout << href << std::endl;
    }

    std::cout << "-------------------------------------------" << std::endl;

    clock_t start_time2 = clock();
    session->sendHttpRequest("Russia");
    std::vector<std::string> hrefs2 = session->getLinks();
    clock_t end_time2 = clock();
    double time_taken2 = double(end_time2 - start_time2) / CLOCKS_PER_SEC;
    for (const std::string& href : hrefs2)
    {
        std::cout << href << std::endl;
    }

    std::cout << "-------------------------------------------" << std::endl;

    clock_t start_time3 = clock();
    session->sendHttpRequest("China");
    std::vector<std::string> hrefs3 = session->getLinks();
    clock_t end_time3 = clock();
    double time_taken3 = double(end_time3 - start_time3) / CLOCKS_PER_SEC;
    for (const std::string& href : hrefs3)
    {
        std::cout << href << std::endl;
    }

    std::cout << "Israel size: " << hrefs.size() << std::endl;
    std::cout << "Israel time: " << time_taken << " seconds" << std::endl;

    std::cout << "Russia size: " << hrefs2.size() << std::endl;
    std::cout << "Russia time: " << time_taken2 << " seconds" << std::endl;

    std::cout << "China size: " << hrefs3.size() << std::endl;
    std::cout << "China time: " << time_taken2 << " seconds" << std::endl;

    return 0;
}
