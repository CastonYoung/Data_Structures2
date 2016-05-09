#pragma once
#ifndef STDAFX
#define STDFAX

#include <iostream>
#include <string>
#include <climits>//<limits.h> + <yvals.h>
#include <conio.h>//For _getch();

#define DEBUGPAUSE _getch();	//ON
#define TYPE char
#define CAST(type, data) reinterpret_cast< type >(reinterpret_cast<void*>( data ))

#ifndef ORF
#define ORF else if
#endif
const int NNUL = INT_MIN;//194
const std::string OoB("Error: Out of Bounds.\n");
const std::string AF ("Error: allocation failure.\n");

#include "List.h"
#include "ArrayListStack.h"
#include "ArrayList.h"
#include "ArrayStack.h"
#include "Linked List.h"

#endif