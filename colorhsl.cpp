#include "colorhsl.h"
#include <math.h>

float ColorHsl::WrapHue(float hue){
	return fmodf(hue, 1.0f);
}

unsigned int ColorHsl::GetRgbUint32(float h, float s, float l) {
	unsigned int r, g, b;
	if(s == 0.0f){
		r = g = b = (int)(l*255.0); // achromatic
	} else {
		float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
		float p = 2.0f * l - q;
		r = (int)(ColorHsl::HueToRgb(p, q, h + 1.0f/3.0f)*255.0);
		g = (int)(ColorHsl::HueToRgb(p, q, h)*255.0);
		b = (int)(ColorHsl::HueToRgb(p, q, h - 1.0f/3.0f)*255.0);
	}
	return 0xFF000000 | (r << 16) | (g << 8) | b;
}

float ColorHsl::HueToRgb(float p, float q, float t){
	if(t < 0.0f) t += 1.0f;
	if(t > 1.0f) t -= 1.0f;
	if(t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
	if(t < 1.0f/2.0f) return q;
	if(t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
	return p;
}
