#pragma once

class Color;

class ColorHsl {
public:
	static unsigned int GetRgbUint32(float h, float s, float l);
	static float HueToRgb(float p, float q, float t);
	static float WrapHue(float hue);
};
