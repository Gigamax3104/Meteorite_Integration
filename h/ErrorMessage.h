#pragma once
#include	<string>

#include	"DxLib.h"
#include	"Vector.h"

class ErrorMassage {
public:
	Vector2 m_pos = Vector2(0, 0);

	ErrorMassage() : m_message("\0"){ SetFontSize(15); }
	ErrorMassage(const std::string& massage) : m_message(massage){ SetFontSize(20); }

	std::string GetMassage() const { return m_message; }
	void Show() {
		DrawString(m_pos.x, m_pos.y, m_message.c_str(), 0xff0000);
		/*m_pos.y += 20; */
	}

private:
	std::string m_message;
};