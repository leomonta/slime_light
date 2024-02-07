#include "main.h"

#include "input.h"

#include <raylib.h>

struct runtimeSettings {
	Camera2D camera;
	unsigned screenWidth;
	unsigned screenHeight;
};

void init(runtimeSettings *sett) {

	auto sh = GetScreenHeight();
	auto sw = GetScreenWidth();

	SetTraceLogLevel(LOG_ALL);
	// setup the window with a name
	InitWindow(sw, sh, "Slime Light");
	// ToggleFullscreen();

	sett->camera = (Camera2D){0};

	// try to enable vsync and 60fps still some screen tearing
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	// Lock the cursor at the center of the screen and hide it
	HideCursor(); // Disable also hides
	DisableCursor();
}

int main() {

	runtimeSettings settings;

	input_loadConfig(nullptr);

	init(&settings);

	while (!WindowShouldClose()) {

		ClearBackground(BLACK);

		BeginDrawing();
		{
			DrawFPS(10, 10);
			DrawRectangle(100, 100, 500, 800, WHITE);
		}
		EndDrawing();
	}

	CloseWindow();
}
