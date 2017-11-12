/**********************************************
* The following file defines a Shader for use *
***********************************************/

// Make sure this header isn't already included
#ifndef SHADER_H
#define SHADER_H

// Define primitive type boolean
#ifndef typedef bool
typedef int bool;
#define true 1
#define false 0
#endif

// // This shader implementation harbors two types of shaders: (0) vertex shader and (1) fragment shader
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
*	already bound to the GPU, unbinds them first.
*/
void shader_Bind(struct Shader* S_input);

/*
*	Loads a text from harddrive, converts it to a character pointer
*	and returns it to the caller.
*	@parameter:
*		fileName: character pointer for file name to read.
*	@return:
*		character pointer for the text in the file.
*/
char* shader_LoadShader(char* fileName);

/*
*	Identifies error messages and prints them out.
*	@parameter:
*		shader:
*		flag:
*		isProgram:
*		errorMessage:
*/
void shader_CheckError(GLuint shader, GLuint flag, bool isProgram, char* errorMessage);

/*
*	Creates a shader of a specific type and returns it as a GLuint.
*	@parameter:
*		text: The full text of our proposed shader.
*		shaderType: Defines which type of shader we wish to create.
*	@return:
*		The specific shader of type GLuint.
*/
GLuint shader_CreateShader(char* text, GLenum shaderType);

#endif