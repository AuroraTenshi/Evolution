#include "Menu.h"
#include "Application.h"
#include <iostream>

enum GameState
{

};

Application::Application(SDL_Renderer * ren, int width, int height)
{
	myRen = ren;
	myWidth = width;
	myHeight = height;


}


Application::~Application()
{
	carnivoreCreatures.clear();
	herbivoreCreatures.clear();
	tmpCreatures.clear();
	
}

void Application::Run()
{
	switch (pattern)
	{
	case NONE:
		break;

	case TESTCASE:
		if (frames % 10 == 0)
		{
			for (int i = 0; i < 1; i++)
			{
				AddNewCreature(
					HERBIVORE,
					500,				//posx
					120,				//posy
					13,								//size
					angle_01 + i / 5.f + rand() % 200 + 1,				//angle
					0.f,							//turnspeed
					0.f,							//turnaccel
					0.6f,							//speed
					0.0f,							//accel
					0.f,						//jerk
					0.f,							//gravity
					100000,								//bounce
					1000,							//life
					37, 150, 53);					//color
			}
		}
		angle_01 += accel_01;
		accel_01 += 0.001f;
		j_01++;
		break;
	case FOODS:
		if (frames % 50 == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				AddNewFood(
					rand() % 950 + 1,				//posx
					rand() % 650 + 1,							//posy
					9,								//size
					250, 0, 250);					//color
			}
		}
		break;
	case CARNIVORES:
		if (frames % 10 == 0)
		{
			for (int i = 0; i < 1; i++)
			{
				AddNewCreature(
					CARNIVORE,
					500,				//posx
					120,				//posy
					13,								//size
					angle_01 + i / 5.f + rand() % 200 + 1,				//angle
					0.f,							//turnspeed
					0.f,							//turnaccel
					0.6f,							//speed
					0.0f,							//accel
					0.f,						//jerk
					0.f,							//gravity
					100000,								//bounce
					1000,							//life
					240, 1, 1);					//color
			}
		}
		angle_01 += accel_01;
		accel_01 += 0.001f;
		j_01++;
		break;
	case INCREASEFOOD:
		if (foodProduction > 1)
		{
			foodProduction = foodProduction - 1;
		}
		break;
	case NORMALFOOD:
		foodProduction = 200;
		break;
	case DECREASEFOOD:
		if (foodProduction < INT_MAX)
		{
			foodProduction = foodProduction + 1;
		}
		break;
	default:
		break;
	}
	
	Events();
	CarnivoresEat();
	HerbivoresEat();
	MoveAndDeleteCreatures();
	DrawEntities();
	//std::cout << carnivoreCreatures.size() + herbivoreCreatures.size() + tmpCreatures.size() << std::endl;
	frames++;
}

void Application::MoveAndDeleteCreatures()
{
	it = carnivoreCreatures.begin();
	while (it != carnivoreCreatures.end())
	{
		if (it->IsAlive())
		{
			it->Decrease();
			it->Move();
			it++;
		}
		else
		{
			it = carnivoreCreatures.erase(it);
		}
	}

	it = herbivoreCreatures.begin();
	while (it != herbivoreCreatures.end())
	{
		if (it->IsAlive())
		{
			it->Decrease();
			it->Move();
			it++;
		}
		else
		{
			it = herbivoreCreatures.erase(it);
		}
	}

	it = tmpCreatures.begin();
	while (it != tmpCreatures.end())
	{
		if (it->IsOnScreen())
		{
			it->Move();
			it++;
		}
		else
		{
			it = tmpCreatures.erase(it);
		}
	}
}

bool Application::Collide(int x1, int y1, int x2, int y2, int size1, int size2)
{
	if (abs(x1 - x2) < (size1 + size2) / 2 && abs(y1 - y2) < (size1 + size2) / 2)
		return true;
	return false;
}

/*
bool Application::Collide()
{
	int x1 = xy->GetX();
	int y1 = xy->GetY();
	int size1 = xy->GetSize();
	int x2, y2, size2;

	it = carnivoreCreatures.begin();
	while (it != carnivoreCreatures.end())
	{
		x2 = it->GetX();
		y2 = it->GetY();
		size2 = it->GetSize();
		if(Collide(x1, y1, size1, x2, y2, size2)) return true;
		it++;
	}

	it = herbivoreCreatures.begin();
	while (it != herbivoreCreatures.end())
	{
		x2 = it->GetX();
		y2 = it->GetY();
		size2 = it->GetSize();
		if (Collide(x1, y1, size1, x2, y2, size2)) return true;
		it++;
	}

	// !tmpCreatures

	return false;
}
*/

