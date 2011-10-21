CC = gcc
CFLAGS = -Wall -Werror -O2 -Wshadow
EXEC_NAME = postprocessor
INCLUDES = 
LIBS = 
OBJ_FILES = postprocessor.o gnuplot_i.o
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)

clean :
	rm -f $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	cp $(EXEC_NAME) $(INSTALL_DIR)
