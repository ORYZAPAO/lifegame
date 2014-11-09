TARGET = life
OBJS   = main.o 
INCLUDE = lifegame.h

CXX    = clang++ -std=c++11
##CXX    = g++ -std=c++11
CFLAGS = -c

.SUFFIX: .o .h .cpp
.PHONY : clean


$(TARGET) : $(OBJS) 
	$(CXX) -o $(TARGET) $^

##ｄ.h.o :
##	touch $<
##.cpp.o :
##	$(CXX) $(CFLAGS) $<

main.o: main.cpp $(INCLUDE)
	$(CXX) $(CFLAGS) $<

clean:	
	rm $(TARGET) *.o 
