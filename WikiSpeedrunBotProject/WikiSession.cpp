#include "WikiSession.h"
#include <stdexcept>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::stringstream* buffer)
{
    size_t totalSize = size * nmemb;
    buffer->write(static_cast<char*>(contents), totalSize);
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
    // Send wiki page request
    
    _bufferData = std::stringstream();
    // Set URL for pageName
    std::string url = "http://en.wikipedia.org/wiki/" + pageName;
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    
    // Send request
    CURLcode res = curl_easy_perform(_curl);
    
    // Invalid request
    if (res != CURLE_OK)
    {
        throw std::runtime_error("Error: http request failed: " + std::string(curl_easy_strerror(res)));
    }

    // Invalid page
    std::string content = _bufferData.str();  
    if (content.find(PAGE_DOESNT_EXIST) != std::string::npos) 
    {
        throw std::runtime_error("Error: Wikipedia page '" + pageName + "' does not exist");
    }
}

std::vector<std::string> WikiSession::bufferToLinks()
{
    std::vector<std::string> links;
    std::string page = _bufferData.str();

    size_t pos = 0;

    constexpr size_t hrefOffset = sizeof("href=\"/wiki/") / sizeof(char) - 1;

    while ((pos = page.find("href=\"/wiki/", pos)) != std::string::npos)
    {
        pos += hrefOffset;
        // Link must end in # or " (example: href="/wiki/Methanol_toxicity", end in " after toxicity)
        size_t delimiter = page.find_first_of("\"#", pos);

        if (delimiter == std::string::npos)
        {
            // Shouldn't happen if happens an internal error exists..
            throw std::runtime_error("Internal error: No delimiter found for href.");
        }

        // Extract link from page pos
        std::string link = page.substr(pos, delimiter - pos);

        // Add to the links
        links.push_back(std::move(link));
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

std::vector<std::string> WikiSession::getPageLinks(const std::string& pageName)
{
    sendHttpRequest(pageName);
    return bufferToLinks();
}
