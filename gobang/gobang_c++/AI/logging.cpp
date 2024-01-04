//
// Created by ycm on 2023/12/9.
//

#include "logging.h"

std::ofstream Logger::file;
char Logger::fileName[50]{};

Logger::Logger():level(static_cast<unsigned int>(logging::INFO)), loggerName("MainLogger") {
    Logger::initFile();
}

Logger::Logger(const char* name):level(static_cast<unsigned int>(logging::INFO)), loggerName(name) {
    Logger::initFile();
}

void Logger::initFile() {
    if(!Logger::file.is_open()){
        time_t lt1;
        tm *newTime;
        std::time( &lt1 );
        newTime=std::localtime(&lt1);
        std::strftime(Logger::fileName, 50, "./log/%Y%m%d.log", newTime);
//        Logger::file.open(Logger::fileName, std::ios::out | std::ios::app);
    }
}

Logger::~Logger() {
    Logger::file.close();
}

unsigned int Logger::getLevel() const {
    return this->level;
}

void Logger::setLevel(unsigned int Level) {
    this->level = Level;
}

void Logger::debug(const std::string& msg, unsigned int Level/*=static_cast<unsigned int>(logging::DEBUG)*/) {
    this->log(msg, Level);
}

void Logger::info(const std::string& msg, unsigned int Level/*=static_cast<unsigned int>(logging::INFO)*/) {
    this->log(msg, Level);
}

void Logger::warn(const std::string& msg, unsigned int Level/*=static_cast<unsigned int>(logging::WARN)*/) {
    this->log(msg, Level);
}

void Logger::error(const std::string& msg, unsigned int Level/*=static_cast<unsigned int>(logging::ERROR)*/) {
    this->log(msg, Level);
}

void Logger::fatal(const std::string& msg, unsigned int Level/*=static_cast<unsigned int>(logging::FATAL)*/) {
    this->log(msg, Level);
}

Logger::Logger(Logger &logger) {

}

void Logger::writeHead(unsigned int Level) {
    return;
    time_t lt1;
    tm *newTime;
    std::time( &lt1 );
    newTime=std::localtime(&lt1);
    char timeStr[50];
    std::strftime(timeStr, 50, "%Y-%m-%d %H:%M:%S", newTime);
    Logger::file << Level << "|" << timeStr << "|";
    if (Level <= (int) logging::DEBUG) {
        Logger::file << "DEBUG";
    } else if (Level <= (int) logging::INFO) {
        Logger::file << "INFO";
    } else if (Level <= (int) logging::WARN) {
        Logger::file << "WARN";
    } else if (Level <= (int) logging::ERROR) {
        Logger::file << "ERROR";
    } else if (Level <= (int) logging::FATAL) {
        Logger::file << "FATAL";
    } else {
        Logger::file << "UNKNOWN";
    }
    Logger::file << "|" << this->loggerName << ": ";
}

void Logger::log(const std::string &msg, unsigned int Level) {
    return;
    if(this->level <= Level){
        this->writeHead(Level);
        Logger::file << msg << std::endl;
    }
}
