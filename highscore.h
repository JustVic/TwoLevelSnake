#ifndef highscore_h
#define highscore_h

#include "gamestate.h"

class Highscore : public GameState
{
	private:
		int Highlevel;
		std::string HighlevelStr;
		kiss_button buttonBack;
		kiss_label HighscoreLabel;
		SDL_RWops* saveFile;
		SDL_Event event;
		std::shared_ptr<SDL_Texture> cupTexture;
		std::shared_ptr<RenderManager> rend;
		int centerW;
		int centerH;
		int screenWidth;
		int screenHeight;

	public:
		bool Init(GameEngine* game);

		void Update(GameEngine* game);

		void HandleEvents(GameEngine* game);

		void DrawLabel(std::shared_ptr<RenderManager>& rend, int x, int y, int
					   w, int h);

		void Draw(std::shared_ptr<RenderManager>& rend);
};

#endif
