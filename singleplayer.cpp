#include "singleplayer.h"

extern int draw;

bool Singleplayer::Init(GameEngine* game)
{
	fruitTexture = game->GetRend()->createTexture("data/quadb.bmp");

	nom_nomTexture = game->GetRend()->createTexture("data/quadr.bmp");

	teleportTexture = game->GetRend()->createTexture("data/quado.bmp");

	wallTexture = game->GetRend()->createTexture("data/quad.bmp");

	backgroundTexture = game->GetRend()->createTexture("data/background.bmp");

	kiss_window* window = (game->GetRend()->GetWindow());

	width = game->GetRend()->GetWidth();

	height = game->GetRend()->GetHeight();

	cellWidth = game->GetRend()->GetCellWidth();

	fieldWidth = width/cellWidth;	

	int center = game->GetRend()->GetWidth()/2;

	std::string scoreStr = "Score";

	kiss_label_new(&scoreLabel, window, (char*)scoreStr.c_str(),
                           game->GetRend()->GetWidth()-scoreLabel.rect.w-8,
                0);

    scoreLabel.textcolor = kiss_white;

	//this->UpdateScore();

	Block b1,b2,b3;

	b1.x=0;
	b1.y=0;
	b1.z=1;

	snk.push_back(b1);
	b2.x=-1;
	b2.y=0;
	b2.z=1;

	snk.push_back(b2);
	b3.x=-2;
	b3.y=0;
	b3.z=1;

	snk.push_back(b3);

	srand ( time(NULL) );

	Block wall;
	int x = rand()%fieldWidth;
	int y = rand()%(height/(cellWidth)-1);
	wall.x = x;
	wall.y = y;
	wall.z = 0;
	wall.tp = WALL;

	walls.push_back(wall);

	Block wall2;
	x = rand()%fieldWidth;
	y = rand()%(height/(cellWidth)-1);
	wall2.x = x;
	wall2.y = y;
	wall2.z = 0;
	wall2.tp = WALL;

	walls.push_back(wall2);

	Block wall3;
	x = rand()%(fieldWidth);
	y = rand()%(height/(cellWidth)-1);
	int z = rand()%2;

	wall3.x = x;
	wall3.y = y;
	wall3.z = z;
	wall3.tp = WALL;

	walls.push_back(wall3);

	nom_nom.x = rand()%fieldWidth;//26
	nom_nom.y = rand()%(height/(cellWidth)-1);//17
	nom_nom.z = rand()%2;

	direction = 0;

	teleportFlag = false;

	tFlag = false;

	level = 1;

	score = 0;

	speed = 1;

	this->UpdateScore();


	GenerateTeleportBlocks();

	frameStart = SDL_GetTicks();

	Uint32 frameEnd;
	Uint32 frameDuration;

	return true;
}

void Singleplayer::GenerateNextRound()
{
	snk.clear();

	Block b1,b2,b3;

	b1.x=0;
	b1.y=0;
	b1.z=1;
	snk.push_back(b1);

	b2.x=-1;
	b2.y=0;
	b2.z=1;
	snk.push_back(b2);

	b3.x=-2;
	b3.y=0;
	b3.z=1;
	snk.push_back(b3);


	direction=0;

	nom_nom.x = rand()%fieldWidth;//27;//26
	nom_nom.y = rand()%(height/(cellWidth)-1);//18;//17
	nom_nom.z = rand()%2;

	speed = 1;
	score = 0;
	level = 1;

	walls.clear();

	this->UpdateScore();


	for(int i=0; i<3; i++)
	{
		Block wall;
		SDL_Rect wall_rec;
		wall_rec = this->GenerateWallBlock();
		wall.x=wall_rec.x;
		wall.y=wall_rec.y;
		wall.z = 0;
		walls.push_back(wall);
	}

	GenerateTeleportBlocks();
}

