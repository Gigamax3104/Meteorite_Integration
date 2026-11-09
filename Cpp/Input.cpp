#include "../h/Input.h"


Input::Input()
{
	for (int i = 0; i < 256; i++)
	{
		keys[i].state = KeyState::FREE;
		keys[i].holdFrame = 0;
	}
	debugValue = 0;
}

void Input::Update()
{
	for (int i = 0; i < 256; i++)
	{
		if (CheckHitKey(i)) // ‚»‚ÌƒL[‚ª‰Ÿ‚³‚ê‚½ê‡
		{
			if (keys[i].state == KeyState::FREE || keys[i].state == KeyState::UP)
			{
				keys[i].state = KeyState::DOWN;
				keys[i].holdFrame = 1;
			}
			else
			{
				keys[i].state = KeyState::HOLD;
				keys[i].holdFrame++;
				if (keys[i].holdFrame > 100)
				{
					keys[i].holdFrame = 100;
				}
			}
		}
		else // ‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢ê‡
		{
			if (keys[i].state == KeyState::DOWN || keys[i].state == KeyState::HOLD)
			{
				keys[i].state = KeyState::UP;
			}
			else
			{
				keys[i].state = KeyState::FREE;
				keys[i].holdFrame = 0;
			}
		}
	}

	if (GetKeyDown(KEY_INPUT_F3))
	{
		debugValue++;
		if (debugValue > maxDebugValue)
		{
			debugValue = 0;
		}
	}
}

bool Input::GetKey(int keyCode) const
{
	return keys[keyCode].state == KeyState::HOLD || keys[keyCode].state == KeyState::DOWN;
}

bool Input::GetKeyDown(int keyCode) const
{
	return keys[keyCode].state == KeyState::DOWN;
}

bool Input::GetKeyUp(int keyCode) const
{
	return keys[keyCode].state == KeyState::UP;
}

int Input::GetKeyHoldFrame(int keyCode) const
{
	return keys[keyCode].holdFrame;
}

Vector2 Input::GetDirection() const
{
	Vector2 direction;
	direction.x = GetKey(KEY_INPUT_D) - GetKey(KEY_INPUT_A);
	direction.y = GetKey(KEY_INPUT_S) - GetKey(KEY_INPUT_W);
	return direction;
}

Vector2 Input::GetDirectionDown() const
{
	Vector2 direction = Vector2::zero;
	if (GetKeyDown(KEY_INPUT_D) || GetKeyDown(KEY_INPUT_A)) {
		direction.x = GetKeyDown(KEY_INPUT_D) - GetKeyDown(KEY_INPUT_A);
	}
	if (GetKeyDown(KEY_INPUT_S) || GetKeyDown(KEY_INPUT_W)) {
		direction.y = GetKeyDown(KEY_INPUT_S) - GetKeyDown(KEY_INPUT_W);
	}
	return direction;
}