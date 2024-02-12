/*
#include "input.h"

#include "constants.h"
#include "utils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *GAMEPLAY_KEY_STR[] = {
    "KCONFIRM",
    "KCANCEL",
    "KUP",
    "KDOWN",
    "KLEFT",
    "KRIGHT",
    "KACTION",
    "KSECONDARY",
    "KINTERACT",
    "KPICKUP",
    "KINVETORY",
    "KMENU",
    "KANY",
};

const char GAMEPLAY_KEY_LEN[] = {
    8,  // KCONFIRM
    7,  // KCANCEL
    3,  // KUP
    5,  // KDOWN
    5,  // KLEFT
    6,  // KRIGHT
    7,  // KACTION
    10, // KSECONDARY
    9,  // KINTERACT
    7,  // KPICKUP
    9,  // KINVETORY
    5,  // KMENU
    4,  // KANY
};

typedef struct {
	int   translationTable[KANY + 1];
	char  inputType[KANY + 1];
	float threshold[KANY + 1];
	int   gamepad;
} keyConfig;

keyConfig currentConfig;

const keyConfig defaultConfig = {
    {KEY_ENTER, KEY_ESCAPE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_R, KEY_E, KEY_P, KEY_I, KEY_ESCAPE, KEY_NULL},
    {'k',       'k',        'k',    'k',      'k',      'k',       'k',       'k',   'k',   'k',   'k',   'k',        'k'     },
    {0.f,       0.f,        0.f,    0.f,      0.f,      0.f,       0.f,       0.f,   0.f,   0.f,   0.f,   0.f,        0.f     },
    0
};

int input_loadConfig(const char *filepath) {

	//
	// -------------------------------------------------------------------------------------------- read file
	//

	int         res   = 0;
	const char *fname = INPUT_CONFIG_FILE;

	if (filepath != nullptr) {
		fname = filepath;
	}

	// I use errno to check for errors
	// just to be sure
	errno = NO_ERR;

	// open and create if does not exists
	auto configFile = fopen(fname, "a+");

	// opening failed for other reasons
	if (errno != NO_ERR || configFile == NULL) {
		TraceLog(LOG_ERROR, "Input config file opening failed -> %s\n", strerror(errno));
		return 1;
	}

	//
	// -------------------------------------------------------------------------------------------- parse file
	//

	currentConfig = defaultConfig;

	// read 256 characters from the file
	char buffer[INPUT_BUFFER_SIZE] = {0};

	unsigned pos     = 0;
	int      key     = KANY;
	int      rlKcode = KEY_NULL;

	// search file line by line
	while (true) {

		if (fgets(buffer, INPUT_BUFFER_SIZE, configFile) == nullptr) {
			break;
		}

		if (errno != NO_ERR) {
			TraceLog(LOG_ERROR, "Input config file read failed -> %s\n", strerror(errno));
			res = 1;
			break;
		}

		auto temp = strnchr(buffer, ':', INPUT_BUFFER_SIZE);
		// empty line it seems
		if (temp == nullptr) {
			continue;
		}

		// before the ':'
		pos = temp - buffer;

		for (int i = 0; i < KANY; ++i) {
			if (strneq(buffer, pos, GAMEPLAY_KEY_STR[i])) {
				key = i;
				break;
			}
		}

		// no know key found
		if (key == KANY) {
			continue;
		}

		temp = strnchr(&buffer[pos], '-', INPUT_BUFFER_SIZE - pos);

		if (temp == nullptr) {
			continue;
		}

		char medium = *(--temp);

		// just switch it, it's easier
		switch (medium) {
		case KEYBOARD:
		case GAMEPAD:
		case MOUSE:
		case AXIS:
			break;

		// unknown type? next line please
		default:
			continue;
		};

		pos = temp - buffer;

		// +2 to skip the medium and the dash
		rlKcode = atoi(&buffer[pos + 2]);

		currentConfig.translationTable[key] = rlKcode;
		currentConfig.inputType[key]        = medium;

		// read threshold if the input is a gamepad axis
		if (medium != AXIS) {
			continue;
		}

		temp = strnchr(&buffer[pos], '-', INPUT_BUFFER_SIZE - pos);

		float ts = atof(&buffer[pos]);
	}

	//
	// -------------------------------------------------------------------------------------------- close file
	//

	fclose(configFile);
	return res;
}

int input_writeConfig(const char *filepath) {

	//
	// -------------------------------------------------------------------------------------------- read file
	//

	const char *fname = INPUT_CONFIG_FILE;

	if (filepath != nullptr) {
		fname = filepath;
	}

	// just to be sure
	errno = NO_ERR;

	// I use errno to check for errors
	auto configFile = fopen(fname, "w");

	// opening failed for other reasons, err 2
	if (errno != NO_ERR || configFile == NULL) {
		TraceLog(LOG_ERROR, "File opening failed -> %s\n", strerror(errno));
		return 1;
	}

	//
	// -------------------------------------------------------------------------------------------- write file
	//

	// not the most efficient implementation
	// but should be fine for 10 rows with a fistful of characters
	for (int i = 0; i < KANY; ++i) {

		fwrite(GAMEPLAY_KEY_STR[i], 1, GAMEPLAY_KEY_LEN[i], configFile);               // GAMEPLAY key
		fwrite(": ", 1, 2, configFile);                                                // :
		fwrite(&currentConfig.inputType[i], 1, 1, configFile);                         // input type
		fwrite("-", 1, 1, configFile);                                                 // -
		char buffer[4] = {0};                                                          // temp buffer, more than 3 won't be needed ever, the +1 is needed for the '\0'
		auto sz        = snprintf(buffer, 4, "%d", currentConfig.translationTable[i]); // convert to string
		fwrite(buffer, 1, sz, configFile);                                             // raylib keycode
		fwrite("\n", 1, 1, configFile);                                                // newline
	}

	//
	// -------------------------------------------------------------------------------------------- close file
	//

	fclose(configFile);
	return 0;
}

bool input_isPressed(const GAMEPLAY_KEY k) {

	switch (currentConfig.inputType[k]) {
	case KEYBOARD:
		return IsKeyPressed(currentConfig.translationTable[k]);
		break;

	case GAMEPAD:
		return IsGamepadButtonPressed(currentConfig.gamepad, currentConfig.translationTable[k]);
		break;

	case MOUSE:
		return IsMouseButtonPressed(currentConfig.translationTable[k]);
		break;

	case AXIS:
		return GetGamepadAxisMovement(currentConfig.gamepad, currentConfig.translationTable[k]) > currentConfig.threshold[k];
		break;
	}
}*/
