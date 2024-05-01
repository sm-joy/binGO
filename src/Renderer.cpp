#include "..\include\Renderer.hpp"


Renderer::Renderer(const char* pWinTitle, int pWinWidth, int pWinHeight, const char* pWinIconPath, const char* pFontPath, int pFontSize) : window_(nullptr), renderer_(nullptr), winIcon_(nullptr), font_(nullptr)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";

	int imageFormates = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP ;
	if (!(IMG_Init(imageFormates) & imageFormates)) std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";

	if (TTF_Init() == -1) std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << "\n";

	window_ = SDL_CreateWindow(pWinTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pWinWidth, pWinHeight, SDL_WINDOW_SHOWN);
	if (window_ == nullptr)
	{
		sdlQuit();
		std::cerr << "Error initializing SDL_Window: " << SDL_GetError() << "\n";
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (renderer_ == nullptr)
	{
		sdlQuit();
		std::cerr << "Error initializing SDL_Renderer: " << SDL_GetError() << "\n";
	}
	
	if (pWinIconPath != nullptr) setWindowIcon(pWinIconPath);
	if (pFontPath != nullptr) 
	{
		if (pFontSize != 0) loadFont(pFontPath, pFontSize);
		else std::cerr << "Error: Font Path was given but no Font Size was give!\n";
	}
}


void Renderer::sdlQuit()
{
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}


void Renderer::clearWindow() { SDL_RenderClear(renderer_); }


void Renderer::destroyTextures()
{
	for (SDL_Texture* texture : loadedTextures_)
	{
		SDL_DestroyTexture(texture);
	}
	loadedTextures_.clear();
}


void Renderer::destroyProgram()
{
	destroyTextures();
	if (winIcon_ != nullptr) SDL_FreeSurface(winIcon_);
	if (window_ != nullptr) SDL_DestroyWindow(window_);
	if (renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
	if (font_ != nullptr) TTF_CloseFont(font_);
	sdlQuit();
}


void Renderer::displayWindow() { SDL_RenderPresent(renderer_); }


void Renderer::setRenderDrawColor(SDL_Color* pColor) { SDL_SetRenderDrawColor(renderer_, pColor->r, pColor->g, pColor->b, pColor->a);}


void Renderer::setBackgroundColor(SDL_Color* pColor) { setRenderDrawColor(pColor); clearWindow(); }


SDL_Texture* Renderer::loadTexture(const char* pFilePath)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer_, pFilePath);
	if (texture == nullptr) std::cerr << "Error Loading '" << pFilePath << "' Texture! Error: " << SDL_GetError() << "\n";
	else loadedTextures_.push_back(texture);
	return texture;
}


void Renderer::setWindowIcon(const char* pWinIconPath) 
{
	winIcon_ = IMG_Load(pWinIconPath);
	if (winIcon_ != nullptr) SDL_SetWindowIcon(window_, winIcon_);
	else std::cerr << "Error Loading '" << pWinIconPath << "' Icon! Error: " << SDL_GetError() << "\n";
}


void Renderer::renderRect(SDL_Rect* pRect, SDL_Color* pColor, bool pFilled)
{
	setRenderDrawColor(pColor);
	if (pFilled) SDL_RenderFillRect(renderer_, pRect);
	else SDL_RenderDrawRect(renderer_, pRect);
}


Renderer::~Renderer() { destroyProgram(); }

void Renderer::loadFont(const char* pFontPath, int pFontSize)
{
	font_ = TTF_OpenFont(pFontPath, pFontSize);
	if (font_ == nullptr) std::cerr << "Error Loading '" << pFontPath << "' Font! Error: " << SDL_GetError() << "\n";

}

void Renderer::renderText(const char* pText, int pPosX, int pPosY, SDL_Color* pColor)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font_, pText, *pColor);
	if (textSurface == nullptr)
	{
		std::cerr << "Cannot Render ttf_rendertext_solid! Error: " << SDL_GetError() << "\n";
		return;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
	if (textTexture == nullptr)
	{
		std::cerr << "Cannot convert surface to texture! Error: " << SDL_GetError() << "\n";
		SDL_FreeSurface(textSurface);
		return;
	}

	renderTexture(textTexture, pPosX, pPosY, textSurface->w, textSurface->h);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void Renderer::renderTextCenterRect(const char* pText, SDL_Color* pColor, SDL_Rect* pRect)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font_, pText, *pColor);
	if (textSurface == nullptr)
	{
		std::cerr << "Cannot Render ttf_rendertext_solid! Error: " << SDL_GetError() << "\n";
		return;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
	if (textTexture == nullptr)
	{
		std::cerr << "Cannot convert surface to texture! Error: " << SDL_GetError() << "\n";
		SDL_FreeSurface(textSurface);
		return;
	}

	int x = pRect->x + (pRect->w - textSurface->w) / 2;
	int y = pRect->y + (pRect->h - textSurface->h) / 2;


	renderTexture(textTexture, x, y, textSurface->w, textSurface->h);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}


void Renderer::renderTexture(SDL_Texture* pTexture, int pPosX, int pPosY, int pTextureWidth, int pTextureHeight)
{
	SDL_Rect destinationRect = { pPosX, pPosY, pTextureWidth, pTextureHeight };
	SDL_RenderCopy(renderer_, pTexture, nullptr, &destinationRect);
}