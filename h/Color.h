#pragma once
#define	COLOR_RED 0xff0000
#define COLOR_GREEN 0x00ff00
#define COLOR_BLUE 0x0000ff
#define COLOR_ORANGE 0xf08300
#define COLOR_YELLOW 0xffd900
#define COLOR_PURPLE 0x8e4898
#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xffffff

class Color {
public:
	int color;
	bool transparent;

	Color() : color(COLOR_WHITE), transparent(true){}
	Color(int color_code, bool trans = true) : color(color_code), transparent(trans){}
	Color(const Color& other) : color(other.color), transparent(other.transparent){}

	void operator=(const Color& other) { color = other.color; transparent = other.transparent; }

	bool operator==(const Color& other) { return color == other.color && transparent == other.transparent; }
	bool operator!=(const Color& other) { return color != other.color && transparent != other.transparent; }
};