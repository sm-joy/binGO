#pragma once
#include<SDL.h>

#include "utils.hpp"

class Cell
{
public:
	Cell();
	Cell(int pRow, int pColumn, const char* pText, SDL_Rect* pRect);
	Cell(const Cell* pObject);
	~Cell();
	const char* getText() const;
	SDL_Rect* getRect() const;
	void set(bool pIsChecked, int pRow, int pColumn, const char* pText, SDL_Rect* pRect);
private:
	bool isChecked_;
	int column_;
	int row_;
	char* text_;
	SDL_Rect* rect_;
};

