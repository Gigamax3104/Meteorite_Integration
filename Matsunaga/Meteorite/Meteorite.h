#pragma once
#include "../../h/Vector.h"

class Meteorite
{
public:
	Meteorite(Vector2 pos, double speed, int radius, Vector2 earthPosition);
	~Meteorite();
	void Update();
	void Draw();
	void Destroy();

	int Radius() const { return radius; }
	Vector2 Position() const { return position; }
private:
	Vector2 position;
	Vector2 direction;
	double speed;
	int radius;
};