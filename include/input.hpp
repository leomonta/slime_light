/*
 * Interface to make the program independent from the keys configured or the input method
 *
 * The program only needs to ask the input module if a specific Action (Ksomething) has been performed
 * This supports only degital (yes no) actions, but allows for analog devices (e.g. gamepad's sticks)
 *
 * TODO: read configuration from file
 * TODO: write configuration to file
 * TODO: allow remapping
 * TODO: abstract away gamepad / keyboard
 * TODO: deal with buffering
 *  - Just ask IsKeyPressed() under the hood ?
 *  - use IsKeyDown() instead ?
 *  - maintain a buffer internally ?
 *    - keep inputs forever ?
 *    - keep inputs for n frames ?
 *    - keep inputs for n milliseconds ?
 * TODO: deal with analog inputs
 * TODO: decide config file format
 *   - TOML
 *   - YAML <- this for now, at least the basic key: value
 *   - JSON
 *   - Binary
 *   - Rawdog
 *
 *

#pragma once

typedef enum : char {
	KCONFIRM,   // Confirm menu choices, advances dialogs
	KCANCEL,    // Deny menu choices, interrupt dialogs
	KUP,        // Move up in game and in menu
	KDOWN,      // Move down in game and in menu
	KLEFT,      // Move left in game and in menu
	KRIGHT,     // Move right game and in menu
	KACTION,    // Attack, use weapon
	KSECONDARY, // activate weapon secondary effect
	KINTERACT,  // Touch, use, talk to entities in game FIXME: might be merged with KCONFIRM
	KPICKUP,    // Pucks up an item from the ground, TODO: DO NOT MERGE WITH KINTERACT FOR GOD SAKE
	KINVETORY,  // Open Bag / Inventory / Portable hole
	KMENU,      // Open and closes the game menu
	KANY        // unknown or other key pressed
} GAMEPLAY_KEY;

typedef enum : char {
	KEYBOARD = 'k',
	GAMEPAD  = 'g',
	MOUSE    = 'm',
	AXIS     = 'a',
} INPUT_TYPE;

**
 * Reads the configured keys form the given file,
 * if the filepath is nullptr the default "keyconfig" on the current directory will be used
 *
 *
 * @param filepath the file where to read the configuration from, if nullptr the dafult filepath will be used
 * @return 0 if success, > 0 otherwise
 *
int input_loadConfig(const char *filepath);

**
 * Writes the current configuration to the given file, if filepath is nullptr the default file will be used
 *
 * @param filepath the file where to write the configuration to, if nullptr the default filepath will be used
 * @return 0 if success, 1 otherwise
 *
int input_writeConfig(const char *filepath);

**
 * Returns if the given ket has been pressed
 *
 * @param k the the to check for
 * @return true if pressed, false otherwise
 *
bool input_isPressed(const GAMEPLAY_KEY k);
*/
