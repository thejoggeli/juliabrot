#pragma once

class Color;

class ColorHsl {
public:
	//! convert color from HSL to 32-bit integer (e.g. yellow = 0xFFFF00)
	//! \param h hue from 0 to 1
	//! \param s saturation from 0 to 1
	//! \param l lightness from 0 to 1
	//! \return 32-bit integer (e.g. yellow = 0xFFFF00)
	static unsigned int GetRgbUint32(float h, float s, float l);
protected:

	//! convert hue to rgb (used for hsl-2-rgb algorithm)
	static float HueToRgb(float p, float q, float t);

	//! wrap hue between 0 and 1
	static float WrapHue(float hue);
};
