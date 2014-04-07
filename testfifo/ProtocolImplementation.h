/* 
 * File:   ProtocolImplementation.h
 * Author: dmitriy
 *
 * Created on 3 Апрель 2014 г., 23:59
 */

#ifndef PROTOCOLIMPLEMENTATION_H
#define	PROTOCOLIMPLEMENTATION_H

#include <string>


class ExecutorFactory;
class ResponseExecutor;
class SingleLogger;
class CameraRegister;

//realization of protocol logic
class ProtocolImplementation
{
private:
    SingleLogger* logger_;
    std::string fifoName_;
    bool bThreaded_;
    ExecutorFactory* executorFactory_;
    ResponseExecutor* constructExecutor(unsigned int uniqueId, const std::string& command);
    CameraRegister* camRegister_;

public:
    ProtocolImplementation();
    ~ProtocolImplementation();
    ResponseExecutor* initResponseExecutor(unsigned int uniqueId);
    void closeClientResponse(unsigned int uniqueId);
    void sendResponseInfo(unsigned int uniqueId, const std::string& info);
};

#endif	/* PROTOCOLIMPLEMENTATION_H */

