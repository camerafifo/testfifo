/* 
 * File:   InvalidExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:20 PM
 */

#ifndef INVALIDEXECUTOR_H
#define	INVALIDEXECUTOR_H

#include "ResponseExecutor.h"

class InvalidExecutor : public ResponseExecutor
{
public:
    InvalidExecutor(unsigned int uniqueId);
    virtual bool executeResponse(std::string& responseInfo);
};

#endif	/* INVALIDEXECUTOR_H */

