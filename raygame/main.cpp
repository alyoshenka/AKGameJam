#include "raylib.h"
#include "menuState.h"

// #include "tutorial3State.h"
#include "testState.h"

#include <string>

// addCollision()
// how should i do physics?

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 960;
	int screenHeight = 560;

	InitWindow(screenWidth, screenHeight, "AKGJ");

	/*gameState * stateInstance = new menuState();
	GameStates currentState = MAINMENU;*/
	gameState * stateInstance = new testState();
	GameStates currentState = TEST;

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// go to next state
		GameStates nextState = stateInstance->next();
		// if different state
		if (nextState != currentState) {
			// get new one
			delete stateInstance;
			// set up new one
			setupGameState(stateInstance, nextState);
			// make new = current
			currentState = nextState;
			continue;
		}

		// update state
		stateInstance->update();

		BeginDrawing();
		ClearBackground(BLACK);

		stateInstance->draw();

		std::string pos = std::to_string((int)GetMouseX()) + ", " + std::to_string((int)GetMouseY());
		DrawText(pos.c_str(), GetMouseX(), GetMouseY() - 10, 10, WHITE);

		EndDrawing();
	}

	// De-Initialization

	delete stateInstance;

	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}