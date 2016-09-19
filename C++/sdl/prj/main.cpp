//main file
//include sdl
#include <SDL2/SDL.h>
//includes librairies
#include <iostream>
#include <stdio.h>
//includes fichiers

/*********constantes**********/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
/*****************************/

//Starts up SDL and creates window
bool init();

//Frees memory and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gScreenSurface );
	gScreenSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]){

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Fill the surface white
		SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF ) );
		
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );

		//Wait two seconds
		SDL_Delay( 2000 );
	}

	//Free resources and close SDL
	close();


	std::cout<<"Hello World\n";
	return 0;
}