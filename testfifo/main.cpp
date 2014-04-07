#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include "ResponseManager.h"
#include "SingleLogger.h"
#include "Handlers.h"

void daemonFrame()
{
    pid_t currentPID;
#if(1)
    
    currentPID = fork();

    if (currentPID < 0)
        exit(EXIT_FAILURE);


    if (currentPID > 0)
        exit(EXIT_SUCCESS);

    if (setsid() < 0)
        exit(EXIT_FAILURE);
#endif
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    signal(SIGQUIT, Handlers::fatalSignalHandler);
    signal(SIGILL, Handlers::fatalSignalHandler);
    signal(SIGTRAP, Handlers::fatalSignalHandler);
    signal(SIGABRT, Handlers::fatalSignalHandler);
    signal(SIGIOT, Handlers::fatalSignalHandler);
    signal(SIGBUS, Handlers::fatalSignalHandler);
    signal(SIGFPE, Handlers::fatalSignalHandler);
    signal(SIGSEGV, Handlers::fatalSignalHandler);
    signal(SIGSTKFLT, Handlers::fatalSignalHandler);
    signal(SIGCONT, Handlers::fatalSignalHandler);
    signal(SIGPWR, Handlers::fatalSignalHandler);
    signal(SIGSYS, Handlers::fatalSignalHandler);
    signal(SIGTERM, Handlers::terminationSignalHandler<ResponseManager>);
    
#if(1)
    currentPID = fork();

    if (currentPID < 0)
        exit(EXIT_FAILURE);

    if (currentPID > 0)
        exit(EXIT_SUCCESS);

    umask(0);

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int stdioStub = open("/dev/null", O_RDWR);
    dup(stdioStub);
    dup(stdioStub);
    
    setpgrp(); 
#endif

    SingleLogger* logger = SingleLogger::InitLogger();
    std::string message("Daemon PID: " + std::to_string((getpid())));
    logger->logMessage(SingleLogger::INFO, message.c_str());
    logger->FreeLogger();
}

bool checkDaemonExistence(const char* daemonName) 
{
    SingleLogger* logger = SingleLogger::InitLogger(); 
    std::string serviceName(daemonName);
    bool isRunning = false;
    std::string pidFileName("/var/run/" + serviceName + ".pid");
    std::ifstream pidFile(pidFileName.c_str(), std::ifstream::binary);
    if(pidFile.is_open())
    {
        long pid = 0;
        std::string pidLine;
        if (pidFile.is_open()) 
        {
            getline(pidFile, pidLine);
            pid = std::stoi(pidLine);
            kill(pid, 0);
            isRunning = !(errno == ESRCH);
        }
    }

    if (!isRunning) 
    {
        std::ofstream pidFile(pidFileName.c_str(), std::ofstream::binary);
        if (pidFile.is_open()) {
            pidFile << getpid();
            pidFile.close();
        }
        else
            logger->logMessage(SingleLogger::WARNING, "pid file is not created");
    } 
    else
        logger->logMessage(SingleLogger::ERROR, "daemon already running");

    return isRunning;
}

int main(int argc, char** argv)
{
    std::string path;
    char tempFileName[PATH_MAX + 1];
    memset(tempFileName, 0, PATH_MAX + 1);
    readlink("/proc/self/exe", tempFileName, PATH_MAX);
    path.assign(tempFileName);
    int slash = path.find_last_of("/");
    std::string daemonName;
    std::string logDirectory = "/";
    if(slash != 0 && slash != std::string::npos)
    {
        daemonName.assign(path.c_str() + slash + 1);
        path.erase(slash);
        logDirectory = path + "/";
        path.append("/cam_fifo");
    }
    else 
    {
        daemonName = "testfifo";
        path = "/cam_fifo";
    }
    
    SingleLogger* logger = 
            SingleLogger::InitLogger(std::string(logDirectory + daemonName + ".log").c_str());
    
    //create daemon
    daemonFrame();
    
    //check daemon is not running
    if(checkDaemonExistence(daemonName.c_str()))
        return 0;
                
    int publicFifo = -1;
       
    char readbBuf[256];
    memset(readbBuf, 0, sizeof(readbBuf));
    pid_t pid = -1;

    
    logger->logMessage(SingleLogger::INFO, "service is starting");    
    unlink(path.c_str());
    
    std::string message("fifo creation at \"" + path + "\"");
    logger->logMessage(SingleLogger::INFO, message.c_str());
    int result = mkfifo(path.c_str(), S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP); 
    if(result == -1) 
    {
        std::string errMessage("creation fifo error: ");
        errMessage.append(strerror(errno));
        logger->logMessage(SingleLogger::ERROR, errMessage.c_str());
        exit(0);
    }
        
    ResponseManager* manager = new ResponseManager();
    Handlers::releasedResource = static_cast<void*>(manager);
    Handlers::pidFileToDelete = "/var/run/" + daemonName + ".pid";
    
    while(true) 
    {
        publicFifo = open(path.c_str(), O_RDONLY);
        if(publicFifo < 0) 
        {
            std::string errMessage("open fifo error: ");
            errMessage.append(strerror(errno));
            logger->logMessage(SingleLogger::ERROR, errMessage.c_str());
            exit(0);
        }
        
        //read public fifo
        int readSize = read(publicFifo, readbBuf, sizeof(readbBuf));
        close(publicFifo);
        publicFifo = -1;
        
        if(readSize > 0) 
        {
            std::string message(readbBuf);

            message.append(" is processed");
            logger->logMessage(SingleLogger::INFO, message.c_str());

            unsigned int pid = atoi(readbBuf);
            memset(readbBuf, 0, sizeof (readbBuf));
            
            //start to process request
            manager->processRequest(pid);
        }
    }
    
    return 0;
}
        
