/* 
 * File:   Handlers.h
 * Author: dmitriy
 *
 * Created on 6 Апрель 2014 г., 13:22
 */

#ifndef HANDLERS_H
#define	HANDLERS_H
#include "SingleLogger.h"

//daemon handlers
namespace Handlers
{
    void* releasedResource;
    std::string pidFileToDelete;
    
    void fatalSignalHandler(int sig)
    {
        SingleLogger* logger = SingleLogger::InitLogger();
        std::string message("caught signal: ");
        message.append(strsignal(sig));
        message.append(" - exiting");
        logger->logMessage(SingleLogger::ERROR, message.c_str());
        logger->FreeLogger();
        unlink(pidFileToDelete.c_str());
        _exit(0);
    }

    template<typename T>
    void terminationSignalHandler(int sig)
    {
        SingleLogger* logger = SingleLogger::InitLogger();
        std::string message("caught signal: ");
        message.append(strsignal(sig));
        message.append(" - exiting");
        logger->logMessage(SingleLogger::INFO, message.c_str());
        logger->FreeLogger();
        
        T* releasedObject = reinterpret_cast<T*>(releasedResource);
        delete releasedObject;
        releasedResource = NULL;
        unlink(pidFileToDelete.c_str());
        _exit(0);
    }
}
#endif	/* HANDLERS_H */

