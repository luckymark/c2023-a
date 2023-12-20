//
// Created by ycm on 2023/12/9.
//

#ifndef GOBANG_LOGGING_H
#define GOBANG_LOGGING_H

#include <fstream>
#include <string>
#include <ctime>

enum class logging {
    DEBUG = 10,
    INFO = 30,
    WARN = 50,
    ERROR = 70,
    FATAL = 90
};

class Logger {
public:
    Logger();

    explicit Logger(const char* loggerName);

    Logger(Logger &logger);

    ~Logger();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "modernize-use-nodiscard"
    unsigned int getLevel() const;
#pragma clang diagnostic pop

    void setLevel(unsigned int Level);

    void debug(const std::string& msg, unsigned int Level=static_cast<unsigned int>(logging::DEBUG));

    void info(const std::string& msg, unsigned int Level=static_cast<unsigned int>(logging::INFO));

    void warn(const std::string& msg, unsigned int Level=static_cast<unsigned int>(logging::WARN));

    void error(const std::string& msg, unsigned int Level=static_cast<unsigned int>(logging::ERROR));

    void fatal(const std::string& msg, unsigned int Level=static_cast<unsigned int>(logging::FATAL));

protected:
    unsigned int level{};
    static std::ofstream file;
    static char fileName[50];
    std::string loggerName{};

    void writeHead(unsigned int Level);
    void log(const std::string& msg, unsigned int Level);
    static void initFile();
};

#endif //GOBANG_LOGGING_H