void Application::DrawEntities()
{
	
	for (it = carnivoreCreatures.begin(); it != carnivoreCreatures.end(); ++it)
	{
		//
		Color color;
		color = it->GetColor();
		rect.x = it->GetX() - it->GetSize() / 2;
		rect.y = it->GetY() - it->GetSize() / 2;
		rect.w = rect.h = it->GetSize();
		SDL_SetRenderDrawColor(myRen, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(myRen, &rect);
	}
	for (it = herbivoreCreatures.begin(); it != herbivoreCreatures.end(); ++it)
	{
		//
		Color color;
		color = it->GetColor();
		rect.x = it->GetX() - it->GetSize() / 2;
		rect.y = it->GetY() - it->GetSize() / 2;
		rect.w = rect.h = it->GetSize();
		SDL_SetRenderDrawColor(myRen, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(myRen, &rect);
	}
	for (it = tmpCreatures.begin(); it != tmpCreatures.end(); ++it)
	{
		//
		Color color;
		color = it->GetColor();
		rect.x = it->GetX() - it->GetSize() / 2;
		rect.y = it->GetY() - it->GetSize() / 2;
		rect.w = rect.h = it->GetSize();
		SDL_SetRenderDrawColor(myRen, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(myRen, &rect);
	}
	for (itFood = foods.begin(); itFood != foods.end(); ++itFood)
	{
		//
		Color color;
		
		color = itFood->GetColor();
		
		rect.x = itFood->GetX() - itFood->GetSize() / 2;
		
		rect.y = itFood->GetY() - itFood->GetSize() / 2;
		
		rect.w = rect.h = itFood->GetSize();
		
		SDL_SetRenderDrawColor(myRen, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(myRen, &rect);
	}
}

void Application::DrawCircle(double x, double y, int radius, int r, int g, int b)
{
	SDL_SetRenderDrawColor(myRen, r, g, b, 255);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(myRen, (int)x + dx, (int)y + dy);
			}
		}
	}
}
void Application::AddNewFood(int x, int y, int size, int r, int g, int b)
{
	Food* ptr = new Food(x, y, size, r, g, b);
	foods.push_front(*ptr);
}

void Application::AddNewCreature(
	CreatureType bt,
	int x,
	int y,
	int size,
	double angle,
	double turnspeed,
	double turnaccel,
	double speed,
	double accel,
	double jerk,
	double gravity,
	int bounce,
	int health,
	int r,
	int g,
	int b)
{
	Creature* ptr = new Creature(x, y, size, angle, turnspeed, turnaccel, speed, accel, jerk, gravity, bounce, health, r, g, b);
	switch(bt)
	{
	case CARNIVORE:
		carnivoreCreatures.push_front(*ptr);
		break;
	case HERBIVORE:
		herbivoreCreatures.push_front(*ptr);
		break;
	case FRIENDLY:
		tmpCreatures.push_front(*ptr);
		break;
	default:
		break;
	}
}

void Application::KeyDown(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		quit = true;
		break;
	case SDLK_UP:
	case 'w':
		//player->SetUp(true); 
		break;
	case SDLK_DOWN:
	case 's':
		//player->SetDown(true);
		break;
	case SDLK_LEFT:
	case 'a':
		//player->SetLeft(true);
		break;
	case SDLK_RIGHT:
	case 'd':
		//player->SetRight(true);
		break;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		//player->SetSpeed(2);
		break;
	default:
		break;
	}
}

void Application::KeyUp(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_UP:
	case 'w':
		//player->SetUp(false);
		break;
	case SDLK_DOWN:
	case 's':
		//player->SetDown(false);
		break;
	case SDLK_LEFT:
	case 'a':
		//player->SetLeft(false);
		break;
	case SDLK_RIGHT:
	case 'd':
		//player->SetRight(false);
		break;
	case SDLK_0:
		pattern = NONE;
		break;
	case SDLK_1:
		pattern = TESTCASE;
		break;
	case SDLK_2:
		pattern = FOODS;
		break;
	case SDLK_3:
		pattern = CARNIVORES;
		break;
	case SDLK_4:
		pattern = INCREASEFOOD;
		break;
	case SDLK_5:
		pattern = NORMALFOOD;
		break;
	case SDLK_6:
		pattern = DECREASEFOOD;
		break;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		//player->SetSpeed(6);
		break;
	case 'r':
		//player->SetColor(255, 0, 0);
		frames = 0;
		break;
	case 'e':
		//player->SetColor(255, 0, 0);
		break;
	case 't':
		//player->SetColor(255, 0, 255);
		boolT = !boolT;
		break;
	case 'f':
		//player->SetColor(0, 255, 255);
		follow = !follow;
		break;
	default:
		break;
	}
}

void Application::Events()
{
	if (frames % foodProduction == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			AddNewFood(
				rand() % 950 + 1,				//posx
				rand() % 650 + 1,							//posy
				9,								//size
				250, 0, 250);					//color
		}
	}
}

