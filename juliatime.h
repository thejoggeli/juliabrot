#ifndef JULIATIME_H
#define JULIATIME_H

class JuliaTime
{
private:
	JuliaTime();
public:
	static int startTimeMs;
	static int currentTimeMs;
	static int lastTimeMs;
	static int deltaTimeMs;
	static double sinceStart;
	static double deltaTime;
	static void update();
	static void start();
	static int fps;
	static int fpsCounter;
	static int lastFpsTimeMs;
};

#endif // TIME_H
