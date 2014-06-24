
CC = g++
CFLAGS = -c

WFLAGS = -Wall -Warray-bounds 

OPTS = -O0
 
OFLAGS =  -g2

LFLAGS = -lm

EXECUTABLE = rayTracer

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LIB = -fopenmp
SUBMIT_DIR = HW1
BACKUP_DIR = $(shell date "+%b_%d_%Y_%I_%M")
BACKUP_REPO	= ./Backups
BACKUP_PATH = $(BACKUP_REPO)/$(BACKUP_DIR)

all:$(EXECUTABLE)

	
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(WFLAGS) $(OPTS) $(LFLAGS) $(LIB) $^ -o $@ 

obj/%.o: src/%.cpp
	mkdir -p ./obj
	$(CC) $(CFLAGS) $(WFLAGS) $(OPTS) $(OFLAGS) $(LIB) -c -o $@ $<


clean:
	rm -f $(OBJ_FILES)
	rm -f *.out
	rm -f *~
	rm -f $(EXECUTABLE) 
	rm -f $(SUBMIT_DIR).tar

#Create a Backup directory with <Month>_<Date>_<Year>_<Hr>_<Min>_<Sec>.tar
backup: 
	mkdir -p $(BACKUP_REPO)
	mkdir -p $(BACKUP_PATH)
	mkdir -p $(BACKUP_PATH)/src
	mkdir $(BACKUP_PATH)/scenes	
	cp -r ./src/*.h ./$(BACKUP_PATH)/src
	cp -r ./src/*.cpp ./$(BACKUP_PATH)/src
	cp -r ./scenes/* ./$(BACKUP_PATH)/scenes
	cp Makefile $(BACKUP_PATH)/
	tar -zcvf $(BACKUP_REPO)/$(BACKUP_DIR).tar $(BACKUP_PATH)/
	rm -rf $(BACKUP_PATH)

#Make the Sumbission directory with all the .cpp and .h and the Makefile	
submit:
	rm -rf $(SUBMIT_DIR)      						# Remove Previous Submission Dir
	rm -rf $(SUBMIT_DIR).tar						# Remove Previous .tar
	mkdir $(SUBMIT_DIR)								# Make a new directory
	mkdir $(SUBMIT_DIR)/src	
	mkdir $(SUBMIT_DIR)/scenes						# Make a src folder in the new directory
	cp -r ./src/*.h ./$(SUBMIT_DIR)/src
	cp -r ./src/*.cpp ./$(SUBMIT_DIR)/src
	cp -r ./scenes/* ./$(SUBMIT_DIR)/scenes
	cp Makefile ./$(SUBMIT_DIR)
	tar -zcvf $(SUBMIT_DIR).tar $(SUBMIT_DIR)
	rm -rf $(SUBMIT_DIR)
	
#Cleans all the tars, along with all the backups
cleantar:
	rm -rf *.tar
	
	
	
