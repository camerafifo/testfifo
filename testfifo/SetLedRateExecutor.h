/* 
 * File:   SetLedRateExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:17 PM
 */

#ifndef SETLEDRATEEXECUTOR_H
#define	SETLEDRATEEXECUTOR_H
#include "ResponseExecutor.h"

class SetLedRateExecutor : public ResponseExecutor
{
//private:
//    unsigned int nArguments_;
//    std::map<unsigned int, std::list<std::string> > argumentValueSet_;
//    std::string argString_;
    
public:
    SetLedRateExecutor(unsigned int);
    virtual bool executeResponse(std::string& responseInfo);
};


#endif	/* SETLEDRATEEXECUTOR_H */

