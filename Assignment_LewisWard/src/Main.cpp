// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#include "Events.h"

// TODO:
// setTitle & setIcon

int main(int argc, char *argv[])
{
	// gameloop when false will quit the program
	bool gameloop = initSDL();

	// setup delta time
	initTimerDT();

	// create win
	Window win;
	// create event handler
	EventHandler events;

	initGlew();

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

		// draw simple triangle with OpenGL
		glBegin(GL_TRIANGLES);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(300.0f, 100.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(100.0f, 400.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(500.0f, 400.0f, 0.0f);
		glEnd();

		// swap the SDL window (SDL's version of glutSwapBuffer)
		SDL_GL_SwapWindow(win.getWindow());
	}

	// quit SDL
	SDL_Quit();
	// quit program
	return 0;
}