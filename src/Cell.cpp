#include "..\include\cell.hpp"

Cell::Cell(int pRow, int pColumn, const char* pText, SDL_Rect* pRect) : isChecked_(false), row_(pRow), column_(pColumn), rect_(pRect)
{
	size_t len = strlen(pText);
	text_ = new char[len + 1];
	Utils::stringCopy(text_, pText, len);
}

Cell::Cell() : isChecked_(false), row_(-1), column_(-1), text_(nullptr), rect_(nullptr)
{}

Cell::~Cell()
{
	delete rect_;
	delete text_;
}

const char* Cell::getText() const { return text_; }
SDL_Rect* Cell::getRect() const { return rect_; }

Cell::Cell(const Cell* pObject) : isChecked_(pObject->isChecked_), row_(pObject->row_), column_(pObject->column_), text_(pObject->text_)
{
	rect_ = new SDL_Rect;
	(*rect_) = { pObject->rect_->x, pObject->rect_->y, pObject->rect_->w, pObject->rect_->h };
}

void Cell::set(bool pIsChecked, int pRow, int pColumn, const char* pText, SDL_Rect* pRect)
{
	isChecked_ = pIsChecked;
	row_ = pRow;
	column_ = pColumn;
	size_t len = strlen(pText);
	text_ = new char[len+1];
	Utils::stringCopy(text_, pText, len);
	rect_ = pRect;
}