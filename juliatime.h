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
};

#endif // TIME_H
