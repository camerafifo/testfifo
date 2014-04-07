#include "GetLedColorExecutor.h"
#include "CameraRegister.h"

GetLedColorExecutor::GetLedColorExecutor(unsigned int uniqueId)
        :ResponseExecutor(uniqueId)
{
    nArguments_ = 0;   
}

bool GetLedColorExecutor::executeResponse(std::string& responseInfo)
{
    std::string colorValue;
    
    bool bValid = camRegister_->getVaue("color", colorValue);
    responseInfo = bValid ? successMsg_ + " " + colorValue : failureMsg_;
    
    return bValid;
}
