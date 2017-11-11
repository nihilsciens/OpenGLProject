/**********************************************
* The following file defines a Shader for use *
***********************************************/

// Make sure this header isn't already included
#ifndef SHADER_H
#define SHADER_H

// This shader is of type 2: fragment shader and vertex shader
#define NUM_SHADERS 2

// For the function LoadShader: assume maximum file length
#define MAX_LENGTH 128

// The necessary libraries
#include <GL\glew.h>

/*
*	Contains the necessary variables and types of a Shader.
*	@variables:
*		main_Program: Unsigned integer handle for OpenGL to keep track of program.
*		main_Shaders: 
*/
struct Shader {
	GLuint main_Program;
	GLuint main_Shaders[NUM_SHADERS];
};

/*
*	The Shader constructor will return a new active, usable display.
*	@parameters:
*		fileName: Character 'string' pointer for the file name to read.
*	@return:
*		A shader pointer of type struct Shader.
*/
struct Shader* shader_Constructor(char* fileName);

/*
*	The shader destructor deconstructs and turns off the shader.
*	@parameters:
*		S_input: The shader as a Shader struct pointer.
*/
void shader_Destructor(struct Shader* S_input);

/*
*	Binds the GPU to this shader type. If any other shader is
*	already bound to the GPU, unbind first.
*/
void shader_Bind();

/*
*	Loads a text from harddrive, converts it to a character pointer
*	and returns it to the caller.
*	@parameter:
*		fileName: character pointer for file name to read.
*	@return:
*		character pointer for the text in the file.
*/
char* shader_LoadShader(char* fileName);

#endif