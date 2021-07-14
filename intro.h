#ifndef intro_h
#define intro_h

#include "gamestate.h"

class Intro : public GameState
{
	private:
		kiss_button button1;
		kiss_label hello;
		std::function<void()> nextStateCallback;
		SDL_Event event;
		std::shared_ptr<RenderManager> rend;

	public:
		bool Init(GameEngine* game);

		void Update(GameEngine* game);

		void setB2Callback(std::function<void()> callback)
                {nextStateCallback = callback;};

		void HandleEvents(GameEngine* game);

		void Draw(std::shared_ptr<RenderManager>& rend);
};

#endif
