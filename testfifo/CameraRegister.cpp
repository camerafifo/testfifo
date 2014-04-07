#include "CameraRegister.h"

CameraRegister* CameraRegister::self_ = NULL;
unsigned int CameraRegister::refcount_ = 0;
std::map<std::string, std::string> CameraRegister::registerSet_;
std::map<std::string, pthread_mutex_t> CameraRegister::registerLock_;

CameraRegister* CameraRegister::InitCameraRegister() 
{
    if (self_ == NULL) 
    {
        self_ = new CameraRegister();
        registerSet_.insert(std::make_pair("state", "of"));
        registerLock_.insert(std::make_pair("state", pthread_mutex_t()));
        registerSet_.insert(std::make_pair("color", "red"));
        registerLock_.insert(std::make_pair("color", pthread_mutex_t()));
        registerSet_.insert(std::make_pair("rate", "0"));
        registerLock_.insert(std::make_pair("rate", pthread_mutex_t()));
        
        for(auto it = registerLock_.begin(); it != registerLock_.end(); ++it)
            pthread_mutex_init(&(it->second), NULL);
    }
    
    refcount_++;
    return self_;
}

void CameraRegister::FreeCamRegister()
{
    --refcount_; 
    if(!refcount_) 
    {
        for(auto it = registerLock_.begin(); it != registerLock_.end(); ++it)
            pthread_mutex_destroy(&it->second);
        
        delete this;
        self_= NULL;
        
    }
}

bool CameraRegister::setVaue(const char* item, const char* value)
{
    if(item == NULL || value == NULL)
        return false;
    
    auto it = registerLock_.find(item);
    if(it != registerLock_.end())
    {
        pthread_mutex_lock(&it->second);
        registerSet_.find(item)->second.assign(value);
        pthread_mutex_unlock(&it->second);
        return true;
    }
    
    return false;
}

bool CameraRegister::getVaue(const char* item, std::string& value)
{
    if(item == NULL)
        return false;
    
    auto it = registerLock_.find(item);
    if(it != registerLock_.end())
    {
        pthread_mutex_lock(&it->second);
        value.assign(registerSet_.find(item)->second);
        pthread_mutex_unlock(&it->second);
        return true;
    }
    
    return false;
}
