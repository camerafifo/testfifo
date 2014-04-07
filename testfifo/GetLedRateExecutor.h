/* 
 * File:   GetLedRateExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:20 PM
 */

#ifndef GETLEDRATEEXECUTOR_H
#define	GETLEDRATEEXECUTOR_H
#include "ResponseExecutor.h"

class GetLedRateExecutor : public ResponseExecutor
{
public:
    
    GetLedRateExecutor(unsigned int uniqueId);
    virtual bool executeResponse(std::string& responseInfo);
};


#endif	/* GETLEDRATEEXECUTOR_H */

