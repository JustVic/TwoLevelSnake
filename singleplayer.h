#ifndef singleplayer_h
#define singleplayer_h

#include "gamestate.h"

enum type { WALL, TELEPORT, NOM_NOM };

struct Block
{
    int x;
    int y;
    int z;
    type tp;
};

class Singleplayer : public GameState
{
	private:
		//std::vector<SDL_Rect> snk;
		std::vector<Block> snk;

		//SDL_Rect nom_nom;
		Block nom_nom;
		std::vector<Block> walls;
		std::vector<Block> field;

		//std::vector<SDL_Rect> movingObstacles;
		char scoreC[100] = "score ";
		kiss_label scoreLabel = {0};
		kiss_label score_Num = {0};
		std::string scoreStr;
		SDL_RWops* saveFile;
		Block teleportEnter;
		Block teleportExit;

        //SDL_Rect teleportEnter;
        //SDL_Rect teleportExit;
		bool teleportFlag;
        bool tFlag;
        int level;
        int score;
        int speed;
        int direction;
		int oldDirection;
        SDL_Event event;
        int frameStart;
        int frameEnd;
        int frameDuration;
		int width;
		int height;
		int cellWidth;
		int fieldWidth;
        std::function<void()> nextStateCallback;
        std::function<void()> quitCallback;
        //std::function<void()> nextCallback;
        std::shared_ptr<SDL_Texture> fruitTexture;
        std::shared_ptr<SDL_Texture> nom_nomTexture;
        std::shared_ptr<SDL_Texture> teleportTexture;
        std::shared_ptr<SDL_Texture> wallTexture;
		std::shared_ptr<SDL_Texture> backgroundTexture;

        std::shared_ptr<RenderManager> rend;

	public:
        bool Init(GameEngine* game);

        void Update(GameEngine* game);

        void HandleEvents(GameEngine* game);

        void GenerateNextRound();

        void Restart();

        SDL_Rect GenerateWallBlock();

        SDL_Rect GenerateNom_NomBlock();

        SDL_Rect GenerateTeleportBlocks();

        bool CheckSelfCollision();

		bool UpdateScore();


        void setNextStateCallback(std::function<void()> callback)
        {nextStateCallback = callback;};

        void DrawLabel(std::shared_ptr<RenderManager>& rend, int x, int
			       y, int z);
        void DrawNom_Nom(std::shared_ptr<RenderManager>& rend, int x,
				 int y, int z);
        void DrawWall(std::shared_ptr<RenderManager>& rend, int x, int
			      y, int z);

        void DrawTeleportEnter(std::shared_ptr<RenderManager>& rend, int x, int
                                  y, int z);

        void DrawTeleportExit(std::shared_ptr<RenderManager>& rend, int x, int
                                  y, int z);

        void DrawBackground(std::shared_ptr<RenderManager>& rend, int x, int y, int w, int h);

        void Draw(std::shared_ptr<RenderManager>& rend);
};

#endif
