#include "stdafx.h"
#include "Clock.h"


Clock::Clock()
{
	serverStartTick_ = this->systemTick();
}

Clock::~Clock()
{
}

wstring Clock::tickToStr(time_t tick, WCHAR * fmt)
{
	array<wchar_t, SIZE_64> timeStr;

	tm time;
	localtime_s(&time, &tick);

	wcsftime(timeStr.data(), timeStr.size(), fmt, &time);

	return timeStr.data();
}

time_t Clock::strToTick(wstring str, wchar_t * fmt)
{
	int year, month, day, hour, min, sec;

	swscanf_s(str.data(), fmt, &year, &month, &day, &hour, &min, &sec);
	//struct tm
	//{
	//	int tm_sec;   // seconds after the minute - [0, 60] including leap second
	//	int tm_min;   // minutes after the hour - [0, 59]
	//	int tm_hour;  // hours since midnight - [0, 23]
	//	int tm_mday;  // day of the month - [1, 31]
	//	int tm_mon;   // months since January - [0, 11]
	//	int tm_year;  // years since 1900
	//	int tm_wday;  // days since Sunday - [0, 6]
	//	int tm_yday;  // days since January 1 - [0, 365]
	//	int tm_isdst; // daylight savings time flag
	//};
	tm time = { sec, min, hour, day, month - 1, year - 1900 };

	return mktime(&time);
}
wstring Clock::nowTimeWithMillisec(WCHAR * fmt)
{
#if 0
	timePoint now = system_clock::now();
	timePoint oldSecond = system_clock::from_time_t(this->systemTick());

	duration<double> milliSecond = now - oldSecond;
	array<WCHAR, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", (int)(milliSecond.count() * 1000));
#else
	high_resolution_clock::time_point point = high_resolution_clock::now();
	milliseconds ms = duration_cast<milliseconds>(point.time_since_epoch());

	seconds s = duration_cast<seconds>(ms);
	time_t t = s.count();
	std::size_t fractionalSeconds = ms.count() % 1000;
	array<WCHAR, SIZE_8> milliStr;
	_snwprintf_s(milliStr.data(), milliStr.size(), _TRUNCATE, L"%03d", (int)(fractionalSeconds));
#endif
	wstring timeString = this->tickToStr(this->systemTick(), fmt);
	timeString += L".";
	timeString += milliStr.data();
	return timeString;
}

DayOfTheWeek Clock::todayOfTheWeek()
{
	tm time;
	time_t tick = this->systemTick();
	localtime_s(&time, &tick);
	return (DayOfTheWeek)time.tm_wday;
}
