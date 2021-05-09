#include "metadata.h"
#include <iostream>
#include <string>
#include <regex>

std::string Metadata::getFriendlyName()
{
    return this->friendlyName;
}

std::string Metadata::getPublishDate()
{
    return this->publishDate;
}

bool Metadata::getIsValid()
{
    return this->isValid;
}

Metadata::Metadata(const char* blob, size_t len)
{
    std::string input(blob, len);
    std::regex docMetadata("document\\-metadata", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex friendlyName("friendly\\-name\\:(.*)", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex publishDate("publish\\-date:(.*)", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::smatch matches;
    this->isValid = false;

    if (!std::regex_search(input, docMetadata))
    {
        return; // this isn't a metadata code blocl
    }

    this->isValid = true;

    if (std::regex_search(input, matches, friendlyName))
    {
        // std::cout << "metdata found match" << std::endl;
        // std::cout << "number of matches: " << matches.size() << std::endl;
        if (matches.length() > 1)
        {
            this->friendlyName = matches[1];
            matches.empty();
        }
    }
    else
    {
        std::cout << "metadata didn't find match for friendly name" << std::endl;
    }

    if (std::regex_search(input, matches, publishDate))
    {
        if (matches.length() > 1)
        {
            this->publishDate = matches[1];
            matches.empty();
        }
        else
        {
            std::cout << "metadata didn't find match for publish date" << std::endl;
        }
    }
}

