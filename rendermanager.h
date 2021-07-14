#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "kiss_sdl/kiss_sdl.h"
//#include <stdio.h>
#include <iostream>
#include <memory>


class RenderManager
{
	private:
		SDL_Renderer* renderer;
		int width;
		int height;
		int cellWidth;
		kiss_window window1;
		kiss_array objects;

	public:
		RenderManager();

		void Cleanup();

		void Update();

		void Delay();

		SDL_Renderer* GetSDLRenderer();

		kiss_window* GetWindow(){ return &window1; };

		int GetWidth(){ return width; };

		int GetHeight(){ return height; };

		int GetCellWidth(){ return cellWidth; };

		std::shared_ptr<SDL_Texture> createTexture(std::string image);

		void DrawSprite(int x, int y, int width, int height, SDL_Surface* sprite);

		void DrawRectangle(int x, int y, int width, int height, SDL_Surface* rectangle);

		void DrawTexture(SDL_Texture* texture, int x, int y);//, SDL_Rect rect);
		void DrawTexture(SDL_Texture* texture, int x, int y, int w, int
				 h);
		void DrawTextureReal(SDL_Texture* texture, int x, int y, int w, int
				 h);

};

