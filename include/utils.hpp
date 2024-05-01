#pragma once

#include "Cell.hpp"

#include <random>
#include <string>
#include <iostream>


namespace Utils
{
	int randInt(int pMin, int pMax);
	void randIntToStr(int pMin, int pMax, const char* pString);
	bool isUnique(Cell** pCells, const char* pString);
	void print(std::vector<std::vector<std::string>>* pVector);
	void stringCopy(char* pDestination, const char* pSource, int limit);
};