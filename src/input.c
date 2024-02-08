#include "input.h"

#include "constants.h"
#include "utils.h"

#include <errno.h>
#include <raylib.h>
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
    "KINTERACT",
    "KPICKUP",
    "KINVETORY",
    "KMENU",
    "KANY",
};

const char GAMEPLAY_KEY_LEN[] = {
    8,
    7,
    3,
    5,
    5,
    6,
    9,
    7,
    9,
    5,
    4,
};

typedef struct {
	int  translationTable[KANY];
	char inputType[KANY];
} keyConfig;

keyConfig currentConfig;

int input_loadConfig(const char *filepath) {

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
	auto configFile = fopen(fname, "r");

	// file does not exist, err 1
	if (errno == ENOENT) {
		return 1;
	}

	// opening failed for other reasons, err 2
	if (errno != NO_ERR) {
		TraceLog(LOG_ERROR, "File opening failed -> %s\n", strerror(errno));
		fclose(configFile);
		return 2;
	}

	//
	// -------------------------------------------------------------------------------------------- parse file
	//

	memset(&currentConfig.inputType, 'k', KANY);

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

		auto temp = strnchr(buffer, ':', INPUT_BUFFER_SIZE);
		// nothing to see here anymore
		if (temp == nullptr) {
			break;
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
	}

	//
	// -------------------------------------------------------------------------------------------- close file
	//

	fclose(configFile);
	return 0;
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

	// file does not exist, err 1
	if (errno == ENOENT) {
		return 1;
	}

	// opening failed for other reasons, err 2
	if (errno != NO_ERR) {
		TraceLog(LOG_ERROR, "File opening failed -> %s\n", strerror(errno));
		fclose(configFile);
		return 2;
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
		char buffer[3] = {0};                                                          // temp buffer, more than 3 won't be needed ever
		auto sz        = snprintf(buffer, 3, "%d", currentConfig.translationTable[i]); // convert to string
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
}