SDL_Rect Singleplayer::GenerateNom_NomBlock()
{
	bool ok = false;

	Block b1;
	b1.x  = nom_nom.x;
	b1.y = nom_nom.y;
	b1.z = snk[0].z;

	snk.push_back(b1);

	while(!ok)
	{
		ok = true;

		nom_nom.z = rand()%2;
		if(nom_nom.z == 0){
			nom_nom.x = rand()%fieldWidth;
			nom_nom.y = rand()%(height/(cellWidth)-1);
		}
		else {
			nom_nom.x = rand()%fieldWidth;
			nom_nom.y = rand()%(height/(cellWidth)-1);
		}

		for(auto it : walls)
		{
			if((it.x == nom_nom.x)and(it.y == nom_nom.y)){
				if(it.z == nom_nom.z)
					ok = false;
			}
		}
	}
}

SDL_Rect Singleplayer::GenerateTeleportBlocks()
{
	bool ok = false;

	while(!ok)
    {
		ok = true;

		if(!(rand()%1)){
			teleportFlag=true;

			teleportEnter.x = rand()%fieldWidth;
			teleportEnter.y = rand()%(height/(cellWidth)-1);
			teleportExit.x = rand()%fieldWidth;
			teleportExit.y = rand()%(height/(cellWidth)-1);

			teleportEnter.z = 0;// rand()%2;
			teleportExit.z = 1;//rand()%2;

		}
		else
		{
			teleportFlag=false;
		}

		if((teleportEnter.x == teleportExit.x)and(teleportEnter.y == teleportExit.y)){
			if(teleportEnter.z==teleportExit.z)
				ok = false;
		}

		if((teleportEnter.x < 8)and(teleportEnter.x >= 0)){
			if((teleportEnter.y == 0)){
				ok = false;
			}
		}

		if((teleportExit.x < 8)and(teleportExit.x >= 0)){
			if((teleportExit.y == 0)){
				ok = false;
			}
		}

		for(auto i : walls)
		{
            if((i.x == teleportEnter.x)and(i.y == teleportEnter.y)){
				if(i.z == teleportEnter.z)
					ok = false;
			}

			if((i.x == teleportExit.x)and(i.y == teleportExit.y)){
				if(i.z == teleportExit.z)
					ok = false;
			}
		}
	}
}

SDL_Rect Singleplayer::GenerateWallBlock()
{
	bool ok = false;
	SDL_Rect wall_rec = {0, 0, 40, 40};

	while(!ok)
	{
		wall_rec.x = rand()%fieldWidth;//26
		wall_rec.y = rand()%(height/(cellWidth)-1);//17

		ok = true;

		for(auto it : walls)
		{
			if((it.x == wall_rec.x)and(it.y == wall_rec.y)){
				ok = false;
			}
		}

		if((wall_rec.x < 8)and(wall_rec.x >= 0)){
			if((wall_rec.y == 0)){
				ok = false;
			}
		}
	}

        return wall_rec;
}

bool Singleplayer::CheckSelfCollision()
{
	for(auto it = snk.begin(); it != snk.end(); ++it)//auto it : snk)
	{
		if(it != snk.begin()){
			if((it->x == snk[0].x)and(it->y == snk[0].y)and(it->z ==
									snk[0].z))
				return false;
		}
	}

	return true;
}


bool Singleplayer::UpdateScore()
{
	int w,h;

	strcpy(scoreC, "score ");

	scoreStr = std::to_string(score);

	char * hh = strcat(scoreC, scoreStr.c_str());

	TTF_SizeText(kiss_textfont.font, hh, &w, &h);

	int diff_width = (scoreLabel.rect.w - w);

	kiss_string_copy(scoreLabel.text, KISS_MAX_LABEL,
                                                 hh, NULL);

	scoreLabel.rect.x=scoreLabel.rect.x + diff_width;
	scoreLabel.rect.w=w;

//	scoreLabel.rect.x=game->GetRend()->GetWidth()-w-8;

}

