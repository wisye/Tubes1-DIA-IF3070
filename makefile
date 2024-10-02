CC = gcc
CP = g++

SOURCE_FOLDER = src
OUTPUT_FOLDER = bin

WARNING_CFLAG = -Wall -Wextra -Werror
OPENGL_FLAG =  -lglfw -lGLEW -lGL -lGLU -lm -lglut

all: build run

build:
	 @$(CC) $(WARNING_CFLAG) $(OPENGL_FLAG) $(SOURCE_FOLDER)/cube.c \
	 $(SOURCE_FOLDER)/Steepest_Ascent_Hill-climbing/sahc.c \
	 $(SOURCE_FOLDER)/Hill-climbing_with_Sideways_Move/hcsm.c \
	 $(SOURCE_FOLDER)/Simulated_Annealing/sa.c \
	 $(SOURCE_FOLDER)/Stochastic_Hill-climbing/shc.c \
	 $(SOURCE_FOLDER)/Random_Restart_Hill-climbing/rrhc.c \
	 $(SOURCE_FOLDER)/Genetic_Algorithm/ga.c \
	 $(SOURCE_FOLDER)/visualize_cube.c \
	 $(SOURCE_FOLDER)/main.c -o $(OUTPUT_FOLDER)/bin

run:
	@./$(OUTPUT_FOLDER)/bin

example:
	@$(CP) $(WARNING_CFLAG) $(SOURCE_FOLDER)/example/hillsteep_queen.cpp -o $(OUTPUT_FOLDER)/hillsteep_queen

clear:
	@rm -rf bin/*
	@rm -rf src/Parents/*