#include "menu.h"

extern int draw;

static void buttonStartEvent(kiss_button *button, SDL_Event *e, int *draw,
                                 std::function<void()> callback)
{
	if (kiss_button_event(button, e, draw)) {
		callback();
    }
}

static void buttonHighscoreEvent(kiss_button *button, SDL_Event *e, int *draw,
                                 std::function<void()> callback)
{
	if (kiss_button_event(button, e, draw)) {
		callback();
    }
}

static void buttonExitEvent(kiss_button *button, SDL_Event *e, int *draw,
                                 std::function<void()> callback)
{
	if (kiss_button_event(button, e, draw)) {
		callback();
    }
}

bool Menu::Init(GameEngine* game)
{
	buttonStart = {0};
	buttonHighscore = {0};
	buttonExit = {0};

	text_rect = { 0, 0, 200, 20 };

	SDL_Color color = { 255, 255, 255 };

	kiss_window* window = (game->GetRend()->GetWindow());

	int screenWidth = game->GetRend()->GetWidth();

	int screenHeight = game->GetRend()->GetHeight();

	int centerW = game->GetRend()->GetWidth()/2;

	int centerH = game->GetRend()->GetHeight()/2;


	kiss_button_new(&buttonStart, window, "Start Game",
                        centerW, centerH-screenHeight/8);

	kiss_button_new(&buttonHighscore, window, "Highscore",
                        centerW, centerH);

	kiss_button_new(&buttonExit, window, "Exit",
                        centerW, centerH+screenHeight/8);

	return true;
}

void Menu::Update(GameEngine* game)
{

}

void Menu::HandleEvents(GameEngine* game)
{
	SDL_PollEvent(&event);

	kiss_window_event(game->rend->GetWindow(), &event, &draw);

	buttonStartEvent(&buttonStart, &event, &draw,
                         std::bind(&GameEngine::ToSinglePlayer, game));

	buttonHighscoreEvent(&buttonHighscore, &event, &draw,
                         std::bind(&GameEngine::ToHighscore, game));

	buttonExitEvent(&buttonExit, &event, &draw,
                         std::bind(&GameEngine::Quit, game));

	switch(event.type)
    {
		case SDL_KEYDOWN:
			if( event.key.keysym.sym == SDLK_q){
				game->Quit();
            }
            break;

		case SDL_TEXTINPUT:
			break;

		case SDL_QUIT:
			game->Quit();
			break;
	}
}

void Menu::Draw(std::shared_ptr<RenderManager>& rend)
{
	//kiss_window_draw(&(rend->GetWindow()), rend->GetSDLRenderer());

	kiss_button_draw(&buttonStart, rend->GetSDLRenderer());

	kiss_button_draw(&buttonHighscore, rend->GetSDLRenderer());

	kiss_button_draw(&buttonExit, rend->GetSDLRenderer());
}
