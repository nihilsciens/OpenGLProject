#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Shader* shader_Constructor(char* fileName) {
	// Define new struct pointer of type Shader
	struct Shader* S = malloc(sizeof(struct Shader));

	// Create new main program
	S->main_Program = glCreateProgram();

	// Prepare the text file character pointers
	size_t needed = snprintf(NULL, 0, "%s.fs", fileName) + 1;
	char* vertexName = malloc(needed);
	char* fragmentName = malloc(needed);
	snprintf(vertexName, needed, "%s.vs", fileName);
	snprintf(fragmentName, needed, "%s.fs", fileName);

	/*
	* Create Shader[0] vertex shader and Shader[1] fragment shader.
	* The file convention is same name for vertex and fragment shader
	* with the exception of file extension *.vs and *.vf.
	*/
	S->main_Shaders[0] = shader_CreateShader(S, shader_LoadShader(vertexName), GL_VERTEX_SHADER);
	S->main_Shaders[1] = shader_CreateShader(S, shader_LoadShader(fragmentName), GL_FRAGMENT_SHADER);

	// Attach shaders to program
	for (int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(S->main_Program, S->main_Shaders[i]);

	/*
	* Tells OpenGL what part of the data to read,
	* important to do before linking and validating,
	* otherwise leads to nasty bugs in the future.
	*/
	glBindAttribLocation(S->main_Program, 0, "position");

	// Link the program and check if program failed to link shader to program
	//############# THERE IS AN ERROR HERE ##############
	glLinkProgram(S->main_Program);
	shader_CheckError(S->main_Program, GL_LINK_STATUS, true, "Error: Program link failure");

	// Validate the program and check if program is actually usable
	glValidateProgram(S->main_Program);
	shader_CheckError(S->main_Program, GL_VALIDATE_STATUS, true, "Error: Program invalid failure");

	// Return new Shader struct pointer
	return S;

}

void shader_Destructor(struct Shader* S_input) {
	/*
	* Detaches and deletes every shader in S_input.
	* The shader struct should be defined by the constructor in this file,
	* otherise the NUM_SHADERS macro value may be incorrect and crashes.
	*/
	for (int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(S_input->main_Program, S_input->main_Shaders[i]);
		glDeleteShader(S_input->main_Shaders[i]);
	}

	// Deletes the program (does not delete shaders)
	glDeleteProgram(S_input->main_Program);

	// Frees the memory allocated to the Shader struct
	free(S_input);

}

void shader_Bind(struct Shader* S_input) {
	// Binds the program
	glUseProgram(S_input->main_Program);
}

char* shader_LoadShader(char* fileName) {
	// Declare file
	FILE* file;

	// Open file fileName for reading
	fopen_s(&file, fileName, "r");

	// Check if file is correctly opened
	if (file == NULL) {
		printf("Unable to open file!");
		// Close program
		return NULL;
	}

	// Allocate memory for the file
	int maximumLength = MAX_LENGTH;
	char *fileBuffer = (char *)malloc(sizeof(char) * maximumLength);

	// Read lines of file
	int count = 0;
	char ch = getc(file);

	// Make sure End of File not reached
	while (ch != EOF) {
		// Check if expected file length is true
		if (count == maximumLength) {
			// Recalibrate the maximum length
			maximumLength += 128;
			// Reallocate more memory for lineBuffer
			fileBuffer = realloc(fileBuffer, maximumLength);
			// Make sure reallocation was successful
			if (fileBuffer == NULL) {
				printf("Error reallocating space for line buffer.");
				// Close program
				return NULL;
			}
		}
		// Save character and prepare new
		fileBuffer[count] = ch;
		count++;
		ch = getc(file);
	}

	// Close file
	fclose(file);

	// Return the file text as a char pointer
	return fileBuffer;
}

// This method needs revisionary comments
void shader_CheckError(GLuint shader, GLuint flag, bool isProgram, char* errorMessage) {

	// Define placeholders
	GLint success;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
	}
	
	printf("%s: '%s'\n", errorMessage, error);
}

GLuint shader_CreateShader(struct Shader* S_input, char* text, GLenum shaderType) {

	// Define a new shader
	GLuint shader = glCreateShader(shaderType);

	// Check if OpenGL actually managed to create a shader
	if (shader == 0)
		printf("Shader creation error!");

	// Prepare specific GLchar* and GLint forms of parameters
	GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLength[1];
	shaderSourceStrings[0] = text;
	shaderSourceStringLength[0] = sizeof(text) / sizeof(char);

	// Send the shader to OpenGL
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
	
	// Compile the shader
	glCompileShader(shader);

	// Check for shader error
	shader_CheckError(S_input->main_Program, GL_COMPILE_STATUS, false, "Error: Shader compilation failure");

	// Return the shader
	return shader;

}