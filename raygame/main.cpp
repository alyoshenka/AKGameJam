#include "raylib.h"
#include "gameState.h"

int main()
{

	int i = 5;
	int * ip = &i;
	std::cout << i << std::endl;
	std::cout << &i << std::endl;
	std::cout << ip << std::endl;
	std::cout << &ip << std::endl;
	std::cout << *ip << std::endl;

	// return 0;

	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 960;
	int screenHeight = 560;

	InitWindow(screenWidth, screenHeight, "AKGJ");

	gameState gs = gameState::getInstance();

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		gs.go();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}