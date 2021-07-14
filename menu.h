#ifndef menu_h
#define menu_h

#include "gamestate.h"

class Menu : public GameState
{
	private:
		kiss_button buttonStart;
		kiss_button buttonHighscore;
		kiss_button buttonExit;
		SDL_Event event;
		SDL_Rect text_rect;// = { 0, 0, texW, texH };
		SDL_Texture * texture;
		std::function<void()> nextStateCallback;
		std::function<void()> quitCallback;
		std::shared_ptr<RenderManager> rend;

	public:
		bool Init(GameEngine* game);

		void Update(GameEngine* game);

		void HandleEvents(GameEngine* game);

		void setNextStateCallback(std::function<void()> callback)
                {nextStateCallback = callback;};

		void setQuitCallback(std::function<void()> callback)
                {quitCallback = callback;};

		void DrawLabel(std::shared_ptr<RenderManager>& rend, int x, int y);

		void Draw(std::shared_ptr<RenderManager>& rend);
};

#endif
