#include "..\include\Core.hpp"
#include "..\include\settings.hpp"
#include "..\include\utils.hpp"

Core::Core() :
    renderer_(Settings::winTitle, 
    Settings::winWidth, 
    Settings::winHeight, 
    Settings::iconPath, 
    Settings::fontPath, 
    Settings::fontSize), 
    event_{}
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            SDL_Rect* rect = new SDL_Rect;
            (*rect) = { j * Settings::cellWidth, i * Settings::cellHeight, Settings::cellWidth, Settings::cellHeight };
            //have to implement random numbers for cell 0,0 to 4,4

            cells_[i][j].set(false, i, j, "Hello", rect);
        }
    }
}




void Core::run()
{
        while (true)
        {
            while (SDL_PollEvent(&event_))
            {
                if (event_.type == SDL_QUIT) return;
            }

            renderer_.setBackgroundColor(&white);

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    renderer_.renderTextCenterRect(cells_[i][j].getText(), &black, cells_[i][j].getRect());
                }
            }
            renderer_.displayWindow();
        }
}
	