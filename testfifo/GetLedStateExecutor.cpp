#include "GetLedStateExecutor.h"
#include "CameraRegister.h"

GetLedStateExecutor::GetLedStateExecutor(unsigned int uniqueId)
: ResponseExecutor(uniqueId)
{
    nArguments_ = 0;
}

bool GetLedStateExecutor::executeResponse(std::string& responseInfo)
{
    std::string stateValue;
    
    bool bValid = camRegister_->getVaue("state", stateValue);
    responseInfo = bValid ? successMsg_ + " " + stateValue : failureMsg_;
    
    return bValid;
}

