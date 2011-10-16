SIMUL = main.o 

C++ = c++ -Wall -Werror -O -Wshadow -I/usr/local/include -D__MACOSX_CORE__ 

LDFLAGS=-lgsl -lgslcblas -lm -lpthread

all:: main clean

main: $(SIMUL)
	$(C++) -L/usr/local/lib -o simulation $(SIMUL) $(LDFALGS)


-include $(SIMUL:.o=.d)

%.o: %.cpp
	$(C++) -c $*.cpp -o $*.o -Wall -Wshadow -Werror -O
	$(C++) -MM $*.cpp > $*.d

clean::
	@rm *.o

