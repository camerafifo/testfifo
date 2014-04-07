#include "GetLedExecutor.h"

GetLedExecutor::GetLedExecutor(unsigned int uniqueId, const char* arg)
: ResponseExecutor(uniqueId)
, arguments(arg)
{  
  argumentValueSet_.insert(std::make_pair("-color"), std::list<std::string>);
  argumentValueSet_.insert(std::make_pair("-rate"), std::list<std::string>);
  argumentValueSet_.insert(std::make_pair("-state"), std::list<std::string>);
}

bool GetLedExecutor::executeResponse(std::string& responseInfo)
{
  std::vector<std::string> values;
  std::istringstream iarg(argString_);
  std::string currentArg;
  
  while(std::getline(iarg, currentArg, ' '))
    values.push_back(currentArg);
  
  if(values.size() < nArguments_)
    return false;
  
  bool bValid = true;
  
  for(unsigned int i = 0; i < values.size() && bValid; ++i)
  {
    auto it = argumentValueSet_.find(i);
    if(std::find(it->second.begin(), it->second.end(), values[i]) == it->end())
      bValid = false;
  }
  
  return bValid;
}

        
