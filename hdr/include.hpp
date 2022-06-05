#pragma once

//Dependencies
#include <Glass/glass.hpp>
#include <Windows.h>

//Macros

#define mGetStyle(fullScreen) fullScreen ? sf::Style::Fullscreen :\
	sf::Style::Default

#define mMaxNumOfPoints 100
#define mMaxNumOfSegments 100 
#define mNumOfFonts 2

//Globals

extern int ticks; 
 
//Others
using std::vector; 