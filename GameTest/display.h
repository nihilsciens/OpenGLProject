/************************************************
 * The following file defines a Display for use *
 ************************************************/

// Make sure this header isn't already included
#ifndef DISPLAY_H
#define DISPLAY_H

// Define primitive type boolean
typedef int bool;
#define true 1
#define false 0

// The necessary libraries
#include <include\SDL.h>

 /*
 *	Contains the necessary variables and types of a Display.
 *	@variables:
 *		main_Window: A pointer to the SDL_Window* object.
 *		main_GLContext: The SDL_GLContext object used by GLEW.
 *		main_isClosed: Boolean for the activity of the main window.
 */
struct Display {
	SDL_Window* main_Window;
	SDL_GLContext main_GLContext;
	bool main_IsClosed;
};

/*
*	The Display constructor will return a new active, usable display.
*	@parameters:
*		width: width of the display window.
*		height: height of the display window.
*		title: window title as a char pointer.
*	@return:
*		A display pointer of type struct Display.
*/
struct Display* display_Constructor(int width, int height, char* title);

/*
*	The Display destructor deconstructs and turns off the display.
*	Nothing fancy, simply makes the display non-usable.
*	@parameters:
*		D_input: The display as a Display struct pointer.
*/
void display_Destructor(struct Display* D_input);

/*
*	Used for swapping buffers between Window and the one OpenGL is working on.
*	Explanation: A window [should] never display what is being drawed by
*	OpenGL at any time, thus a separate buffer can be worked on by OpenGL.
*	These buffers are switched frequently, causing the window to update.
*	@parameters:
*		D_input: The display as a Display struct pointer.
*/
void display_Update(struct Display* D_input);

/*
*	Clears the buffer and enters them into second display.
*	@parameters:
*		r: red color.
*		g: green color.
*		b: blue color.
*		a: alpha, transparency.
*/
void display_Clear(float r, float g, float b, float a);

/*
*	Will simply return the value of the main_isClosed boolean.
*	@parameters:
*		D_input: The display as a Display struct pointer.
*	@return:
*		Reuturns integer value 1 for true and 0 for false (primitive boolean).
*/
bool display_IsClosed(struct Display* D_input);

#endif