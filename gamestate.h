#ifndef gamestate_h
#define gamestate_h

//#include <functional>
#include "gameengine.h"

class GameState
{
	private:
		RenderManager* rend;

    public:
		//GameState();
		//~GameState();

		virtual bool Init(GameEngine* game) = 0;

		virtual void HandleEvents(GameEngine* game) = 0;

		//virtual void Pause();
		//virtual void Resume();

		virtual void Update(GameEngine* game) = 0;

		//virtual void Draw(GameEngine* game) = 0;

		virtual void Draw(std::shared_ptr<RenderManager>& rend) = 0;
};

#endif
