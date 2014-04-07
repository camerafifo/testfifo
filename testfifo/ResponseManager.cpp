#include <limits.h>
#include <algorithm>
#include "ProtocolImplementation.h"
#include "ResponseExecutor.h"
#include "ResponseManager.h"
#include "SingleLogger.h"
#include <unistd.h>

ResponseManager::ResponseManager()
: protocolImp_(new ProtocolImplementation())
{
    pthread_mutex_init(&taskMutex_, NULL);
    logger_ = SingleLogger::InitLogger();
}

ResponseManager::~ResponseManager()
{
    //terminate all responses and their threads, 
    //that hasn't been executed yet
    while(!requestQueue_.empty())
    {
        pthread_mutex_lock(&taskMutex_);
        auto element = requestQueue_.front();
        requestQueue_.pop();
        pthread_mutex_unlock(&taskMutex_);
        pthread_cancel(element.first);
        protocolImp_->closeClientResponse(element.second->getReponseId());
    }   
    pthread_mutex_destroy(&taskMutex_);
    logger_->FreeLogger();
    delete protocolImp_;
}

void ResponseManager::processRequest(unsigned int requestId)
{
    pthread_t currentThread = 0;
    
    //create new thread to process added response
    pthread_mutex_lock(&taskMutex_);    
    if(pthread_create(&currentThread, NULL, executeRequestTask, this) == 0)
    {        
        //requestQueue_.push(std::make_pair(currentThread, executor));
        requestQueueId_.push(requestId);
        requestId = requestQueueId_.front();
    }
    pthread_mutex_unlock(&taskMutex_);        
}

void* ResponseManager::executeRequestTask(void* object)
{
    ResponseManager* responseMng = reinterpret_cast<ResponseManager*>(object);
    responseMng->executeTask();
}

void ResponseManager::executeTask()
{    
    //get response id
    pthread_mutex_lock(&taskMutex_);
    unsigned int requestId = requestQueueId_.front();
    requestQueueId_.pop();
    pthread_mutex_unlock(&taskMutex_);
    
    //init response executor
    ResponseExecutor* currentExecutor = protocolImp_->initResponseExecutor(requestId);    
    pthread_mutex_lock(&taskMutex_);
    requestQueue_.push(std::make_pair(pthread_self(), currentExecutor));
    pthread_mutex_unlock(&taskMutex_);
    unsigned int taskId = currentExecutor->getReponseId();
    std::string info;
    std::string message(std::to_string(taskId));
    //process response
    currentExecutor->executeResponse(info);
    message.append(": " + info);
    //and send service answer to client
    protocolImp_->sendResponseInfo(taskId, info);
    delete currentExecutor;
    logger_->logMessage(SingleLogger::INFO, message.c_str());
    
    //delete executed task
    pthread_mutex_lock(&taskMutex_);
    requestQueue_.pop();
    pthread_mutex_unlock(&taskMutex_);
}

