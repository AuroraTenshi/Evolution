#include "Entity.h"

#define HEIGHT 700
#define WIDTH 1000

Entity::Entity(double x, double y, int size, int r, int g, int b)
{
	_x = x;
	_y = y;
	_size = size;
	_color.r = r;
	_color.g = g;
	_color.b = b;
}

Food::Food(double x, double y, int size, int r, int g, int b)
{
	_x = x;
	_y = y;
	_size = size;
	_color.r = r;
	_color.g = g;
	_color.b = b;
}

void Food::GetEaten()
{
	//_foods->remove(this);
}

Creature::Creature(double x, double y, int size, double angle, double turnspeed, double turnaccel, double speed, double accel, double jerk, double gravity, int bounce, int health, int r, int g, int b)
{
	_x = x;
	_y = y;
	_size = size;
	_angle = angle;
	_turnSpeed = turnspeed;
	_turnAccel = turnaccel;
	_speed = speed;
	_accel = accel;
	_jerk = jerk;
	_gravity = gravity;
	_bounce = bounce;
	_health = health;
	_color.r = r;
	_color.g = g;
	_color.b = b;
}

bool Creature::IsOnScreen()
{
	return !(_x + _size / 2 < 0 || _x - _size / 2 > WIDTH
		|| _y + _size / 2 < 0 || _y - _size / 2 > HEIGHT);
}

void Creature::Move()
{
	Bounce();
	_x += _speed * sinf(_angle);
	_y += _speed * cosf(_angle) + _fallSpeed;
	_angle += _turnSpeed;
	_turnSpeed += _turnAccel;
	_speed += _accel;
	_accel += _jerk;
	_fallSpeed += _gravity;
}

void Creature::Bounce()
{
	if (_bounce > 0)
	{
		if (_bounceCoolDown > 0)
		{
			_bounceCoolDown--;
		}
		else
		{
			if (_x + _size / 2 > 1000)
			{
				_angle = -_angle;
				_bounceCoolDown = 3;
				_bounce--;
			}

			if (_x - _size / 2 < 0)
			{
				_angle = -_angle;
				_bounceCoolDown = 3;
				_bounce--;
			}

			if (_y + _size / 2 > 700)
			{
				_angle = M_PI - _angle;
				_fallSpeed = -_fallSpeed / 2.f;
				_bounceCoolDown = 3;
				_bounce--;
			}

			if (_y - _size / 2 < 0)
			{
				_angle = M_PI - _angle;
				_fallSpeed = -_fallSpeed / 2.f;
				_bounceCoolDown = 3;
				_bounce--;
			}
		}
	}
}

void Creature::Eat()
{
	_health = _health + 500;
	xp = xp + 50;
	//eatCounter = eatCounter + 1;
	//if (eatCounter % 3 == 0 /*&& eatCounter != 25*/) {
	//	if (rand() % 2 + 1 == 1) {
	//		_size = _size + 10;
	//	}
	//	else {
	//		_speed = _speed + 0.3f;
	//		//_turnAccel = _turnAccel + 0.01f;
	//	}
	//}
	
}

int Creature::GetXp()
{
	return xp;
}

void Creature::setAngle(double angle)
{
	_angle = angle;
}