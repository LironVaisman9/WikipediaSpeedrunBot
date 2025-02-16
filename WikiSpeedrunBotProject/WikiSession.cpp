#include "WikiSession.h"
#include <stdexcept>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::stringstream* buffer)
{
    size_t totalSize = size * nmemb;
    *buffer << std::string((char*)contents, totalSize);
    return totalSize;
}

WikiSession::WikiSession()
{
    _curl = curl_easy_init();
    if (!_curl)
    {
        throw std::runtime_error("Error: Failed to initialize CURL");
    }

    // Follow redirects
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Use a write callback to write to `response`
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_bufferData);

    // Force HTTP/1.1
    curl_easy_setopt(_curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

    // Disable SSL certificate verification
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);
}

void WikiSession::sendHttpRequest(const std::string& pageName)
{
    if (!_curl)
    {
        throw std::runtime_error("Error: CURL session is not initialized");
    }
    std::string url = "http://en.wikipedia.org/wiki/" + pageName;
    _bufferData.str("");
    _bufferData.clear();
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(_curl);
    if (res != CURLE_OK)
    {
        throw std::runtime_error("Error: http request failed: " + std::string(curl_easy_strerror(res)));
    }
    std::string content = _bufferData.str();  
    if (content.find(PAGE_DOESNT_EXIST) != std::string::npos) 
    {
        throw std::runtime_error("Error: Wikipedia page '" + pageName + "' does not exist");
    }
}

std::vector<std::string> WikiSession::getLinks()
{
    std::vector<std::string> links;
    std::string curWord;

    constexpr size_t hrefOffset = sizeof("href=\"/wiki/") / sizeof(char) - 1;

    while (_bufferData >> curWord)
    {
        if (curWord.size() > hrefOffset && // href can exist
            curWord.rfind("href=\"/wiki/", 0) == 0 && // starts with href="wiki/
            curWord.find(':', hrefOffset) == std::string::npos &&
            curWord.find('.', hrefOffset) == std::string::npos) // searches :
        {
            size_t delimeter = curWord.find_first_of("\"#", hrefOffset);
            links.push_back(std::move(curWord.substr(hrefOffset, delimeter - hrefOffset)));
        }
    }
    return links;
}

WikiSession::~WikiSession()
{
    if (_curl != nullptr)
    {
        curl_easy_cleanup(_curl);
    }
}
