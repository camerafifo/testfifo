/* 
 * File:   ResponseManager.h
 * Author: dmitriy
 *
 * Created on 4 Апрель 2014 г., 0:03
 */
#ifndef RESPONSEMANAGER_H
#define	RESPONSEMANAGER_H

#include <vector>
#include <pthread.h>
#include <queue>
#include <map>

class ProtocolImplementation;
class ResponseExecutor;
class SingleLogger;

//manager (i.e. dispatcher) of responses
class ResponseManager
{
private:
    pthread_mutex_t taskMutex_;    
    ProtocolImplementation* protocolImp_;
    std::queue<unsigned int> requestQueueId_;
    std::queue< std::pair<pthread_t, ResponseExecutor*> > requestQueue_;
    SingleLogger* logger_;
    static void* executeRequestTask(void* object); 
    void executeTask();

public:
    ResponseManager();
    ~ResponseManager();
    void processRequest(unsigned int requestId);
};


#endif	/* RESPONSEMANAGER_H */

