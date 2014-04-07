#include "SetLedColorExecutor.h"
#include "CameraRegister.h"

SetLedColorExecutor::SetLedColorExecutor(unsigned int uniqueId)
: ResponseExecutor(uniqueId)
{
    nArguments_ = 1;
    std::list<std::string> firstArgValues;
    firstArgValues.push_back("red");
    firstArgValues.push_back("green");
    firstArgValues.push_back("blue");
    
    argumentValueSet_.insert(std::make_pair(0, firstArgValues));
}

bool SetLedColorExecutor::executeResponse(std::string& responseInfo)
{
    bool bValid = validatePassedArguments();
    if(bValid)	    
    	bValid = camRegister_->setVaue("color", argString_.c_str());
    responseInfo = bValid ? successMsg_ : failureMsg_;
    return bValid;
}

