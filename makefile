FLAGS = -lboost_system
boost.o:
	g++ boostTest.cpp -o boost $(FLAGS) 
