#include "DxLib.h"
#include "Meteorite.h"
#include "../../Itou/ContentCreation2026_10_19/Temp.h"

#include <vector>

Meteorite::Meteorite(Vector2 pos, double speed, int radius, Vector2 earthPosition)
{
	position = pos;
	this->speed = speed;
	this->radius = radius;
	Vector2 distance = earthPosition - position;
	direction = distance.Normalized();
}

void Meteorite::Update()
{
	// ˆÚ“®ˆ—
	position += direction * speed * ptr_class_time->DeltaTime();
}

void Meteorite::Draw()
{
	DrawCircle(position.x, position.y, radius, 0xff0000, true);
}

