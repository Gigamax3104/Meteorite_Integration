#include "Collision.h"
#include <iostream>
bool Collision::PointAndCircle(Vector2 pointPos, Vector2 circlePos, double circleRadius)
{
	double distance = Vector2DistanceSq(pointPos, circlePos);
	return distance <= circleRadius * circleRadius;
}

bool Collision::PointAndRect(Vector2 pointPos, Vector2 rectanglePos, Vector2 rectangleSize)
{
	double left = rectanglePos.x - (rectangleSize.x / 2);
	double right = rectanglePos.x + (rectangleSize.x / 2);
	double top = rectanglePos.y - (rectangleSize.y / 2);
	double bottom = rectanglePos.y + (rectangleSize.y / 2);
	return pointPos.x <= left && pointPos.x >= right && pointPos.y >= top && pointPos.y <= bottom;
}

bool Collision::CircleAndCircle(Vector2 circlePos1, double circleRadius1, Vector2 circlePos2, double circleRadius2)
{
	double totalRadius = circleRadius1 + circleRadius2;
	double distance = Vector2DistanceSq(circlePos1, circlePos2);
	return distance <= totalRadius * totalRadius;
}

bool Collision::RectAndRect(Vector2 rectanglePos1, Vector2 rectangleSize1, Vector2 rectanglePos2, Vector2 rectangleSize2)
{
	double dx = std::abs(rectanglePos1.x - rectanglePos2.x);
	double dy = std::abs(rectanglePos1.y - rectanglePos2.y);
	return dx <= (rectangleSize1.x / 2) + (rectangleSize2.x / 2) && dy <= (rectangleSize1.y / 2) + (rectangleSize2.y / 2);
}