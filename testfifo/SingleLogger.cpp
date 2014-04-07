#include "SingleLogger.h"
#include <sstream>
#include <time.h>
#include <iomanip>

SingleLogger* SingleLogger::self_ = NULL;
unsigned int SingleLogger::refcount_ = 0;
pthread_mutex_t SingleLogger::logMutex_;
std::fstream SingleLogger::logFile_;

SingleLogger* SingleLogger::InitLogger(const char* logFile) 
{
    if (self_ == NULL) 
    {
        self_ = new SingleLogger();
        pthread_mutex_init(&logMutex_, NULL);    
        logFile_.open(logFile, std::fstream::out | std::fstream::app | std::fstream::binary);
    }
    
    refcount_++;
    return self_;
}

void SingleLogger::FreeLogger()
{
    --refcount_; 
    if(!refcount_) 
    {
        pthread_mutex_destroy(&logMutex_);
        logFile_.close();
        delete this; 
        self_= NULL;
    }
}

void SingleLogger::logMessage(eMessageType etype, const char* message)
{
    const std::string msgType[] = {"INFO", "WARNING", "EEROR"};
    
    struct tm *currentLt;
    time_t currentUtc;
    time(&currentUtc);
    currentLt = localtime(&currentUtc);
    
    std::ostringstream formattedTime;
    formattedTime<<currentLt->tm_year + 1900<<"-"<<
            std::setfill('0')<< std::setw(2)<<currentLt->tm_mon + 1<<"-"<<
            std::setfill('0')<< std::setw(2)<<currentLt->tm_mday<<" "<<
            std::setfill('0')<< std::setw(2)<<currentLt->tm_hour<<":"<<
            std::setfill('0')<< std::setw(2)<<currentLt->tm_min<<":"<<
            std::setfill('0')<< std::setw(2)<<currentLt->tm_sec<<": ";
    
    std::string fullMessage(formattedTime.str());
    fullMessage.append(msgType[etype] + ": ");
    fullMessage.append(message);
    
    pthread_mutex_lock(&logMutex_);
    if(logFile_.is_open())
    {
        logFile_<<fullMessage<<"\r\n";
        logFile_.flush();
    }
    pthread_mutex_unlock(&logMutex_);
}
