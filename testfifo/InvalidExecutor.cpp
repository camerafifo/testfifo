#include "InvalidExecutor.h"

InvalidExecutor::InvalidExecutor(unsigned int uniqueId)
: ResponseExecutor(uniqueId)
{
}

bool InvalidExecutor::executeResponse(std::string& responseInfo)
{
    responseInfo = failureMsg_;
    return false;
}
