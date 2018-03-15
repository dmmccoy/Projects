#include <SDL.h>
#include <string>
#include <queue>

class Engine;

class Clock {
public:
  static Clock& getInstance();
  unsigned int getTicks() const;

private:
  friend class Engine;

  bool started;
  bool paused;

  const bool FRAME_CAP_ON;
  const Uint32 PERIOD;

  unsigned int frames;

  unsigned int timeAtStart;
  unsigned int timeAtPause;
  unsigned int currTicks;
  unsigned int prevTicks;
  unsigned int ticks;
  unsigned int totalTime;

  std::deque<int> avgTicks;

  unsigned int getElapsedTicks();
  void toggleSloMo();

  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned int capFrameRate() const;
  int getFps() const;

  void startClock();
  void pause();
  void unpause();
  void calcTime();

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};
