#pragma once
#include <SDL.h>
#include <list>

struct Color
{
	int r;
	int g;
	int b;
};

enum CreatureType
{
	CARNIVORE, HERBIVORE, FRIENDLY
};

class Entity
{
protected:
	double _x;
	double _y;
	int _size;
	Color _color;
	
public:
	Entity() {};
	Entity(double x, double y, int size, int r, int g, int b);
	~Entity() {};

	Color GetColor() { return _color; };
	int GetX() { return (int)_x; };
	int GetY() { return (int)_y; };
	int GetSize() { return _size; };
};

class Food : public Entity
{
private:
	std::list<Food>* _foods;
public:
	Food(
		double x,
		double y,
		int size,
		int r,
		int g,
		int b
	);
	void GetEaten();
};

class Creature : public Entity
{
private:
	double _angle;
	double _turnSpeed;
	double _turnAccel;
	double _speed;
	double _accel;
	double _jerk;
	double _gravity;
	double _fallSpeed = 0;
	int _bounce;
	int _bounceCoolDown = 0;
	double _health;
	int eatCounter = 1;
	int xp = 0;

public:
	Creature(
		double x,
		double y,
		int size,
		double angle,
		double turnspeed,
		double turnangle,
		double speed,
		double accel,
		double jerk,
		double gravity,
		int bounce,
		int health,
		int r, int g, int b);
	~Creature() {};
	void setAngle(double angle);
	bool IsAlive() { return _health > 0; };
	bool IsOnScreen();
	void Decrease() { _health--; };
	void Move();
	void Bounce();
	void Eat();
	void Evolve();
	int GetXp();
	double GetSpeed() { return _speed; };
	double GetAngle() { return _angle; };
};