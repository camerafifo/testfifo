/* 
 * File:   GetLedColorExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:19 PM
 */

#ifndef GETLEDCOLOREXECUTOR_H
#define	GETLEDCOLOREXECUTOR_H

#include "ResponseExecutor.h"

class GetLedColorExecutor : public ResponseExecutor
{
public:
    GetLedColorExecutor(unsigned int uniqueId);
    virtual bool executeResponse(std::string& responseInfo);
};

#endif	/* GETLEDCOLOREXECUTOR_H */

