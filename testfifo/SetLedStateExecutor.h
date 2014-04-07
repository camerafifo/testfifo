/* 
 * File:   SetLedStateExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:17 PM
 */

#ifndef SETLEDSTATEEXECUTOR_H
#define	SETLEDSTATEEXECUTOR_H
#include "ResponseExecutor.h"

class SetLedStateExecutor : public ResponseExecutor
{
//private:
//    unsigned int nArguments_;
//    std::map<unsigned int, std::list<std::string> > argumentValueSet_;
//    std::string argString_;
    
public:
    SetLedStateExecutor(unsigned int uniqueId);
    virtual bool executeResponse(std::string& responseInfo);
};


#endif	/* SETLEDSTATEEXECUTOR_H */

