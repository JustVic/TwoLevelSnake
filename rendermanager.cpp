#include "rendermanager.h"

int draw = 1;

RenderManager::RenderManager()
{
	SDL_Rect srect;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GetDisplayBounds(0, &srect);

	width = srect.w;
	height = srect.h;

	cellWidth = width/20;
	if((cellWidth%2))
		cellWidth-=1;

	//kiss_setup_fontsize(8,9);

	renderer = kiss_init("Snaky 1", &objects, width,
                                         height);
	if (!renderer)
		printf( "Could not initialize renderer! SDL_Error: %s\n", SDL_GetError());

	kiss_window_new(&window1, NULL, 1, 0, 0, kiss_screen_width,
 kiss_screen_height);

	std::cout << "width: " << kiss_screen_width << "\n";
	std::cout << "height: " << kiss_screen_height << "\n";

	window1.visible = 1;

	SDL_SetRenderDrawColor(renderer, 25, 255, 255, 255);
}

SDL_Renderer* RenderManager::GetSDLRenderer()
{
	return renderer;
}

std::shared_ptr<SDL_Texture> RenderManager::createTexture(std::string image)
{

    //SDL_Surface* surface = SDL_LoadBMP(image.c_str());
	std::shared_ptr<SDL_Surface> surface = std::shared_ptr<SDL_Surface>(SDL_LoadBMP(image.c_str()), SDL_FreeSurface);

	std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(this->renderer, surface.get()), SDL_DestroyTexture);

	//SDL_FreeSurface(surface);

	return texture;
}


void RenderManager::DrawTexture(SDL_Texture* texture, int x, int y)
{
	int s = width%(width/cellWidth);
	int z = height%(width/(width/cellWidth));

	SDL_Rect rect;
	rect.w = cellWidth;
	rect.h = rect.w;
	rect.x = (rect.w * x)+s/2;
	rect.y = (rect.h * y)+z/2;

	SDL_RenderCopy(this->renderer, texture, NULL, &rect);
}

void RenderManager::DrawTexture(SDL_Texture* texture, int x, int y, int w, int h)
{
	int s = width%(width/cellWidth);
	int z = height%(width/(width/cellWidth));

	SDL_Rect rect;
	rect.w = cellWidth/2;
	rect.h = rect.w;
	rect.x = (rect.w * x)+s/2;
	rect.y = (rect.h * y)+z/2;

	SDL_RenderCopy(this->renderer, texture, NULL, &rect);
}

void RenderManager::DrawTextureReal(SDL_Texture* texture, int x, int y, int w, int h)
{

	int s = width%(width/cellWidth);
	int z = height%(width/(width/cellWidth));

	SDL_Rect rect;
	rect.w = w;
	rect.h = h;
	rect.x = x+s/2;
	rect.y = y+z/2;

	SDL_RenderCopy(this->renderer, texture, NULL, &rect);
}

void RenderManager::Update()
{
	SDL_RenderPresent(this->renderer);
}

void RenderManager::Delay()
{
	SDL_Delay(2000);
}

void RenderManager::Cleanup()
{
	kiss_clean(&objects);

	SDL_Quit();
}
