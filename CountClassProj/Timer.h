#ifndef TIMER_H
#define TIMER_H


class Timer
{
	public:
		Timer();
		~Timer();

		void start();
		void stop();
		void pause();
		void unpause();

		unsigned int getTicks();

		bool IsStarted();
		bool IsPaused();

	private:
		//clock time when time started
		unsigned int mStartTicks;

		//ticks stored when timer paused
		unsigned int mPausedTicks;

		//timer status
		bool mPaused;
		bool mStarted;
};

#endif