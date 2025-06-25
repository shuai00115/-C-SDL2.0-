#ifndef USER_H
#define USER_H

#include "common.h"

int isUserValid(UserData *user);
int registerUser(UserData *user);
void saveUserData(UserData *user);
int loadUserData(UserData *user);

#endif