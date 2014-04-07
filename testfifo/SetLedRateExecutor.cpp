#include <sstream>
#include "SetLedRateExecutor.h"
#include "CameraRegister.h"
#include <vector>
#include <algorithm>

SetLedRateExecutor::SetLedRateExecutor(unsigned int uniqueId)
: ResponseExecutor(uniqueId)
{
    nArguments_ = 1;
    std::list<std::string> firstArgValues;
    firstArgValues.push_back("0");
    firstArgValues.push_back("1");
    firstArgValues.push_back("2");
    firstArgValues.push_back("3");
    firstArgValues.push_back("4");
    firstArgValues.push_back("5");
    
    argumentValueSet_.insert(std::make_pair(0, firstArgValues));
}


bool SetLedRateExecutor::executeResponse(std::string& responseInfo)
{
    bool bValid = validatePassedArguments();
    if(bValid)
    	bValid = camRegister_->setVaue("rate", argString_.c_str());
    responseInfo = bValid ? successMsg_ : failureMsg_;
    return bValid;
}


