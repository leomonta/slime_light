#pragma once

typedef struct runtimeEnv runtimeEnv;

/**
 * init raylib and other stuff
 *
 */
void init(runtimeEnv& sett);

void loop(runtimeEnv& sett);

void term(runtimeEnv& sett);
