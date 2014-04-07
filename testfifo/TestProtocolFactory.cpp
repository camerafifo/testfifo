#include "TestProtocolFactory.h"
#include "InvalidExecutor.h"
#include "GetLedColorExecutor.h"
#include "GetLedRateExecutor.h"
#include "GetLedStateExecutor.h"
#include "SetLedColorExecutor.h"
#include "SetLedRateExecutor.h"
#include "SetLedStateExecutor.h"
#include <string.h>

ResponseExecutor* TestProtocolFactory::createExecutor(unsigned int uniqueId, const char* commandKey) 
{
    if (strlen(commandKey) != 0) 
    {
        if (strcmp(commandKey, "set-led-state") == 0)
            return new SetLedStateExecutor(uniqueId);
        else if (strcmp(commandKey, "set-led-color") == 0)
            return new SetLedColorExecutor(uniqueId);
        else if (strcmp(commandKey, "set-led-rate") == 0)
            return new SetLedRateExecutor(uniqueId);
        else if (strcmp(commandKey, "get-led-state") == 0)
            return new GetLedStateExecutor(uniqueId);
        else if (strcmp(commandKey, "get-led-color") == 0)
            return new GetLedColorExecutor(uniqueId);
        else if (strcmp(commandKey, "get-led-rate") == 0)
            return new GetLedRateExecutor(uniqueId);
    }
    
    return new InvalidExecutor(uniqueId);
}

