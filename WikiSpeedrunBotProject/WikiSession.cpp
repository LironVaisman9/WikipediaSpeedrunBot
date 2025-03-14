#include "WikiSession.h"
#include <stdexcept>
#include <filesystem>
#include <fstream>

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}


size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* buffer)
{
    size_t totalSize = size * nmemb;
    *buffer += std::string(static_cast<char*>(contents), totalSize);
    return totalSize;
}
/// <summary>
/// C'tor of the wiki session class
/// Initializes curl to 1.1 http
/// </summary>
WikiSession::WikiSession()
{
    _curl = curl_easy_init();
    if (!_curl)
    {
        throw std::runtime_error("Error: Failed to initialize CURL");
    }

    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 10L);

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
/// <summary>
/// Sends a http request to a wikipedia page
/// and saves the html in the buffer 
/// </summary>
/// <param name="pageName">The wikipedia page to scrap</param>
void WikiSession::sendHttpRequest(const std::string& pageName)
{
    if (!_curl)
    {
        throw std::runtime_error("Error: CURL session is not initialized");
    }
    // Send wiki page request
    _bufferData = "";

    // Set URL for pageName
    std::string url = "http://en.wikipedia.org/wiki/" + pageName;
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 10L);

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
    
    // Send request
    CURLcode res = curl_easy_perform(_curl);
    // Invalid request
    if (res != CURLE_OK)
    {
        throw std::runtime_error("Error: http request failed: " + std::string(curl_easy_strerror(res)) + "\nurl: " + url);
    }
    // Invalid page
    std::string content = _bufferData;  
    if (content.find(PAGE_DOESNT_EXIST) != std::string::npos) 
    {
        throw std::runtime_error("Error: Wikipedia page '" + pageName + "' does not exist");
    }
}
/// <summary>
/// Gets all of the href links from the buffer
/// </summary>
/// <returns>Set of the href links</returns>
std::unordered_set<std::string> WikiSession::bufferToLinks() const
{
    std::unordered_set<std::string> links;
    std::string page = _bufferData;
    size_t pos = 0;
    constexpr size_t hrefOffset = sizeof("href=\"/wiki/") / sizeof(char) - 1;
    constexpr size_t notesOffset = sizeof("<h2 id=\"See_also\">See also</h2>") / sizeof(char) - 1;

    size_t breakPos = page.find("<h2 id=\"See_also\">See also</h2>");
    if (breakPos == std::string::npos)
    {
        breakPos = page.find("<h2 id=\"References\">References</h2>");
    }
    if (breakPos == std::string::npos)
    {
        throw std::runtime_error("Page should have `See_also` section");
    }

    while (pos < breakPos)
    {
        pos = page.find("href=\"/wiki/", pos);
        if (pos == std::string::npos)
        {
            break;
        }

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

        if (startsWith(link, "Wikipedia:") || startsWith(link, "Special:") || link == "Main_Page" || link.find_first_of(":") != std::string::npos)
        {
            continue;
        }

        // Add to the links
        links.emplace(std::move(link));
    }
    return links;
}

void WikiSession::saveBufferAsHtml(const std::string& filePath) const
{
    std::ofstream outFile(filePath);
    if (!outFile)
    {
        throw std::runtime_error("Internal error: could not open file in: " + filePath);
    }
    outFile << _bufferData;
    outFile.close();
}

WikiSession::~WikiSession()
{
    std::cout << "Destory CURL: " << _curl << std::endl;
    if (_curl != nullptr)
    {
        curl_easy_cleanup(_curl);
        _curl = nullptr;
    }
}

std::unordered_set<std::string> WikiSession::getPageLinks(const std::string& pageName)
{
    try
    {
        sendHttpRequest(pageName);
    }
    catch (std::exception& ex)
    {
        std::string err = ex.what() + '\n';
        std::cout << err;
        return {};
    }
    return bufferToLinks();
}

void WikiSession::saveHtmlLocally(const std::string& pageName, const std::string& filePath)
{
    std::string path = filePath + "/" + pageName + ".html"; 

    try
    {
        sendHttpRequest(pageName);
    }
    catch (std::exception& ex)
    {
        std::string err = ex.what() + '\n';
        std::cout << err;
        return;
    }
    saveBufferAsHtml(path);
}
