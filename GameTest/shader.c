#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

struct Shader* shader_Constructor(char* fileName) {
	return NULL;
}

void shader_Destructor(struct Shader* S_input) {

}

void shader_Bind() {

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
		// Check if expected maximum line length is true
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

	// Return the file as a char pointer
	return fileBuffer;
}