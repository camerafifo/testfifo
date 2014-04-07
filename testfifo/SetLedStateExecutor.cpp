#include "SetLedStateExecutor.h"
#include "CameraRegister.h"

SetLedStateExecutor::SetLedStateExecutor(unsigned int uniqueId)
        :ResponseExecutor(uniqueId)
{
    nArguments_ = 1;
    std::list<std::string> firstArgValues;
    firstArgValues.push_back("on");
    firstArgValues.push_back("off");
    
    argumentValueSet_.insert(std::make_pair(0, firstArgValues));
}

bool SetLedStateExecutor::executeResponse(std::string& responseInfo)
{
    bool bValid = validatePassedArguments();
    if(bValid)
    	bValid = camRegister_->setVaue("state", argString_.c_str());
    responseInfo = bValid ? successMsg_ : failureMsg_;
    return bValid;
}
