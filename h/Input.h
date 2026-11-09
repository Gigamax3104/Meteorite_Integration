#pragma once
#include "Vector.h"
#include "Dxlib.h"

class Input
{
public:
	enum class KeyState
	{
		FREE,   // 押されていない
		DOWN,   // 押された瞬間
		HOLD,   // 押され続けている
		UP      // 離された瞬間
	};
	Input();
	void Update();

	bool GetKey(int keyCode) const;     // 押しっぱなし
	bool GetKeyDown(int keyCode) const; // 押された瞬間
	bool GetKeyUp(int keyCode) const;   // 離された瞬間
	int GetKeyHoldFrame(int keyCode) const; // 押されているフレーム数

	// 移動や特定の複合処理
	Vector2 GetDirection() const;
	Vector2 GetDirectionDown() const;
	int GetDebugValue() const { return debugValue; }

private:
	// 全キー（DxLibの最大256個）の状態を管理する構造体
	struct KeyInfo
	{
		KeyState state = KeyState::FREE;
		int holdFrame = 0;
	};
	KeyInfo keys[256];

	int debugValue = 0;
	const int maxDebugValue = 3;
};
