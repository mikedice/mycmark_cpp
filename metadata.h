#ifndef __metadata_h__
#define __metadata_h__

#include <string>

class Metadata
{
private:
    std::string friendlyName;
    std::string publishDate;
    bool isValid;
public:
    std::string getFriendlyName();
    std::string getPublishDate();
    bool getIsValid();

    Metadata(const char* blob, size_t len);
};

#endif