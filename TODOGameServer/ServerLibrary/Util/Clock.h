#pragma once

#include <chrono>
#include <ctime>

using namespace std::chrono;
typedef system_clock::time_point timePoint;

#define NOW_TICK				CLOCK.systemTick
#define NOW_STRING				CLOCK.nowTime

#define TICK_MIN                (60)
#define TICK_HOUR               (TICK_MIN * 60)
#define TICK_DAY                (TICK_HOUR * 24)

#define TICK_TO_MIN(x)          (x / TICK_MIN)
#define MIN_TO_TICK(x)          (x * TICK_MIN)

#define TICK_TO_HOUR(x)         (x / TICK_HOUR)        
#define HOUR_TO_TICK(x)         (x * TICK_HOUR)

#define TICK_TO_DAY(x)          (x / TICK_DAY)
#define DAY_TO_TICK(x)          (x * TICK_DAY)

typedef enum
{
	DAY_SUNDAY = 0,
	DAY_MONDAY,
	DAY_TUESDAY,
	DAY_WEDNESDAY,
	DAY_THURSDAY,
	DAY_FRIDAY,
	DAY_SATURDAY,
}DayOfTheWeek;

#define DATETIME_FORMAT	L"D%Y-%m-%dT%H:%M:%S"
#define DATE_FORMAT		L"%Y-%m-%d"
#define TIME_FORMAT		L"%H:%M:%S"
#define DB_TIME_FORMAT	L"%4d-%2d-%2d %2d:%2d:%2d"

class Clock : public Singleton<Clock>
{
private:
	time_t serverStartTick_;
	wstring tickToStr(time_t tick, WCHAR* fmt = DATETIME_FORMAT);
public:
	Clock();
	~Clock();

	time_t strToTick(wstring str, wchar_t* fmt = DB_TIME_FORMAT);

	wstring nowTimeWithMillisec(WCHAR* fmt = DATETIME_FORMAT);
	DayOfTheWeek todayOfTheWeek();
	
	time_t Clock::serverStartTick() { return serverStartTick_; }
	time_t Clock::systemTick() { return system_clock::to_time_t(system_clock::now()); }
	
	wstring nowTime(wchar_t* fmt = DATETIME_FORMAT) { tickToStr(systemTick(), fmt); }
	wstring today() { return this->tickToStr(systemTick(), DATE_FORMAT); }
	wstring tomorrow() { return this->tickToStr(systemTick() + DAY_TO_TICK(1), DATE_FORMAT); }
	wstring yesterday() { return this->tickToStr(systemTick() - DAY_TO_TICK(1), DATE_FORMAT); }
};