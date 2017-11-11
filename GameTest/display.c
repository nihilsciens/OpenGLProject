#include "display.h"
#include <GL\glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <include\SDL.h>

struct Display* display_Constructor(int width, int height, char* title) {

	// Initialize the Display via SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Define 8 bits for each color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// The SDL buffer needs to be size 4*8=32
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	// A double buffers allows for two windows
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Declare and define new Display
	struct Display* D = malloc(sizeof(struct Display));

	// Define values to new Window
	D->main_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	D->main_GLContext = SDL_GL_CreateContext(D->main_Window);

	/*	
	*	GLEW: searches through operative system for supported OpenGL
	*	Will return GLEW_OK if GLEW is ready for running
	*/
	GLenum status = glewInit();

	// Make sure GLEW is ready
	if (status != GLEW_OK)
		printf("Glew failed to initialize OpenGL!");

	// Display is operational
	D->main_IsClosed = false;

	// Return constructed Display
	return D;

}

void display_Destructor(struct Display* D_input) {
	// Deconstructs the Window (Display struct)
	SDL_GL_DeleteContext(D_input->main_GLContext);
	SDL_DestroyWindow(D_input->main_Window);
	SDL_Quit();
	free(D_input);
}

void display_Clear(float r, float g, float b, float a) {
	// Sets the clear color to a specific color defined by parameters
	glClearColor(r, g, b, a);
	// Will clear the buffer and introduce the colors defined above
	glClear(GL_COLOR_BUFFER_BIT);
}

void display_Update(struct Display* D_input) {
	// Swaps the two buffers
	SDL_GL_SwapWindow(D_input->main_Window);

	// Declare possible SDL_Event e
	SDL_Event e;
	
	// Check for SDL_Event
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			// This tells us that the display has sent an SDL_QUIT event
			D_input->main_IsClosed = true;
		}
	}
}

bool display_IsClosed(struct Display* D_input) {
	// Simply returns the value of the boolean main_isClosed
	return D_input->main_IsClosed;
}