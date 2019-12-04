#include "juliatime.h"
#include <time.h>
#include <QTime>

using namespace std;

static QTime qtime;

int JuliaTime::currentTimeMs = 0;
int JuliaTime::lastTimeMs = 0;
int JuliaTime::deltaTimeMs = 0;
int JuliaTime::startTimeMs = 0;
double JuliaTime::sinceStart = 0.0;
double JuliaTime::deltaTime = 0.0;

JuliaTime::JuliaTime()
{
}

void JuliaTime::start()
{
  qtime = QTime::currentTime();
  int ms = qtime.msecsSinceStartOfDay();
  startTimeMs = ms;
  currentTimeMs = ms;
  lastTimeMs = ms;
}

void JuliaTime::update()
{
  qtime = QTime::currentTime();
  lastTimeMs = currentTimeMs;
  currentTimeMs = qtime.msecsSinceStartOfDay();
  deltaTimeMs = currentTimeMs - lastTimeMs;
  sinceStart = (double) (currentTimeMs - startTimeMs) / 1000.0;
  deltaTime = (double) (deltaTimeMs) / 1000.0;
}
