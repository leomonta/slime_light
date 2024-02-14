#include "main.hpp"

#include "input.hpp"
#include "logger/logger.hpp"

void init(VkState& sett) {

	// this creates the window by itself
	initVulkan(sett);

	/*
	// ToggleFullscreen();
	sett->camera = (Camera2D){0};

	// try to enable vsync and 60fps still some screen tearing
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	// Lock the cursor at the center of the screen and hide it
	HideCursor(); // Disable also hides
	DisableCursor();
	*/
}

int main() {
	VkState settings;

	//input_loadConfig(nullptr);

	init(settings);

	loop(settings);

	term(settings);
	
	//~glfwWindow() inside vkstate

}

void loop(VkState& sett) {

	if (!sett.win->shouldClose()) {

		/*
		ClearBackground(BLACK);

		BeginDrawing();
		{
			DrawFPS(10, 10);
			DrawRectangle(100, 100, 500, 800, WHITE);
		}
		EndDrawing();
		*/
	}


}


void term(VkState &sett) {
	//input_writeConfig(nullptr);

	termVulkan(sett);
}
