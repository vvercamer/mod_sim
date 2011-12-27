SIM_OBJ_ = main.o random.o file_maker.o particle.o source.o experiment.o detector.o collimator.o enclosure.o interaction_data.o
SIM_BIN_=simulation

POSTPROCESS_OBJ_ = postprocessing.o
POSTPROCESS_BIN_=postprocessing

SRC=src
LIB=lib
BIN=bin

ROOTFLAGS = $(ROOT_INCLUDE) $(ROOT_LIB)
ROOT_INCLUDE = -I $(ROOTSYS)/include 
ROOT_LIB = $(shell root-config --libs)
#ROOT_LIB = -L $(ROOTSYS)/lib -lCore -lCint \
#         -lGraf -lGraf3d -lHist -lHtml -lMatrix -lMinuit \
#         -lPostscript -lProof -lTree \
#         -lGpad -lGui -lGX11 -lRint 

CC = g++
CFLAGS = -Wall -Werror -O2 -Wshadow
INCLUDES = -I/usr/local/include
LIBS = -L/usr/local/lib -lgsl -lgslcblas -lm 
# -lpthread 
SIM_OBJ = $(patsubst %,$(LIB)/%,$(SIM_OBJ_))
POSTPROCESS_OBJ = $(patsubst %,$(LIB)/%,$(POSTPROCESS_OBJ_))
OBJ_FILES = $(SIM_OBJ) $(POSTPROCESS_OBJ)
SIM_BIN=$(BIN)/$(SIM_BIN_)
POSTPROCESS_BIN=$(BIN)/$(POSTPROCESS_BIN_)




all: $(SIM_BIN) $(POSTPROCESS_BIN) 

clean:
	rm -f $(EXEC_NAME) $(OBJ_FILES)

$(LIB)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(ROOT_INCLUDE) -o $@ -c $<

$(SIM_BIN): $(SIM_OBJ)
	$(CC) -o $@ $+ $(LIBS)

$(POSTPROCESS_BIN): $(POSTPROCESS_OBJ)
	$(CC) -o $@ $+ $(LIBS) $(ROOTFLAGS)

#$(LIB)/%.o: %.c
#	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

#install :
#	cp $(EXEC_NAME) $(BIN)
