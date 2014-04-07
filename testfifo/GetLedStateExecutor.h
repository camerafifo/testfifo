/* 
 * File:   GetLedStateExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:18 PM
 */

#ifndef GETLEDSTATEEXECUTOR_H
#define	GETLEDSTATEEXECUTOR_H

#include "ResponseExecutor.h"

class GetLedStateExecutor : public ResponseExecutor
{
public:
    
    GetLedStateExecutor(unsigned int uniqueId);
    bool executeResponse(std::string& responseInfo);
};

#endif	/* GETLEDSTATEEXECUTOR_H */

