#include "intro.h"

extern int draw;

static void button_start_event(kiss_button *button, SDL_Event *e, int *draw,
                                 std::function<void()> callback)
{
	//int draw = 1;
    if (kiss_button_event(button, e, draw)) {
		callback();
    }
}

bool Intro::Init(GameEngine* game)
{
    button1 = {0};

    kiss_window* window = (game->GetRend()->GetWindow());

	int center = game->GetRend()->GetWidth()/2;

    kiss_label_new(&hello, window, "Press Any Button!", center,
                200);

    return true;
}

void Intro::Update(GameEngine* game)
{
}

void Intro::HandleEvents(GameEngine* game)
{
	SDL_PollEvent(&event);

//        kiss_window_event(rend->GetWindow(), &event, &draw);

    switch(event.type){
		case SDL_KEYDOWN:
			break;

		case SDL_KEYUP:
			game->PopState();
			break;

        case SDL_TEXTINPUT:
			break;

        case SDL_QUIT:
			game->Quit();
            break;
    }
}

void Intro::Draw(std::shared_ptr<RenderManager>& rend)
{
//  kiss_window_draw(&rend.GetWindow(), rend->GetSDLRenderer());

    kiss_label_draw(&hello, rend->GetSDLRenderer());
}


