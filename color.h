#pragma once

class Color
{
public:
    static const Color BLACK;
    static const Color WHITE;
    static const Color GRAY;
    static const Color LIGHT_GRAY;
    static const Color DARK_GRAY;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color MAGENTA;
    static const Color CYAN;
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;
    Color();
    Color(float r, float g, float b);
    ~Color();
    void SetRgb(float r, float g, float b);
    void SetRgba(float r, float g, float b, float);
    void operator = (const Color& color);
};

