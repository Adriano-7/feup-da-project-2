#ifndef FILECOUNTER_H
#define FILECOUNTER_H

#include <string>

class ReadTime {
public:
    double estimateReadTime(const std::string& filename);
    double realOpenTime(const std::string& filename);
};

#endif
