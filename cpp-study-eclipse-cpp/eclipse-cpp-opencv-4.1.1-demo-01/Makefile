CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		eclipse-cpp-opencv-4.1.1-demo-01.o

LIBS =

TARGET =	eclipse-cpp-opencv-4.1.1-demo-01.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)