void Singleplayer::Update(GameEngine* game)
{
	if (frameDuration > 300/speed) {

		if(snk[0].z==0){
			if((snk[0].x > (fieldWidth-1))or(snk[0].x < 0)or(snk[0].y >
							     (height/(cellWidth)-1))or(snk[0].y < 0)){
				std::cout << "BorderColisionBig" << "\n";
				game->Save(level);
				this->GenerateNextRound();

				return;
			}
		}
		else {
			if((snk[0].x > ((fieldWidth*2)-1))or(snk[0].x < 0)or(snk[0].y >
								     ((height/(cellWidth/2))-1))or(snk[0].y < 0)){
				std::cout << "BorderColisionSmall" << "\n";
				game->Save(level);
				this->GenerateNextRound();

				return;
			}
	}

		if(!this->CheckSelfCollision()){
			std::cout << "SelfCollision" << "\n";
			game->Save(level);
			this->GenerateNextRound();

			return;
		}

		if(teleportFlag){

			if(snk[0].x == teleportEnter.x){
				if(snk[0].y == teleportEnter.y){
					if(snk[0].z == teleportEnter.z)
					{
						if(!tFlag){
							snk[0].x = teleportExit.x;
							snk[0].y = teleportExit.y;
							snk[0].z = teleportExit.z;

							tFlag = true;
						}
						else {
							tFlag = false;
						}
					}
				}
			}

			if(snk[0].x == teleportExit.x){
				if(snk[0].y == teleportExit.y){
					if(snk[0].z == teleportExit.z)
					{
						if(!tFlag){
							snk[0].x = teleportEnter.x;
							snk[0].y = teleportEnter.y;
							snk[0].z = teleportEnter.z;

							tFlag = false;
						}
						else {
							tFlag = false;
						}
					}
				}
			}
		}

		for(auto it : walls){
			if(snk[0].x == it.x){
				if(snk[0].y == it.y){
					if(snk[0].z == it.z)
					{
						std::cout << "crash " << it.x <<
								":" << it.y << "\n";
						game->Save(level);
						this->GenerateNextRound();

						return;
					}
				}
			}
		}


		if(snk[0].x == nom_nom.x){
			if(snk[0].y == nom_nom.y){
				if(snk[0].z == nom_nom.z){
					//std::cout << "Ate " << "\n";
					this->GenerateNom_NomBlock();
					score += 1;
					this->UpdateScore();

					if(score >= 15){
						direction = 0;
						level++;
						score = 0;
						this->UpdateScore();
						snk.clear();

						Block b1,b2,b3;

						b1.x = 0;
						b1.y = 0;
						b1.z = 0;
						snk.push_back(b1);

						b2.x = -1;
						b2.y = 0;
						b2.z = 0;
						snk.push_back(b2);

						b3.x = -2;
						b3.y = 0;
						b3.z = 0;
						snk.push_back(b3);
 

						score = 0;
						speed += 1;

						walls.clear();

						for(int i=0;i<level;i++){
							Block wall;

							SDL_Rect wall_rec;

							wall_rec = this->GenerateWallBlock();
							wall.x = wall_rec.x;
							wall.y = wall_rec.y;
							wall.z = 0;

							walls.push_back(wall);

							SDL_Rect wall_rec2;

							Block wall2;

							wall_rec2 = this->GenerateWallBlock();
							wall2.x = wall_rec2.x;
							wall2.y = wall_rec2.y;
							wall2.z = 0;

							walls.push_back(wall2);
						}
						this->GenerateTeleportBlocks();
					}
				}

			}
		}


		for(int i=snk.size()-1; i>0; i--){
			snk[i].x = snk[i-1].x;
			snk[i].y = snk[i-1].y;
			snk[i].z = snk[i-1].z;
		}

		switch(direction){
			case 0:
				snk[0].x += 1;
				break;
			case 1:
				snk[0].x -= 1;
				break;
			case 2:
				snk[0].y -= 1;
				break;
			case 3:
				snk[0].y += 1;
				break;
		}

		oldDirection = direction;

		frameStart = SDL_GetTicks();
	}
}

