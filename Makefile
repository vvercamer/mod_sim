CC = g++
CFLAGS = -Wall -Werror -O2 -Wshadow
EXEC_NAME = simulation
INCLUDES = -I/usr/local/include
LIBS = -L/usr/local/lib -lgsl -lgslcblas -lm 
# -lpthread 
OBJ_FILES = main.o random.o file_maker.o particle.o source.o experiment.o detector.o collimator.o enclosure.o interaction_data.o
#gnuplot.o
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)

clean :
	rm -f $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	cp $(EXEC_NAME) $(INSTALL_DIR)
