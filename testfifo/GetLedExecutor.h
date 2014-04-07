/* 
 * File:   GetLedExecutor.h
 * Author: dmitriy
 *
 * Created on 5 Апрель 2014 г., 10:00
 */

#ifndef GETLEDEXECUTOR_H
#define	GETLEDEXECUTOR_H
#include "ResponseExecutor.h"

class GetLedExecutor : public ResponseExecutor
{
private:
    std::map<unsigned int, std::list<std::string> > argumentValueSet_;
    std::string arguments;
public:
    GetLedExecutor(unsigned int uniqueId, const char* arg);
    virtual bool executeResponse(std::string& responseInfo);
};

#endif	/* GETLEDEXECUTOR_H */

