#ifndef gameengine_h
#define gameengine_h

#include <vector>
#include <functional>
#include <memory>
#include "kiss_sdl/kiss_sdl.h"
#include "rendermanager.h"

struct RWCloser { void operator()(SDL_RWops *p) const { if(p) SDL_RWclose(p); } };

class GameState;

class GameEngine : public std::enable_shared_from_this<GameEngine>
{
	private:
		SDL_Event event;
        bool running;
        //SDL_RWops* saveFile;

		std::unique_ptr<SDL_RWops, RWCloser> saveFile;
		//std::shared_ptr<SDL_RWops> saveFile;
        std::shared_ptr<GameState> currentState;
        std::vector<std::shared_ptr<GameState>> states;

    public:
		std::shared_ptr<RenderManager> rend;

		bool Init();

		void Cleanup();

		std::unique_ptr<SDL_RWops, RWCloser> OpenFile(const char *fname, const char *mode);

		int ReadSave();

		void Save(int Highlevel);

		void ToSinglePlayer();

		void ToHighscore();

		void ChangeState(std::shared_ptr<GameState> state);

		void PushState(std::shared_ptr<GameState> state);

		void PopState();

		void PopStateS();

		std::shared_ptr<RenderManager> GetRend();

		void HandleEvents();

		void Update();

		void Draw();

		bool Running() { return running; }

		void Quit() { running = false; }
};

#endif
