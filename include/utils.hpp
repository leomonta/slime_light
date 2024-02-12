#pragma once

#include <stddef.h>

/**
 * Checks if two string are equals from the start of both.
 *
 * @oaram lhs leftHandSide
 * @oaram rhs rightHandSide
 * @return true if the two strings are equal, false otherwise
 */
bool streq(const char *lhs, const char *rhs);

/**
 * Checks if two string are equals while only checking at most count characters from str
 *
 * @oaram str the non null terminated string
 * @param len the length of the str
 * @oaram nts the null terminated string
 * @return true if the two strings are equal, false otherwise
 */
bool strneq(const char *str, const size_t count, const char *nts);

/**
 * Given a string of at least count characters returns the pointer to the str where the character chr has been found
 *
 * @param str the string to search into
 * @param chr the character to search
 * @param count the length of the str
 * @return the pointer to che found character in the given string, nullptr if not found
 */
const char *strnchr(const char *str, const char chr, const size_t count);