void Singleplayer::HandleEvents(GameEngine* game)
{
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_KEYDOWN:
			if( event.key.keysym.sym == SDLK_BACKSPACE){
				game->Quit();
			}

			if( event.key.keysym.sym == SDLK_ESCAPE){
				game->PopState();
			}


			if( event.key.keysym.sym == SDLK_SPACE){
			}

			if( event.key.keysym.sym == SDLK_LEFT){
				if(oldDirection != 0)
					direction = 1;
			}

			if( event.key.keysym.sym == SDLK_RIGHT){
				if(oldDirection != 1)
					direction = 0;
			}

			if( event.key.keysym.sym == SDLK_UP){
				if(oldDirection != 3)
					direction = 2;
			}

			if( event.key.keysym.sym == SDLK_DOWN){
				if(oldDirection != 2)
					direction = 3;
			}

			break;

		case SDL_TEXTINPUT:
			break;

		case SDL_QUIT:
			game->Quit();
			break;
	}

}

void Singleplayer::DrawLabel(std::shared_ptr<RenderManager>& rend, int x, int y,
			     int z)
{
	if(z==0)
		rend->DrawTexture(fruitTexture.get(), x, y);
	else
		rend->DrawTexture(fruitTexture.get(), x, y, 20, 20);
}

void Singleplayer::DrawNom_Nom(std::shared_ptr<RenderManager>& rend, int x, int
			       y, int z)
{
	if(z==0)
		rend->DrawTexture(nom_nomTexture.get(), x, y);
	else
		rend->DrawTexture(nom_nomTexture.get(), x, y, 20, 20);
}

void Singleplayer::DrawWall(std::shared_ptr<RenderManager>& rend, int x, int y,
			    int z)
{
	if(z==0)
		rend->DrawTexture(wallTexture.get(), x, y);
	else
		rend->DrawTexture(wallTexture.get(), x, y, 20, 20);
}

void Singleplayer::DrawTeleportEnter(std::shared_ptr<RenderManager>& rend, int x, int
                                y, int z)
{
	if(z == 0)
		rend->DrawTexture(teleportTexture.get(), x, y);
	else
		rend->DrawTexture(teleportTexture.get(), x, y, 20, 20);
}

void Singleplayer::DrawTeleportExit(std::shared_ptr<RenderManager>& rend, int x, int
                                y, int z)
{
	if(z == 0)
		rend->DrawTexture(teleportTexture.get(), x, y);
	else
		rend->DrawTexture(teleportTexture.get(), x, y, 20, 20);
}

void Singleplayer::DrawBackground(std::shared_ptr<RenderManager>& rend, int x, int y, int w, int h)
{
	rend->DrawTextureReal(backgroundTexture.get(), x, y, w, h);
}

void Singleplayer::Draw(std::shared_ptr<RenderManager>& rend)
{
    //if(!(draw))
    //{
   // }	
	this->DrawBackground(rend, 0, 0, fieldWidth*(cellWidth),
			     (cellWidth)*(height/(cellWidth)));

	for(int i=0;i<walls.size();i++)
	{
		if(walls[i].z==0){
			this->DrawWall(rend, walls[i].x, walls[i].y, walls[i].z);
		}
	}

	if(teleportFlag){
		this->DrawTeleportEnter(rend, teleportEnter.x,
                                   teleportEnter.y, teleportEnter.z);
	}

	for(int i=0;i<snk.size();i++)
	{
		this->DrawLabel(rend, snk[i].x, snk[i].y, snk[i].z);
	}


	if(teleportFlag){
		this->DrawTeleportExit(rend, teleportExit.x,
                                   teleportExit.y, teleportExit.z);
	}

	for(int i=0;i<walls.size();i++)
	{
		if(walls[i].z==1){
			this->DrawWall(rend, walls[i].x, walls[i].y, walls[i].z);
		}
	}

	this->DrawNom_Nom(rend, nom_nom.x, nom_nom.y, nom_nom.z);

	kiss_label_draw(&scoreLabel, rend->GetSDLRenderer());

	frameEnd = SDL_GetTicks();

	frameDuration = frameEnd - frameStart;
}
