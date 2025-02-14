#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

std::unordered_set<std::string> get_hrefs(std::stringstream& strStream)
{
    std::unordered_set<std::string> hrefs;

    std::string curWord;
    
    constexpr size_t hrefOffset = sizeof("href=\"/wiki/") / sizeof(char) - 1;

    while (strStream >> curWord)
    {
        if (curWord.size() > hrefOffset && // href can exist
            curWord.rfind("href=\"/wiki/", 0) == 0 && // starts with href="wiki/
            curWord.find(':', hrefOffset) == std::string::npos && 
            curWord.find('.', hrefOffset) == std::string::npos) // searches :
        {
            size_t delimeter = curWord.find_first_of("\"#", hrefOffset);
            hrefs.emplace(std::move(curWord.substr(hrefOffset, delimeter - hrefOffset)));
        }
    }

    return hrefs;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::stringstream* buffer) 
{
    size_t totalSize = size * nmemb;
    *buffer << std::string((char*)contents, totalSize);
    return totalSize;
}

int main() 
{
    CURL* curl = curl_easy_init();

    if (curl) 
    {
        std::stringstream bufferData;
        
        // HTTP request
        curl_easy_setopt(curl, CURLOPT_URL, "http://en.wikipedia.org/wiki/Germany"); 
        
        // Follow redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  
        
        // Use a write callback to write to `response`
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bufferData);
        
        // Force HTTP/1.1
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1); 

        // Disable SSL certificate verification
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Get result of operation
        CURLcode res = curl_easy_perform(curl);

        
        if (res != CURLE_OK) 
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else 
        {
            std::unordered_set<std::string> hrefs = get_hrefs(bufferData);
            std::cout << "size: " << hrefs.size() << std::endl;
            for (const std::string& href : hrefs)
            {
                std::cout << href << std::endl;
            }

            std::ofstream file("sample.html");
            file << bufferData.str();
            
            std::cout << "Successfull operation!";
        }

        curl_easy_cleanup(curl);
    }
    else 
    {
        std::cerr << "Failed to initialize cURL.\n";
    }

    return 0;
}
