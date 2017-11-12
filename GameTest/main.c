#include <stdlib.h>
#include <stdio.h>
#include <GL\glew.h>

// Personal header files
#include "display.h"
#include "shader.h"


int wmain(int argc, char* argv[]) {

	// Construct a new Display
	struct Display* my_Display = display_Constructor(800, 600, "This is my title!");

	// Create new Shader
	struct Shader* my_Shader = shader_Constructor("./res/basicShader");

	// Will be active for as long as the display is active
	while (!display_IsClosed(my_Display)) {
		// Clear the display with chosen color
		display_Clear(0.0f, 0.05f, 0.3f, 0.1f);
		// Bind shader
		//shader_Bind(my_Shader);
		// Update the Display
		display_Update(my_Display);
	}

	// Destruct the Display
	display_Destructor(my_Display);

	// Quit program
	return 0;
}