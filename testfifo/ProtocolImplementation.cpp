#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <algorithm>
#include <limits.h>
#include "ProtocolImplementation.h"
#include "TestProtocolFactory.h"
#include "SingleLogger.h"
#include "CameraRegister.h"

ProtocolImplementation::ProtocolImplementation()
: bThreaded_(true)
, executorFactory_(new TestProtocolFactory())
{
    camRegister_ = CameraRegister::InitCameraRegister();
    
    char tempFileName[PATH_MAX + 1];
    memset(tempFileName, 0, PATH_MAX + 1);
    readlink("/proc/self/exe", tempFileName, PATH_MAX);
    fifoName_.assign(tempFileName);
    int slash = fifoName_.find_last_of("/");
    if(slash != 0 && slash != std::string::npos)
    {
        fifoName_.erase(slash);
        fifoName_.append("/cam_fifo");
    }
    else 
        fifoName_ = "/cam_fifo";    
         
    logger_ = SingleLogger::InitLogger();
}

ProtocolImplementation::~ProtocolImplementation()
{
    delete executorFactory_;
    camRegister_->FreeCamRegister();
    logger_->FreeLogger();
}

ResponseExecutor* ProtocolImplementation::initResponseExecutor(unsigned int uniqueId)
{
    int fifoRequest = -1;
    std::string fifoRequestName(fifoName_ + "." + std::to_string(uniqueId));
    
    //open and read task fifo 
    fifoRequest = open(fifoRequestName.c_str(), O_RDONLY);
    
    char command[1024];
    memset(command, 0, sizeof(command));

    if(!(fifoRequest < 0)) 
    {
        read(fifoRequest, command, sizeof (command));
        close(fifoRequest);
        return constructExecutor(uniqueId, std::string(command));
    }
}

void ProtocolImplementation::closeClientResponse(unsigned int uniqueId)
{
    
    int fifoRequest = -1;
    
    //send to a client whose request was not executed
    //that service starts termination
    std::string fifoRequestName(fifoName_ + "." + std::to_string(uniqueId));
    fifoRequest = open(fifoRequestName.c_str(), O_WRONLY);
    if (fifoRequest < 0)
        return;
    
    const std::string connectionErr = "CAMERA CONNECTION ERROR \r\n"; 
    
    ssize_t nsize = write(fifoRequest, connectionErr.c_str(), connectionErr.length());
    
    close(fifoRequest);
}

void ProtocolImplementation::sendResponseInfo(unsigned int uniqueId, const std::string& info)
{
    int fifoRequest = -1;
    std::string fifoRequestName(fifoName_ + "." + std::to_string(uniqueId));
    fifoRequest = open(fifoRequestName.c_str(), O_WRONLY);    
    std::string tmp(info + "\n");
    if(fifoRequest < 0) 
        return;
    
    //send to a client response message
    ssize_t nsize = write(fifoRequest, tmp.c_str(), tmp.length());

    close(fifoRequest);
}

ResponseExecutor* ProtocolImplementation::constructExecutor(unsigned int uniqueId, const std::string& command)
{
    //parse requst and init executor
    int space = command.find_first_of(' ');
    int endpos = command.find_last_of('\n');
    std::string responseType;
    std::string arguments;

    if(endpos != std::string::npos) 
    {
        if (space == std::string::npos)
            space = endpos;
        else 
        {
            int argLength = command.length() - strlen("\n") - space - 1;
            arguments.assign(command.c_str() + space + 1, argLength);
        }
    }
    
    responseType.assign(command.begin(), command.begin() + space);
    std::string logMessage(std::to_string(uniqueId) + ": " + command);    
    logger_->logMessage(SingleLogger::INFO, std::string(responseType + " " + arguments).c_str());
    
    ResponseExecutor* executor = executorFactory_->createExecutor(uniqueId, responseType.c_str());
    executor->passArgs(arguments.c_str());
    return executor;
}