/* 
 * File:   ExecutorFactory.h
 * Author: dmitriy
 *
 * Created on 7 Апрель 2014 г., 0:34
 */

#ifndef EXECUTORFACTORY_H
#define	EXECUTORFACTORY_H
class ResponseExecutor;

//interface to create execute response
class ExecutorFactory
{
    
public:
    virtual ResponseExecutor* createExecutor(unsigned int uniqueId, const char* commandKey) = 0;
};

#endif	/* EXECUTORFACTORY_H */

