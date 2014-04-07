/* 
 * File:   ResponseExecutor.h
 * Author: dmitriy
 *
 * Created on 1 Апрель 2014 г., 23:34
 */

#ifndef RESPONSEEXECUTOR_H
#define	RESPONSEEXECUTOR_H
#include <string>
#include <map>
#include <list>

class CameraRegister;

//base class of response executors
class ResponseExecutor
{
protected:
    const unsigned int uniqueId_;
    unsigned int nArguments_;
    std::map<unsigned int, std::list<std::string> > argumentValueSet_;
    std::string argString_;
    static const std::string successMsg_;
    static const std::string failureMsg_;
    CameraRegister* camRegister_;
    
    bool validatePassedArguments();
public:
    ResponseExecutor(unsigned int uniqueId); 
    virtual ~ResponseExecutor();
    unsigned int getReponseId();
    void passArgs(const char* args);
    virtual bool executeResponse(std::string& responseInfo) = 0;
};


#endif	/* RESPONSEEXECUTOR_H */

