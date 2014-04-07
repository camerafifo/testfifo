/* 
 * File:   SingleLogger.h
 * Author: dmitriy
 *
 * Created on 6 Апрель 2014 г., 2:38
 */

#ifndef SINGLELOGGER_H
#define	SINGLELOGGER_H
#include <mutex>
#include <fstream>
#include <atomic>

//logger, realised as a singleton
class SingleLogger
{
private:
     SingleLogger(){};
    ~SingleLogger(){};
    
    SingleLogger(const SingleLogger& logger); 
    SingleLogger& operator=(SingleLogger& logger);
    
    static SingleLogger* self_;
    static unsigned int refcount_;
    static pthread_mutex_t logMutex_;
    static std::fstream logFile_;
    
public:
    enum eMessageType {INFO = 0, WARNING, ERROR};
    static SingleLogger* InitLogger(const char* logPath = NULL);
    void FreeLogger();
    void logMessage(eMessageType etype, const char* message);
};

#endif	/* SINGLELOGGER_H */

