OBJECT=GNU-Linux/ResponseExecutor.o GNU-Linux/GetLedRateExecutor.o GNU-Linux/GetLedStateExecutor.o GNU-Linux/GetLedColorExecutor.o \
	GNU-Linux/SingleLogger.o GNU-Linux/CameraRegister.o GNU-Linux/TestProtocolFactory.o GNU-Linux/ProtocolImplementation.o \
	GNU-Linux/ResponseManager.o GNU-Linux/main.o \
	GNU-Linux/SetLedRateExecutor.o GNU-Linux/SetLedStateExecutor.o GNU-Linux/SetLedColorExecutor.o GNU-Linux/InvalidExecutor.o 
	
CXX=g++
TARGET=../GNU-Linux/testfifo
CXXFLAGS=-c -std=c++0x -Wall -O2 -fPIC
LIBS=-lpthread 

$(TARGET): $(OBJECT)
	mkdir -p ../GNU-Linux/
	cp protocol.sh send.sh ../GNU-Linux
	$(CXX) $(OBJECT) $(LIBS) -o $(TARGET)

GNU-Linux/ResponseExecutor.o: ResponseExecutor.cpp  
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) ResponseExecutor.cpp -o GNU-Linux/ResponseExecutor.o

GNU-Linux/GetLedRateExecutor.o: GetLedRateExecutor.cpp GetLedRateExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) GetLedRateExecutor.cpp -o GNU-Linux/GetLedRateExecutor.o

GNU-Linux/GetLedStateExecutor.o: GetLedStateExecutor.cpp GetLedStateExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) GetLedStateExecutor.cpp -o GNU-Linux/GetLedStateExecutor.o

GNU-Linux/GetLedColorExecutor.o: GetLedColorExecutor.cpp GetLedColorExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) GetLedColorExecutor.cpp -o GNU-Linux/GetLedColorExecutor.o

GNU-Linux/SetLedRateExecutor.o: SetLedRateExecutor.cpp SetLedRateExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) SetLedRateExecutor.cpp -o GNU-Linux/SetLedRateExecutor.o

GNU-Linux/SetLedStateExecutor.o: SetLedStateExecutor.cpp SetLedStateExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) SetLedStateExecutor.cpp -o GNU-Linux/SetLedStateExecutor.o

GNU-Linux/SetLedColorExecutor.o: SetLedColorExecutor.cpp SetLedColorExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) SetLedColorExecutor.cpp -o GNU-Linux/SetLedColorExecutor.o

GNU-Linux/InvalidExecutor.o: InvalidExecutor.cpp InvalidExecutor.h ResponseExecutor.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) InvalidExecutor.cpp -o GNU-Linux/InvalidExecutor.o

GNU-Linux/SingleLogger.o: SingleLogger.cpp SingleLogger.h  
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) SingleLogger.cpp -o GNU-Linux/SingleLogger.o

GNU-Linux/CameraRegister.o: CameraRegister.cpp CameraRegister.h  
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) CameraRegister.cpp -o GNU-Linux/CameraRegister.o

GNU-Linux/TestProtocolFactory.o: TestProtocolFactory.cpp TestProtocolFactory.h  ExecutorFactory.h ResponseExecutor.h
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) TestProtocolFactory.cpp -o GNU-Linux/TestProtocolFactory.o

GNU-Linux/ResponseManager.o: ResponseManager.cpp TestProtocolFactory.h  
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) ResponseManager.cpp -o GNU-Linux/ResponseManager.o

GNU-Linux/ProtocolImplementation.o: ProtocolImplementation.cpp ProtocolImplementation.h  
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) ProtocolImplementation.cpp -o GNU-Linux/ProtocolImplementation.o

GNU-Linux/main.o: main.cpp ResponseManager.h SingleLogger.h Handlers.h 
	mkdir -p GNU-Linux
	$(CXX) $(CXXFLAGS) $(POCOINCLUDE) main.cpp -o GNU-Linux/main.o

clean:
	rm -f $(TARGET) $(OBJECT) 
