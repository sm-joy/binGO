#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>


class Renderer
{
public:
	Renderer(const char* pWinTitle, int pWinWidth, int pWinHeight, const char* pWinIconPath = nullptr, const char* pFontPath = nullptr, int pFontSize = 0);
	~Renderer();
	void clearWindow();
	void destroyProgram();
	void displayWindow();
	void setRenderDrawColor(SDL_Color* pColor);
	void setBackgroundColor(SDL_Color* pColor);
	SDL_Texture* loadTexture(const char* pFilePath);
	void destroyTextures();
	void setWindowIcon(const char* pWinIconPath);
	void renderRect(SDL_Rect* pRect, SDL_Color* pColor, bool pFilled = false);
	void sdlQuit();
	void loadFont(const char* pFontPath, int pFontSize);
	void renderText(const char* pText, int pPosX, int pPosY, SDL_Color* pColor);
	void renderTextCenterRect(const char* pText, SDL_Color* pColor, SDL_Rect* pRect);
	void renderTexture(SDL_Texture* pTexture, int pPosX, int pPosY, int pTextureWidth, int pTextureHeight);
private:
	SDL_Window *window_;
	SDL_Renderer* renderer_;
	TTF_Font* font_;
	SDL_Surface* winIcon_;
	std::vector<SDL_Texture*> loadedTextures_;
};