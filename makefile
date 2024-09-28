CC = gcc
CP = g++

SOURCE_FOLDER = src
OUTPUT_FOLDER = bin

WARNING_CFLAG = -Wall -Wextra -Werror

all: build run

build:
	@$(CC) $(WARNING_CFLAG) $(SOURCE_FOLDER)/cube.c $(SOURCE_FOLDER)/main.c -o $(OUTPUT_FOLDER)/bin

run:
	@./$(OUTPUT_FOLDER)/bin

example:
	@$(CP) $(WARNING_CFLAG) $(SOURCE_FOLDER)/example/hillsteep_queen.cpp -o $(OUTPUT_FOLDER)/hillsteep_queen