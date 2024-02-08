#include "input.h"

#include "constants.h"
#include "utils.h"

#include <errno.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *GAMEPLAY_KEYS_STR[KANY + 1] =
    {"KCONFIRM",
     "KCANCEL",
     "KUP",
     "KDOWN",
     "KLEFT",
     "KRIGHT",
     "KINTERACT",
     "KPICKUP",
     "KINVETORY",
     "KMENU",
     "KANY"};

typedef struct {
	int  translationTable[KANY];
	char inputOrigin[KANY];
} keyConfig;

keyConfig currentConfig;

int input_loadConfig(const char *filepath) {

	// -------------------------------------------------------------------------------------------- read file

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

	// -------------------------------------------------------------------------------------------- parse file

	// read 256 characters from the file
	char buffer[INPUT_CONFIG_FILE_SIZE] = {0};

	unsigned pos     = 0;
	int      key     = KANY;
	int      rlKcode = KEY_NULL;

	// search file line by line
	while (true) {

		if (fgets(buffer, INPUT_CONFIG_FILE_SIZE, configFile) == nullptr) {
			break;
		}

		auto temp = strnchr(buffer, ':', INPUT_CONFIG_FILE_SIZE);
		// nothing to see here anymore
		if (temp == nullptr) {
			break;
		}

		// before the ':'
		pos = temp - buffer;

		for (int i = 0; i < KANY; ++i) {
			if (strneq(buffer, pos, GAMEPLAY_KEYS_STR[i])) {
				key = i;
				break;
			}
		}

		temp = strnchr(&buffer[pos], '-', INPUT_CONFIG_FILE_SIZE - pos);

		if (temp == nullptr) {
			continue;
		}
		char medium = *(--temp);

		pos = temp - buffer;

		// no know key found
		if (key == KANY) {
			continue;
		}
		// +2 to skip the medium and the dash

		rlKcode = atoi(&buffer[pos + 2]);

		currentConfig.translationTable[key] = rlKcode;
		currentConfig.inputOrigin[key]      = medium;
	}

	// -------------------------------------------------------------------------------------------- close file

	fclose(configFile);
	return 0;
}

int input_writeConfig(const char *filepath) {
}

bool input_isPressed(const GAMEPLAY_KEYS k) {
}
