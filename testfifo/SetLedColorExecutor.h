/* 
 * File:   SetLedColorExecutor.h
 * Author: qwerty
 *
 * Created on April 4, 2014, 5:22 PM
 */

#ifndef SETLEDCOLOREXECUTOR_H
#define	SETLEDCOLOREXECUTOR_H
#include "ResponseExecutor.h"

class SetLedColorExecutor : public ResponseExecutor
{
//private:
//    unsigned int nArguments_;
//    std::map<unsigned int, std::list<std::string> > argumentValueSet_;
//    std::string argString_;   
    
public:
    SetLedColorExecutor(unsigned int uniqueId);
    virtual bool executeResponse(std::string& responseInfo);
};



#endif	/* SETLEDCOLOREXECUTOR_H */

