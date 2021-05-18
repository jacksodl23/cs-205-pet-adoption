/*
 * Storing a global current User variable
 * Allows for keeping track of current User
 * logged in and for access to operate on that
 * User
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "user.h"

#define CRYPTO_KEY Q_UINT64_C(0xbfd0da17cd79b3a4)

extern User currentUser;

#endif // GLOBALS_H
