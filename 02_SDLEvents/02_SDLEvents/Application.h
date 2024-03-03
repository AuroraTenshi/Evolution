#pragma once
#include <SDL.h>
#include <list>
#include "Entity.h"
#include <vector>



enum Pattern
{
	NONE, TESTCASE, FOODS, CARNIVORES, INCREASEFOOD, NORMALFOOD, DECREASEFOOD
};

class Application
{
	private:
		bool quit = false;
		SDL_Renderer * myRen = nullptr;
		int myWidth = 0;
		int myHeight = 0;
		std::list<Creature>::iterator it;
		std::list<Food>::iterator itFood;
		std::list<Creature> carnivoreCreatures;
		std::list<Creature> herbivoreCreatures;
		std::list<Food> foods;
		std::list<Creature> tmpCreatures;

		int foodProduction = 200;
		
		Uint32 frames = 1001;
		Pattern pattern = NONE;
		SDL_Rect rect;
		bool boolT = false;
		bool follow = false;

		double angle_01 = -2.f;
		double accel_01 = 0.f;
		int j_01 = 0;

		int j_02 = 20;

		double angle_03 = 1.f;
		double accel_03 = 1.f;
		double speed_03 = 1.f;
		bool up_03 = true;

		//double angle_04;
		double speed_04;

		double angle_tenshi = 0.f;

		double dirX = 0.f;
		double dirY = 0.f;
		double followX = 100.f;
		double followY = 100.f;

	public:
		Application(SDL_Renderer*, int, int);
		~Application();
		void Run();
		void MoveAndDeleteCreatures();
		bool Collide(int, int, int, int, int, int);
		void DrawEntities();
		void DrawCircle(double x, double y, int radius, int r, int g, int b);
		void AddNewCreature(CreatureType bt, int x, int y, int size, double angle, double turnspeed, double turnaccel, double speed, double accel, double jerk, double gravity, int bounce, int lifetime, int r, int g, int b);
		void AddNewFood(int x, int y, int size, int r, int g, int b);
		void KeyDown(SDL_Keycode);
		void KeyUp(SDL_Keycode);
		bool AppQuit() { return quit; };
		void MovePlayer();
		void Events();
		double CalculateAngle(double x1, double y1, double x2, double y2);
		double Abs(double a1, double a2);
		bool IsLeftTurn(double a1, double a2);
		void HerbivoresEat();
		void CarnivoresEat();
		double CalculateVectorLength(double x, double y);
		bool ShouldEvolve(std::list<Creature>::iterator cr);
		std::list<Creature> Evolve(std::list<Creature>::iterator cr, CreatureType creatureType);
};