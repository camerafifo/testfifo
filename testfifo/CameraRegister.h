/* 
 * File:   CameraRegister.h
 * Author: dmitriy
 *
 * Created on 7 Апрель 2014 г., 8:17
 */

#ifndef CAMERAREGISTER_H
#define	CAMERAREGISTER_H

#include <map>
#include <mutex>
#include <memory>

class CameraRegister
{
private:

    CameraRegister()
    {
    };

    ~CameraRegister()
    {
    };

    CameraRegister(const CameraRegister& reg);
    CameraRegister& operator=(CameraRegister& reg);

    static CameraRegister* self_;
    static unsigned int refcount_;
    static std::map<std::string, std::string> registerSet_;
    static std::map<std::string, pthread_mutex_t> registerLock_;
    
public:
    static CameraRegister* InitCameraRegister();
    void FreeCamRegister();
    bool setVaue(const char* item, const char* value);
    bool getVaue(const char* item, std::string& value);
};

#endif	/* CAMERAREGISTER_H */

