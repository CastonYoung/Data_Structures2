#pragma once
#ifndef STDAFX
#define STDFAX

#include <iostream>
#include <string>
#include <climits>//<limits.h> + <yvals.h>
#include <conio.h>//For _getch();

#define DEBUGPAUSE _getch();	//ON
#define TYPE char

const int NNUL = INT_MIN;//194
const std::string OoB("Error: Out of Bounds.\n");
const std::string AF ("Error: allocation failure.\n");
const std::string LNS("Error: There is no list yet.");
const std::string ENL("Error: An entry with that ID has not been listed.");
const std::string EAL("Error: An entry with that ID is already in the list.");

#include "List.h"
#include "ArrayListStack.h"
#include "ArrayList.h"
#include "Linked List.h"
#include "ArrayStack.h"

#endif