double Application::CalculateAngle(double x1, double y1, double x2, double y2)
{

	
	double angle;
	double dx = x2 - x1;
	double dy = y2 - y1;
	if (dy == 0)
		if (dx < 0)
			angle = M_PI * 1.5f;
		else
			angle = M_PI * 0.5f;
	else
		if (dy < 0)
			angle = atanf(dx / dy) + M_PI;
		else
			angle = atanf(dx / dy);
	return angle;
	
}

double Application::CalculateVectorLength(double x, double y)
{
	return sqrt(x*x + y*y);
}

void Application::HerbivoresEat()
{
	std::list<Creature>::iterator it;
	std::list<Food>::iterator it2;
	std::list<Creature> newGeneration;
	for (it = herbivoreCreatures.begin(); it != herbivoreCreatures.end(); ++it)
	{
		for (it2 = foods.begin(); it2 != foods.end(); ++it2)
		{
			if (Collide(it->GetX(), it->GetY(), it2->GetX(), it2->GetY(), it->GetSize(), it2->GetSize()))
			{
				foods.erase(it2);
				it->Eat();
				if (ShouldEvolve(it)) {
					std::list<Creature> creatureList = Evolve(it, HERBIVORE);
					newGeneration.insert(newGeneration.end(), creatureList.begin(), creatureList.end());
					herbivoreCreatures.erase(it++);
				}
				break;
			}
		}
		if (it == herbivoreCreatures.end())
			break;
	}

	herbivoreCreatures.insert(herbivoreCreatures.end(), newGeneration.begin(), newGeneration.end());

	for (it = herbivoreCreatures.begin(); it != herbivoreCreatures.end(); ++it)
	{
		for (it2 = foods.begin(); it2 != foods.end(); ++it2)
		{
			if (Collide(it->GetX(), it->GetY(), it2->GetX(), it2->GetY(), it->GetSize() * 6, it2->GetSize()))
			{
				it->setAngle(CalculateAngle(it->GetX(), it->GetY(), it2->GetX(), it2->GetY()));
			}
		}
	}
}

void Application::CarnivoresEat()
{
	std::list<Creature>::iterator it;
	std::list<Creature>::iterator it2;
	std::list<Creature> newGeneration;
	for (it = carnivoreCreatures.begin(); it != carnivoreCreatures.end(); ++it)
	{
		for (it2 = herbivoreCreatures.begin(); it2 != herbivoreCreatures.end(); ++it2)
		{
			if (Collide(it->GetX(), it->GetY(), it2->GetX(), it2->GetY(), it->GetSize(), it2->GetSize()))
			{
				herbivoreCreatures.erase(it2);
				it->Eat();
				if (ShouldEvolve(it)) {
					std::list<Creature> creatureList = Evolve(it, CARNIVORE);
					newGeneration.insert(newGeneration.end(), creatureList.begin(), creatureList.end());
					carnivoreCreatures.erase(it++);
				}
				break;
			}
		}
		if (it == carnivoreCreatures.end())
			break;
	}

	carnivoreCreatures.insert(carnivoreCreatures.end(), newGeneration.begin(), newGeneration.end());

	for (it = carnivoreCreatures.begin(); it != carnivoreCreatures.end(); ++it)
	{
		for (it2 = herbivoreCreatures.begin(); it2 != herbivoreCreatures.end(); ++it2)
		{
			if (Collide(it->GetX(), it->GetY(), it2->GetX(), it2->GetY(), it->GetSize() * 6, it2->GetSize()))
			{
				it->setAngle(CalculateAngle(it->GetX(), it->GetY(), it2->GetX(), it2->GetY()));
			}
		}
	}
}

bool Application::ShouldEvolve(std::list<Creature>::iterator cr)
{
	return (cr->GetXp() >= 100);
}

std::list<Creature> Application::Evolve(std::list<Creature>::iterator cr, CreatureType creatureType)
{
	std::list<Creature> tmpCreatures;
	if (creatureType == CARNIVORE)
	{
		for (int i = 0; i < 2; i++)
		{
			Creature* ptr = new Creature(
				cr->GetX(),
				cr->GetY(),
				cr->GetSize() * (rand() % 20 + 94) / 100,
				cr->GetAngle() + (i * 2 + 1) * 1.57,
				0.f,
				0.f,
				cr->GetSpeed() * (rand() % 20 + 90) / 100,
				//cr->GetSpeed(),
				0.0f,
				0.f,
				0.f,
				100000,
				1000,
				240,
				1,
				1);
			tmpCreatures.push_front(*ptr);
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			Creature* ptr = new Creature(
				cr->GetX(),
				cr->GetY(),
				cr->GetSize() * (rand() % 20 + 94) / 100,
				cr->GetAngle() + (i * 2 + 1) * 1.57,
				0.f,
				0.f,
				cr->GetSpeed() * (rand() % 20 + 90) / 100,
				
				0.0f,
				0.f,	//jerk
				0.f,
				100000,
				1500,
				37,
				150,
				53);
			tmpCreatures.push_front(*ptr);
		}
	}
	return tmpCreatures;
}