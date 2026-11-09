#pragma once
#include "../../h/Vector.h"
namespace Collision
{
	bool PointAndCircle(Vector2 pointPos, Vector2 circlePos, double circleRadius); // “_‚Ì‰~‚Ì“–‚½‚è”»’è
	bool PointAndRect(Vector2 pointPos, Vector2 rectanglePos, Vector2 rectangleSize); // “_‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
	bool CircleAndCircle(Vector2 circlePos1, double circleRadius1, Vector2 circlePos2, double circleRadius2); // ‰~‚Æ‰~‚Ì“–‚½‚è”»’è
	bool RectAndRect(Vector2 rectanglePos1, Vector2 rectangleSize1, Vector2 rectanglePos2, Vector2 rectangleSize2); // ‹éŒ`‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
}