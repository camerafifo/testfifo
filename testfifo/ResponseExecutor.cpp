#include "ResponseExecutor.h"
#include <sstream>
#include <vector>
#include <algorithm>

#include "CameraRegister.h"

const std::string ResponseExecutor::successMsg_ = "OK";
const std::string ResponseExecutor::failureMsg_ = "FAILED";

ResponseExecutor::ResponseExecutor(unsigned int uniqueId)
: uniqueId_(uniqueId) 
{
  camRegister_ = CameraRegister::InitCameraRegister();
}

ResponseExecutor::~ResponseExecutor()
{
  camRegister_->FreeCamRegister();
}

bool ResponseExecutor::validatePassedArguments()
{
    std::vector<std::string> values;
    std::istringstream iarg(argString_);
    std::string currentArg;

    while (std::getline(iarg, currentArg, ' '))
        values.push_back(currentArg);

    if (values.size() < nArguments_)
        return false;

    bool bValid = true;
    
    for (unsigned int i = 0; i < values.size() && bValid; ++i) 
    {
        auto it = argumentValueSet_.find(i);
        if (std::find(it->second.begin(), it->second.end(), values[i]) == it->second.end())
            bValid = false;
    }
    
    return bValid;
}

unsigned int ResponseExecutor::getReponseId()
{
    return uniqueId_;
}

void ResponseExecutor::passArgs(const char* args)
{
    argString_.assign(args);
}