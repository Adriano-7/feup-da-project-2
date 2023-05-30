#include "ReadTime.h"
#include <fstream>
#include <chrono>

double ReadTime::estimateReadTime(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return -1;  // Return -1 if the file cannot be opened
    }

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    double averageReadTime = elapsedTime.count() / lineCount;

    file.close();
    return averageReadTime * lineCount;
}

double ReadTime::realOpenTime(const std::string& filename) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    std::ifstream file(filename);
    if (!file.is_open()) {
        return -1;  // Return -1 if the file cannot be opened
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    double openTime = elapsedTime.count();

    file.close();
    return openTime;
}