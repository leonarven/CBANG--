


LIBS = -lsfml-network -lsfml-system



SRC_SERVER = $(shell find ./server -type f -name "*.cpp")
SRC_CLIENT = $(shell find ./client -type f -name "*.cpp")

OBJ_SERVER = $(patsubst ./server/%.cpp, ./server/obj/%.o, $(SRC_SERVER))
OBJ_CLIENT = $(patsubst ./client/%.cpp, ./server/obj/%.o, $(SRC_CLIENT))

DEP_SERVER = $(patsubst %.cpp, ./server/obj/%.d, $(SRC_SERVER))
DEP_CLIENT = $(patsubst %.cpp, ./client/obj/%.d, $(SRC_CLIENT))

CPPFLAGS 	= $(if $(DEBUGMODE), -g -D DEBUG) -Wall -MD -c
LDFLAGS 	= $(if $(DEBUGMODE), -Wl -S) $(LIBS)

all: client

server: $(OBJ_SERVER)
	@echo Linking: $(OBJ_SERVER)
	@g++ $(LDFLAGS) $(OBJ_SERVER) -o ./server/bin/server

client: $(OBJ_CLIENT)
	@echo Linking: $(OBJ_CLIENT)
	@g++ $(LDFLAGS) $(OBJ_CLIENT) -o ./client/bin/client

./server/obj/%.o: ./server/%.cpp
	@echo Compiling: $<
	@mkdir -p $(dir $@)
	@g++ $(CPPFLAGS) $< -o $@
	
./client/obj/%.o: ./client/%.cpp
	@echo Compiling: $<
	@mkdir -p $(dir $@)
	@g++ $(CPPFLAGS) $< -o $@

.PHONY:clean
clean:
	@echo Cleaning up...
	@rm -r ./server/obj/*
	@rm -r ./server/bin/* 
	@rm -r ./client/obj/*
	@rm -r ./client/bin/* 
