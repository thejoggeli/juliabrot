#pragma once

class Color;

class ColorHsl {
public:
    static const ColorHsl RED;
    static const ColorHsl GREEN;
    static const ColorHsl BLUE;
    static const ColorHsl CYAN;
    static const ColorHsl MAGENTA;
    static const ColorHsl YELLOW;
    float h = 0.0f;
    float s = 1.0f;
    float l = 1.0f;
    ColorHsl();
    ColorHsl(float h, float s, float l);
    void SetHsl(float h, float s, float l);
    void SetHsl(const ColorHsl* color);
    void AddHue(float amount);
	Color GetRgb() const;
	unsigned int GetRgbUint32() const;
	static Color HslToRgb(float h, float s, float l);
	static Color HslToRgb(const ColorHsl* color);
    static float HueToRgb(float p, float q, float t);
    static float WrapHue(float hue);
};
