#include "Hill-climbing_with_Sideways_Move/hcsm.h"
#include "Random_Restart_Hill-climbing/rrhc.h"
#include "Simulated_Annealing/sa.h"
#include "Steepest_Ascent_Hill-climbing/sahc.h"
#include "Stochastic_Hill-climbing/shc.h"
#include "cube.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

float angleX = 0.0f, angleY = 0.0f;
float lastMouseX = 0.0f, lastMouseY = 0.0f;
float zoom = -15.0f; // Initial zoom level
bool mousePressed = false;

void *input_thread(void *arg) {
	Cube *cube = (Cube *)arg;
	char input[100];
	puts("what algorithm you wanna use? (sahc, hcsm, shc, rrhc, sa), shuffle, or quit");
	while (1) {
		if (fgets(input, sizeof(input), stdin) != NULL) {
			// Remove newline character from input
			input[strcspn(input, "\n")] = 0;

			if (strcmp(input, "sahc") == 0) {
				sahc(cube);
			}
			else if (strcmp(input, "hcsm") == 0) {
				hcsm(cube);
			}
			else if (strcmp(input, "shc") == 0) {
				shc(cube);
			}
			else if (strcmp(input, "rrhc") == 0) {
				rrhc(cube);
			}
			// else if (strcmp(input, "sa") == 0) {
			// 	sa(cube);
			// }
			else if (strcmp(input, "shuffle") == 0) {
				shuffle_cube(cube);
			}
			else if (strcmp(input, "quit") == 0) {
				exit(0);
			}
			else {
				puts("Invalid input. Please enter one of the following: sahc, hcsm, shc, rrhc, sa");
			}
		}
	}
	return NULL;
}

bool isPartOfSequence(int x, int y, int z, Cube *cube) {
	// Check rows, columns, pillars, diagonals, and space diagonals
	int sum;

	// Check row
	sum = 0;
	for (int i = 0; i < SIZE; i++) {
		sum += cube->blocks[x][y][i].value;
	}
	if (sum == MAGIC_NUMBER) return true;

	// Check column
	sum = 0;
	for (int i = 0; i < SIZE; i++) {
		sum += cube->blocks[x][i][z].value;
	}
	if (sum == MAGIC_NUMBER) return true;

	// Check pillar
	sum = 0;
	for (int i = 0; i < SIZE; i++) {
		sum += cube->blocks[i][y][z].value;
	}
	if (sum == MAGIC_NUMBER) return true;

	// Check main diagonal
	if (x == y && y == z) {
		sum = 0;
		for (int i = 0; i < SIZE; i++) {
			sum += cube->blocks[i][i][i].value;
		}
		if (sum == MAGIC_NUMBER) return true;
	}

	// Check anti-diagonal
	if (x + y + z == SIZE - 1) {
		sum = 0;
		for (int i = 0; i < SIZE; i++) {
			sum += cube->blocks[i][SIZE - 1 - i][i].value;
		}
		if (sum == MAGIC_NUMBER) return true;
	}

	// Check space diagonals
	if (x == y) {
		sum = 0;
		for (int i = 0; i < SIZE; i++) {
			sum += cube->blocks[i][i][z].value;
		}
		if (sum == MAGIC_NUMBER) return true;
	}

	if (y == z) {
		sum = 0;
		for (int i = 0; i < SIZE; i++) {
			sum += cube->blocks[x][i][i].value;
		}
		if (sum == MAGIC_NUMBER) return true;
	}

	if (x == z) {
		sum = 0;
		for (int i = 0; i < SIZE; i++) {
			sum += cube->blocks[i][y][i].value;
		}
		if (sum == MAGIC_NUMBER) return true;
	}

	return false;
}

void drawBlock(int value, float x, float y, float z, bool isGreen) {
	glPushMatrix();
	glTranslatef(x, y, z);
	if (isGreen) {
		glColor4f(0.0f, 1.0f, 0.0f, 0.15f); // Set color to green with 50% opacity
	}
	else {
		glColor4f(0.5f, 0.5f, 1.0f, 0.05f); // Set color to purple with 10% opacity
	}
	glutSolidCube(1.0); // Draw a cube at (x, y, z)
	glPopMatrix();

	// Draw the value inside the block
	glPushMatrix();
	glTranslatef(x, y, z);
	glDisable(GL_DEPTH_TEST); // Disable depth testing for text
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos3f(-0.1f, -0.1f, 0.0f); // Center the text inside the cube
	char buf[10];
	snprintf(buf, sizeof(buf), "%d", value);
	for (char *c = buf; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glEnable(GL_DEPTH_TEST); // Re-enable depth testing
	glPopMatrix();
}

void drawCube(Cube *cube) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				bool isGreen = isPartOfSequence(i, j, k, cube);
				drawBlock(cube->blocks[i][j][k].value, i * 1.2f, j * 1.2f, k * 1.2f, isGreen);
			}
		}
	}
}

void display(Cube *cube) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-2.5f, -2.5f, zoom); // Use the zoom level

	// Rotate based on the current angles
	glRotatef(angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);

	// Draw the cube
	drawCube(cube);

	glfwSwapBuffers(glfwGetCurrentContext());
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	(void)mods; // Mark the parameter as unused

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mousePressed = true;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		lastMouseX = xpos;
		lastMouseY = ypos;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mousePressed = false;
	}
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
	(void)window; // Mark the parameter as unused

	if (mousePressed) {
		float dx = xpos - lastMouseX;
		float dy = lastMouseY - ypos;
		angleX += dy * 0.2f;
		angleY += dx * 0.2f;
		lastMouseX = xpos;
		lastMouseY = ypos;
	}
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	(void)window;  // Mark the parameter as unused
	(void)xoffset; // Mark the parameter as unused

	zoom += yoffset; // Adjust zoom level based on scroll input
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	(void)window;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(void) {
	Cube *cube = (Cube *)malloc(sizeof(Cube));

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow *window = glfwCreateWindow(640, 480, "3D Cube Visualization", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize GLUT
	int glut_argc = 1;
	char *glut_argv[] = {(char *)"dummy"};
	glutInit(&glut_argc, glut_argv);

	// Set up callbacks for mouse, scroll, and framebuffer size
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set the clear color to a dark gray
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Your 3D cube values
	init_cube(cube);

	// Set the initial viewport and projection
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);

	// Create a thread to handle user input
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, input_thread, (void *)cube);

	while (!glfwWindowShouldClose(window)) {
		display(cube);
		glfwPollEvents();
	}

	glfwTerminate();
	free(cube);
	return 0;
}