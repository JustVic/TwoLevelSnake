#include "gameengine.h"
#include "intro.h"
#include "menu.h"
#include "highscore.h"
#include "singleplayer.h"

#include <stdexcept>

extern int draw;

bool GameEngine::Init(void)
{
	std::shared_ptr<GameState> intro = std::shared_ptr<Intro>(new Intro);
	std::shared_ptr<GameState> menu = std::shared_ptr<Menu>(new Menu);

	//std::shared_ptr<GameState> singlePlayer = std::shared_ptr<Singleplayer>(new
    //                                                                    Singleplayer);

	rend = std::shared_ptr<RenderManager>(new RenderManager);

	if(!rend)
		return false;

	if(!intro->Init(this))
		return false;

    //if(!singlePlayer->Init(this))
	//	return false;

    if(!menu->Init(this))
		return false;

    //this->PushState(std::move(singlePlayer));

    this->PushState(std::move(menu));

    this->PushState(std::move(intro));

	running = true;

    return true;
}

std::shared_ptr<RenderManager> GameEngine::GetRend()
{
    return this->rend;
}

void GameEngine::ToSinglePlayer() {

	std::shared_ptr<GameState> singlePlayer = std::shared_ptr<Singleplayer>(new
                                                                        Singleplayer);

    singlePlayer->Init(this);

	this->PushState(std::move(singlePlayer));

}

void GameEngine::ToHighscore() {

    std::shared_ptr<GameState> highscore = std::shared_ptr<Highscore>(new
                                                                          Highscore);
    highscore->Init(this);

    states.push_back(std::move(highscore));
}

std::unique_ptr<SDL_RWops, RWCloser> GameEngine::OpenFile(const char *fname, const char *mode) {
    return std::unique_ptr<SDL_RWops, RWCloser>(SDL_RWFromFile(fname, mode));
}

int GameEngine::ReadSave() {

	int Highlevel;

	saveFile = OpenFile("data/save2.txt", "r");

	if (saveFile) {
		std::cout << "Reading save file...\n";
    	if (SDL_RWread(saveFile.get(), &Highlevel, sizeof(int), 1) != 1) {
			//std::cout << "Save file format error...\n";
        	throw std::runtime_error(std::string("Save file format error: ") + SDL_GetError());

    	}
	} else {
		saveFile = OpenFile("data/save2.txt", "w+");
		if (saveFile) {
			std::cout << "Writing new save file...\n";
			Highlevel = 0;
			SDL_RWwrite(saveFile.get(), &Highlevel, sizeof(Highlevel), 1);
		} else {
			//std::cout << "Unable to create save file...\n";
			throw std::runtime_error(std::string("Unable to create save file: ") + SDL_GetError());
		}
	}
	return Highlevel;
}

void GameEngine::Save(int Highlevel) {

		int Highlevel_Old = this->ReadSave();
		std::cout << "Previous: " << Highlevel_Old << ", Highlevel: " << Highlevel << "\n";
		if(Highlevel_Old<Highlevel){
			saveFile = OpenFile("data/save2.txt", "w+");

			if (saveFile) {
				std::cout << "Writing save file...\n";
				if(SDL_RWwrite(saveFile.get(), &Highlevel,
					       sizeof(Highlevel), 1) != 1){
					std::cout << "Unable to write save file...\n";
				}
			}
			else {
				//std::cout << "Unable to read save file...\n";
				throw std::runtime_error(std::string("Unable to read save file: ") + SDL_GetError());
			}
		}
}

void GameEngine::ChangeState(std::shared_ptr<GameState> state)
{

}

void GameEngine::PushState(std::shared_ptr<GameState> state)
{
	states.push_back(std::move(state));
}

void GameEngine::PopState()
{
	states.pop_back();

	SDL_Event sdlevent = {};
	sdlevent.type = SDL_MOUSEMOTION;
	//sdlevent.key.keysym.sym = SDL_BUTTON_LEFT;
	SDL_PushEvent(&sdlevent);
}

void GameEngine::PopStateS()
{
    states.pop_back();
}

void GameEngine::HandleEvents()
{
	states.back()->HandleEvents(this);
}

void GameEngine::Cleanup(void)
{
	rend->Cleanup();
}

void GameEngine::Update()
{
	rend->Update();
	states.back()->Update(this);
}

void GameEngine::Draw()
{
	SDL_RenderClear(rend->GetSDLRenderer());

	if(draw)
		states.back()->Draw(rend);

        //draw = 0;
}
