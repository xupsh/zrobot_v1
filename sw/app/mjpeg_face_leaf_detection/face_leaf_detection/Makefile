CPP = arm-xilinx-linux-gnueabi-g++
CFLAGS += `pkg-config --cflags opencv`
LFLAGS += `pkg-config --libs opencv`

facedetection:facedetection.o leafRecognition.o LeafClassifier.o calculate.o calculatorORleaf.o hullDetector.o v4l2lib.o
	$(CPP) $(LFLAGS) -O2 -o $@ $^
facedetection.o:facedetection.cpp
	$(CPP) $(CFLAGS) -O2 -c $^
leafRecognition.o:leafRecognition.cpp
	$(CPP) $(CFLAGS) -O2 -c $^
LeafClassifier.o:LeafClassifier.cpp
	$(CPP) $(CFLAGS) -O2 -c $^
calculate.o:calculate.cpp
	$(CPP) $(CFLAGS) -O2 -c $^
calculatorORleaf.o:calculatorORleaf.cpp
	$(CPP) $(CFLAGS) -O2 -c $^
hullDetector.o:hullDetector.cpp
	$(CPP) $(CFLAGS) -O2 -c $^
v4l2lib.o:v4l2lib.c v4l2lib.h
	$(CPP) -O2 -c $<

.PHONY: clean
clean:
	rm *.o facedetection *~ 
