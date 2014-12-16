// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#include "Events.h"
#include "gl/Program.h"
#include "Mesh.h"
#include "Menu.h"

int main(int argc, char *argv[])
{
	// gameloop when false will quit the program
	bool gameloop = initSDL();
	// setup delta time
	initTimerDT();
	// create win
	Window window;
	// set window title
	window.setTitle("Lewis Ward's Game");
	// setup Glew
	initGlew();

	// enable OpenGL 2D textures
	glEnable(GL_TEXTURE_2D);


	// create shaders
	gls::Shader vertexShader("shaders/menu.vtx.glsl", gls::sVERTEX);
	gls::Shader fragmentShader("shaders/menu.pix.glsl", gls::sFRAGMENT);
	// create program
	gls::Program program;
	program.create(&vertexShader, &fragmentShader);
	// load texture
	Texture texture("images/image.bmp");

	gui::Menu mainMenu(texture.texture());
	gui::Menus menus(mainMenu);

	// create event handler
	EventHandler events;

	// stores delta time
	float dt;

	// updating and drawing the game takes place
	while(gameloop)
	{
		// update delta time
		dt = updateTimerDT();

		// update SDL events
		int i = events.update();
		if(i > 0) std::cout<<i<<"\n";
		// has the user clicked on the quit button
		gameloop = events.playState();

		// clear the colour and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind program
		program.bind();
			// draw menu
			menus.draw();
		// unbind program and texture
		program.unbind();

		// swap the SDL window (SDL's version of glutSwapBuffer)
		SDL_GL_SwapWindow(window.getWindow());
	}

	menus.~Menus();
	// delete shaders
	vertexShader.~Shader();
	fragmentShader.~Shader();
	// delete program
	program.~Program();
	// delete window
	window.~Window();
	// quit SDL
	SDL_Quit();
	// quit program
	return 0;
}
