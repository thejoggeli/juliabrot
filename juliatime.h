#ifndef JULIATIME_H
#define JULIATIME_H

class JuliaTime
{
private:
	JuliaTime();
public:

	//! start timestamp (in ms)
	static int startTimeMs;

	//! timestamp current (in ms)
	static int currentTimeMs;

	//! timestamp from last update (in ms)
	static int lastTimeMs;

	//! time passed since last update (in ms)
	static int deltaTimeMs;

	//! time passed since start (in seconds)
	static double sinceStart;

	//! time passed since last update (in seconds)
	static double deltaTime;

	//! update time (recalculates time since start, delta time, fps, etc)
	static void update();

	//! start time (initialize everything)
	static void start();

	//! current fps (updates every second)
	static int fps;

private:
	static int fpsCounter;
	static int lastFpsTimeMs;
};

#endif // TIME_H
