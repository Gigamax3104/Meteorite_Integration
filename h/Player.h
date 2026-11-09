#pragma once
#include	"Vector.h"
#include	"Input.h"

class Player {
public:
	Player() : m_speed(0.0), m_pos(0.0, 0.0),m_input(){}
	Player(double speed, double x, double y) : m_speed(speed),m_pos(x, y){}
	Player(double speed, Vector2 pos) : m_speed(speed), m_pos(pos){}

	virtual ~Player(){}

	void Init(double speed, Vector2 pos);

	void Update();

	Input& GetInput() { return m_input; }

private:
	double m_speed;

	Vector2 m_pos;

	Input m_input;
};