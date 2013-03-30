FILE = test.cc GA_Matrix.cc GA_Engine.cc
CXXFLAGS = -g -Wall -O3
CPPUNIT = -ldl -cppunit
GA_Scheduler: $(FILE)
	g++ -o GA_Scheduler $(FILE) $(CXXFLAGS)
