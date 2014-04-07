#include "GetLedRateExecutor.h"
#include "CameraRegister.h"

GetLedRateExecutor::GetLedRateExecutor(unsigned int uniqueId)
: ResponseExecutor(uniqueId)
{
    nArguments_ = 0;
}

bool GetLedRateExecutor::executeResponse(std::string& responseInfo)
{
    std::string rateValue;
    
    bool bValid = camRegister_->getVaue("rate", rateValue);
    responseInfo = bValid ? (successMsg_ + " " + rateValue) : failureMsg_;
    
    return bValid;
}
