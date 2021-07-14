#include "highscore.h"

extern int draw;

static void buttonBackEvent(kiss_button *button, SDL_Event *e, int *draw,
                                 std::function<void()> callback)
{
	if (kiss_button_event(button, e, draw)) {
		callback();
    }
}

bool Highscore::Init(GameEngine* game)
{
	buttonBack = {0};

	kiss_window* window = (game->GetRend()->GetWindow());

	centerW = game->GetRend()->GetWidth()/2;
	centerH = game->GetRend()->GetHeight()/2;

	screenWidth = game->GetRend()->GetWidth();
	screenHeight = game->GetRend()->GetHeight();


    kiss_button_new(&buttonBack, window, "Back",
                        centerW, centerH);
	
    char high[100] = "Highscore ";

	Highlevel = game->ReadSave();

	HighlevelStr = std::to_string(Highlevel);

	char* highscore = strcat(high, HighlevelStr.c_str());

	int width = 0;

	width = kiss_textwidth(kiss_textfont, highscore, NULL);

	kiss_label_new(&HighscoreLabel, window, highscore,
                           centerW-width/2,
                centerH-screenHeight/8);

	cupTexture = game->GetRend()->createTexture("data/cup.bmp");

	return true;
}

void Highscore::Update(GameEngine* game)
{
}

void Highscore::HandleEvents(GameEngine* game)
{
	SDL_PollEvent(&event);

	buttonBackEvent(&buttonBack, &event, &draw,
                         std::bind(&GameEngine::PopState, game));

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

void Highscore::DrawLabel(std::shared_ptr<RenderManager>& rend, int x, int y,
						  int w, int h)
{
	rend->DrawTextureReal(cupTexture.get(), x, y, w, h);
}

void Highscore::Draw(std::shared_ptr<RenderManager>& rend)
{
	kiss_button_draw(&buttonBack, rend->GetSDLRenderer());

	kiss_label_draw(&HighscoreLabel, rend->GetSDLRenderer());

	int picWidth = screenWidth/24;
	int picHeight = screenHeight/12;

	this->DrawLabel(rend, centerW-(screenWidth/6/2)-picWidth,
					centerH-picHeight/2-screenHeight/8, picWidth, picHeight);
}
