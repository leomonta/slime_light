#include "main.hpp"

#include "input.hpp"
#include "logger/logger.hpp"
#include "renderer.hpp"

struct runtimeEnv {
	std::unique_ptr<glfwWindow> win;
	unsigned screenWidth;
	unsigned screenHeight;
};

void init(runtimeEnv& sett) {

	// this creates the window by itself
	sett.win = createWindow();

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
	runtimeEnv settings;

	//input_loadConfig(nullptr);

	init(settings);

	loop(settings);

	term(settings);
	
	//~glfwWindow()

}

void loop(runtimeEnv& sett) {

	if (!sett.win->shouldClose()) {

		logger::log("ASD");

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


void term(runtimeEnv &sett) {
	//input_writeConfig(nullptr);

	destroyWindow(sett.win);
}
