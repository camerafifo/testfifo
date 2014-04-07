/* 
 * File:   TestProtocolFactory.h
 * Author: dmitriy
 *
 * Created on 7 Апрель 2014 г., 0:37
 */

#ifndef TESTPROTOCOLFACTORY_H
#define	TESTPROTOCOLFACTORY_H
#include "ExecutorFactory.h"
#include "ResponseExecutor.h"

//factory of response executors for test protocol
class TestProtocolFactory : public ExecutorFactory
{
    virtual ResponseExecutor* createExecutor(unsigned int uniqueId, const char* commandKey);
};

#endif	/* TESTPROTOCOLFACTORY_H */

