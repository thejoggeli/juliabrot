#include "color.h"

const Color Color::BLACK = Color(0, 0, 0);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::GRAY = Color(0.5f, 0.5f, 0.5f);
const Color Color::LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f);
const Color Color::DARK_GRAY = Color(0.25f, 0.25f, 0.25f);
const Color Color::RED = Color(1.0f, 0, 0);
const Color Color::GREEN = Color(0, 1.0f, 0);
const Color Color::BLUE = Color(0, 0, 1.0f);
const Color Color::YELLOW = Color(1.0f, 1.0f, 0);
const Color Color::MAGENTA = Color(1.0f, 0, 1.0f);
const Color Color::CYAN = Color(0, 1.0f, 1.0f);

Color::Color(){}
Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
}

Color::~Color(){
}

void Color::SetRgb(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
}

void Color::SetRgba(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Color::operator = (const Color& color){
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

