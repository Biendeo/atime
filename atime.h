#ifndef ATIME_H
#define ATIME_H

#ifdef __cplusplus
#include <ctime>
#include <string>

class atime {
	public:
	atime() {
		timeData = static_cast<time_t>(0);
	};

	atime(time_t time) {
		this->timeData = time;
	};

	atime &operator=(atime otherTime) {
		this->timeData = otherTime.timeData;
		return *this;
	}

	atime &operator=(time_t otherTime) {
		this->timeData = otherTime;
		return *this;
	}

	time_t operator+=(atime &otherTime) {
		timeData += otherTime.timeData;
		return timeData;
	}

	time_t operator+=(time_t &otherTime) {
		timeData += otherTime;
		return timeData;
	}

	friend time_t operator+(atime leftTime, time_t rightTime) {
		return leftTime.timeData + rightTime;
	}

	friend time_t operator+(time_t leftTime, atime rightTime) {
		return rightTime + leftTime;
	}

	friend time_t operator+(atime leftTime, atime rightTime) {
		return leftTime.timeData + rightTime.timeData;
	}

	std::string display(std::string format) {
		size_t foundPos;

		while ((foundPos = format.find("YYYY")) != std::string::npos) {
			format.replace(foundPos, 4, std::to_string(getYear()));
		}
		
		while ((foundPos = format.find("MM")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getMonth()), 0));
		}
		
		while ((foundPos = format.find("dd")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getDayOfMonth()), 0));
		}
		
		while ((foundPos = format.find("EEE")) != std::string::npos) {
			format.replace(foundPos, 3, std::to_string(getDayOfWeek()));
		}
		
		while ((foundPos = format.find("hh")) != std::string::npos) {
			format.replace(foundPos, 2, std::to_string(getHour()));
		}

		while ((foundPos = format.find("mm")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getMinutes()), 2));
		}

		while ((foundPos = format.find("ss")) != std::string::npos) {
			format.replace(foundPos, 2, leadZeroes(std::to_string(getSeconds()), 2));
		}

		return format;
	}

	std::string display() {
		return display("EEE dd/MM/YYYY hh:mm:ss");
	}

	time_t time() {
		return timeData;
	}

	atime &now() {
		timeData = std::time(NULL);
		return *this;
	}

	int getYear() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_year + YEAR_DIFFERENCE_TO_MK;
	}

	int getMonth() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_mon + 1;
	}

	int getDayOfMonth() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_mday;
	}

	int getDayOfYear() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_yday;
	}

	int getDayOfWeek() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_wday;
	}

	int getHour() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_hour;
	}

	int getMinutes() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_min;
	}

	int getSeconds() {
		// TODO: Create own localtime function to make it thread-safe.
		return localtime(&timeData)->tm_sec;
	}

	void setYear(int year) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_year = year - YEAR_DIFFERENCE_TO_MK;
		timeData = mktime(timeStruct);
	}
	
	void setMonth(int month) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_mon = month - 1;
		timeData = mktime(timeStruct);
	}

	void setDayOfMonth(int day) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_mday = day;
		timeData = mktime(timeStruct);
	}

	void setDayOfYear(int day) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_yday = day;
		timeData = mktime(timeStruct);
	}

	void setDayOfWeek(int day) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_yday = day;
		timeData = mktime(timeStruct);
	}

	void setHour(int hour) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_hour = hour;
		timeData = mktime(timeStruct);
	}

	void setMinutes(int minutes) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_min = minutes;
		timeData = mktime(timeStruct);
	}

	void setSeconds(int seconds) {
		// TODO: Determine behaviour when time is out of range.
		tm *timeStruct = localtime(&timeData);
		timeStruct->tm_sec = seconds;
		timeData = mktime(timeStruct);
	}

	enum WEEKDAY {
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	};

	enum MONTH {
		JANUARY,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	private:
	time_t timeData;

	static const int YEAR_DIFFERENCE_TO_MK = 1900;

	std::string leadZeroes(std::string str, int desiredLength) {
		for (int i = str.length(); i < desiredLength; i++) {
			str.append("0");
		}
		return str;
	}
};

#else

#endif


#endif